/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:45:00 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/17 19:25:29 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_shlvl(t_shell *shell)
{
    char	*shlvl_str;
    int		shlvl;
    char	*new_shlvl;

    shlvl_str = get_env_value("SHLVL", shell->envp);
    if (!shlvl_str)
        shlvl = 0;
    else
        shlvl = ft_atoi(shlvl_str);
    if (shlvl < 0)
        shlvl = 0;
    shlvl++;
    new_shlvl = ft_itoa(shlvl);
    if (!new_shlvl)
        return ;
    set_env("SHLVL", new_shlvl, shell);
    free(new_shlvl);
}

static void	process_line(char *line, t_shell *shell)
{
    t_token	*tokens;
    t_cmd	*cmds;

    tokens = tokenizer(line);
    if (!tokens)
        return ;
    cmds = parse(tokens);
    if (!cmds)
    {
        free_tokens(tokens);
        return ;
    }
    execute_pipeline(cmds, shell, line, tokens);
    free_tokens(tokens);
    free_cmds(cmds);
}

int	main(int argc, char **argv, char **envp)
{
    char	*line;
    t_shell	shell;

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
            ft_putendl_fd("exit", 1);
            break ;
        }
        if (*line)
            add_history(line);
        process_line(line, &shell);
        free(line);
    }
    free_2d(shell.envp);
    return (shell.last_exit_status);
}
