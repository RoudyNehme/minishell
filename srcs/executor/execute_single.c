/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:14:57 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/27 14:46:41 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void execute_single(t_cmd *cmd, t_shell *shell, char *line, t_token *tokens)
{
if (is_builtin(cmd->args[0]))
{
    int save_stdout = dup(1);
    int save_stdin = dup(0);

    apply_redirs_single(cmd);
    shell->last_exit_status =
        run_builtin(cmd->args, shell, line, tokens, shell->cmds);
    if (dup2(save_stdout, 1) == -1 ||
        dup2(save_stdin, 0) == -1)
    {
        perror("minishell");
        exit(1);
    }
    close(save_stdout);
    close(save_stdin);
    return;
}
else
{
	pid_t	pid;
	int		status;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		// fork failed
		shell->last_exit_status = 1;
		return ;
	}
	if (pid == 0)
	{
		// CHILD
		if (!cmd->args || !cmd->args[0])
			exit(0); // only redirs, no command

		apply_redirs_single(cmd);

		path = get_command_path(cmd->args[0], shell->envp);
		if (!path)
		{
			write(2, "minishell: ", 11);
			write(2, cmd->args[0], ft_strlen(cmd->args[0]));
			write(2, ": command not found\n", 21);
			exit(127);
		}
		if (!ft_strcmp(path, "PERMISSION_DENIED"))
		{
			write(2, "minishell: ", 11);
			write(2, cmd->args[0], ft_strlen(cmd->args[0]));
			write(2, ": Permission denied\n", 20);
			exit(126);
		}
		execve(path, cmd->args, shell->envp);
		// execve failed:
		write(2, "minishell: ", 11);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(126);
	}
	// PARENT
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
}