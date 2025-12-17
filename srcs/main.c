/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:37:01 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/13 16:59:54 by rberdkan         ###   ########.fr       */
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

    setup_signals();

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
        if (!tokens)
        {
            free(line);
            continue;
        }

        cmds = parse(tokens);
        if (!cmds)
        {
            free_tokens(tokens);
            free(line);
            continue;
        }

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
			if(cmds->next == NULL)
            	execute_single(cmds, &shell, line, tokens);
        }

        free_cmds(cmds);
        free_tokens(tokens);
        free(line);
    }
    return (shell.last_exit_status);
}
