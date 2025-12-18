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

static int	process_input(char *line, t_token **tokens, t_cmd **cmds)
{
	if (*line)
		add_history(line);
	*tokens = tokenizer(line);
	if (!*tokens)
		return (0);
	*cmds = parse(*tokens);
	if (!*cmds)
	{
		free_tokens(*tokens);
		return (0);
	}
	return (1);
}

static void	execute_commands(t_cmd *cmds, t_shell *shell, char *l, t_token *t)
{
	expand_commands(cmds, shell);
	if (!cmds || !cmds->args)
		return ;
	if (process_heredocs(cmds, shell) != 0)
	{
		g_signal = 0;
		return ;
	}
	if (cmds->next == NULL)
		execute_single(cmds, shell, l, t);
	else
		execute_pipeline(cmds, shell, l, t);
	g_signal = 0;
}

static void	main_loop(t_shell *shell)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	while (1)
	{
		g_signal = 0;
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (g_signal == SIGINT && handle_signal_interrupt(shell, line))
			continue ;
		if (!process_input(line, &tokens, &cmds))
		{
			free(line);
			continue ;
		}
		execute_commands(cmds, shell, line, tokens);
		free_cmds(cmds);
		free_tokens(tokens);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	main_loop(&shell);
	return (shell.last_exit_status);
}
