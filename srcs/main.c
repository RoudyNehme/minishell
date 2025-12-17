/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:37:01 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/17 00:46:07 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_shlvl_value(char **envp)
{
    char	*shlvl_str;
    int		shlvl;

    if (!envp)
        return (0);
    shlvl_str = get_env_value("SHLVL", envp);
    if (!shlvl_str)
        return (0);
    shlvl = ft_atoi(shlvl_str);
    if (shlvl < 0)
        return (0);
    if (shlvl > 999)
        return (1);
    return (shlvl);
}

void	increment_shlvl(t_shell *shell)
{
    int		shlvl;
    char	*new_shlvl;

    // Get current SHLVL (handles all edge cases)
    shlvl = get_shlvl_value(shell->envp);
    
    // Increment
    shlvl++;
    
    // Convert to string
    new_shlvl = ft_itoa(shlvl);
    if (!new_shlvl)
        return ;
    
    // Update environment
    set_env("SHLVL", new_shlvl, shell);
    
    free(new_shlvl);
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_token *tokens;
    t_cmd *cmds;
    t_shell shell;

    (void)argc;
    (void)argv;
    shell.envp = dup_env(envp);
    shell.cmds = NULL;
    shell.last_exit_status = 0;

    signal(SIGINT, sigint_prompt_handler);
    signal(SIGQUIT, SIG_IGN);

	increment_shlvl(&shell);

   while (1)
{
    line = readline("minishell> ");

    if (!line)
    {
        printf("exit\n");
        break;
    }
    if (g_signal == SIGINT)
    {
        shell.last_exit_status = 130;
        g_signal = 0;
        if (line && *line)
            free(line);
        continue;
    }
    	if (*line)
        add_history(line);
        tokens = tokenizer(line);
       // print_tokens(tokens);
        if (!tokens)
        {
            free(line);
            continue;
        }

        cmds = parse(tokens);
       // print_cmds(cmds);
        if (!cmds)
        {
            free_tokens(tokens);
            free(line);
            continue;
        }
		//print_cmds(cmds);
		//print_tokens(tokens);
        expand_commands(cmds, &shell);
		if (cmds && cmds->args)
		{
			if (process_heredocs(cmds, &shell) != 0)
			{	
				g_signal = 0;
				free_cmds(cmds);
				free_tokens(tokens);
				free(line);
				continue;
			}
			//write(2, "\n=== MAIN: AFTER HEREDOC ===\n", 30);
			//write(2, "About to execute pipeline\n", 26);
			
			// Execute based on number of commands
			if (cmds->next == NULL)
				execute_single(cmds, &shell, line, tokens);
			else
				execute_pipeline(cmds, &shell, line, tokens);
			g_signal = 0;
		}
        free_cmds(cmds);
        free_tokens(tokens);
        free(line);
    }
    return (shell.last_exit_status);
}
