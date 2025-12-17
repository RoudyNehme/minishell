/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:09:32 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/17 19:45:35 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_fds(int save_stdout, int save_stdin)
{
	if (dup2(save_stdout, STDOUT_FILENO) == -1
		|| dup2(save_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell");
		exit(1);
	}
	close(save_stdout);
	close(save_stdin);
}

static void	execute_builtin_single(t_cmd *cmd, t_shell *shell,
	t_cleanup_data *data)
{
	int	save_stdout;
	int	save_stdin;

	save_stdout = dup(STDOUT_FILENO);
	save_stdin = dup(STDIN_FILENO);
	apply_redirs_single(cmd);
	shell->last_exit_status = run_builtin(cmd->args, shell, data);
	restore_fds(save_stdout, save_stdin);
}

static void	handle_child_process(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		shell->last_exit_status = 1;
		return ;
	}
	if (pid == 0)
		execute_external_command(cmd, shell);
	if (waitpid(pid, &status, 0) == -1)
	{
		shell->last_exit_status = 1;
		return ;
	}
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_status = 128 + WTERMSIG(status);
}

void	execute_single(t_cmd *cmd, t_shell *shell, char *line, t_token *tokens)
{
	t_cleanup_data	data;

	data.line = line;
	data.tokens = tokens;
	data.cmds = cmd;
	if (is_builtin(cmd->args[0]))
		execute_builtin_single(cmd, shell, &data);
	else
		handle_child_process(cmd, shell);
}
