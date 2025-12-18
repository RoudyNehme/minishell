/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:20:33 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/19 00:20:35 by rberdkan         ###   ########.fr       */
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

static int	handle_line(char **line, t_shell *shell)
{
	*line = readline("minishell> ");
	if (!*line)
	{
		printf("exit\n");
		rl_clear_history();
		if (shell->envp)
			free_2d(shell->envp);
		exit(shell->last_exit_status);
	}
	if (g_signal == SIGINT && **line == '\0')
	{
		shell->last_exit_status = 130;
		g_signal = 0;
		free(*line);
		return (-1);
	}
	g_signal = 0;
	return (1);
}

static void	main_loop(t_shell *shell)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;
	int		status;

	while (1)
	{
		status = handle_line(&line, shell);
		if (status == 0)
			break ;
		if (status == -1)
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
	rl_clear_history();
	if (shell.envp)
		free_2d(shell.envp);
	return (shell.last_exit_status);
}
