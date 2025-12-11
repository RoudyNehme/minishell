/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:37:01 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/11 17:37:52 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

    while (1)
    {

		signal(SIGINT, sigint_prompt_handler);
		signal(SIGQUIT, SIG_IGN);
		
        line = readline("minishell> ");

		if (g_signal == SIGINT)
		{
			shell.last_exit_status = 130;
			g_signal = 0;
			continue;
		}


        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (*line)
            add_history(line);

        tokens = tokenizer(line);
        if (!tokens)
        {
            free(line);
            continue;
        }
        // printf("\n--- TOKENS ---\n");
        // print_tokens(tokens);

        // Parse
        cmds = parse(tokens);
        if (!cmds)
        {
            free_tokens(tokens);
            free(line);
            continue;
        }

        // printf("\n--- PARSED COMMANDS ---\n");
        // print_cmds(cmds);

        expand_commands(cmds, &shell);

        // printf("\n--- AFTER EXPANSION ---\n");
        // print_cmds(cmds);
        // TODO: Execute
// TEMPORARY BUILTIN TESTING
	// TEMPORARY BUILTIN TESTING
	if (cmds && cmds->args)
	{
	    execute_single(cmds, &shell,line,tokens);
	}
	    // Clean up
        free_cmds(cmds);
        free_tokens(tokens);
        free(line);
    }

    return (0);
}
