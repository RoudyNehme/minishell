/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:59:58 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/05 18:00:01 by rberdkan         ###   ########.fr       */
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
        line = readline("minishell> ");

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
        //print_tokens(tokens);

        // Parse
        cmds = parse(tokens);
        if (!cmds)
        {
            free_tokens(tokens);
            free(line);
            continue;
        }

        printf("\n--- PARSED COMMANDS ---\n");
        print_cmds(cmds);

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
	else
	{
    	printf("Not a builtin (execution not implemented yet)\n");
	}
        // Clean up
        free_cmds(cmds);
        free_tokens(tokens);
        free(line);
    }

    return (0);
}
