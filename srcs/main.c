/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:29:11 by rnehme            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/11/12 22:35:31 by rberdkan         ###   ########.fr       */
=======
/*   Updated: 2025/11/22 03:01:25 by rnehme           ###   ########.fr       */
>>>>>>> origin/rnehme
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
    shell.envp = envp;
	shell.own_env = 0;
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

        printf("\n--- TOKENS ---\n");
        print_tokens(tokens);

        // Parse
        cmds = parse(tokens);
        if (!cmds)
        {
            free_tokens(tokens);
            free(line);
            continue;
        }

        expand_commands(cmds, &shell);

        printf("\n--- PARSED COMMANDS ---\n");
        print_cmds(cmds);

        // TODO: Execute

        // Clean up
        free_cmds(cmds);
        free_tokens(tokens);
        free(line);
    }

    return (0);
}
