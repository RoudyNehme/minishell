/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:54:47 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/17 18:16:10 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin_child(t_cmd *cmd, t_pipeline *pl)
{
	int				exit_code;
	t_cleanup_data	data;

	data.line = NULL;
	data.tokens = NULL;
	data.cmds = pl->cmd_list;
	exit_code = run_builtin(cmd->args, pl->shell, &data);
	exit(exit_code);
}

void	execute_external_child(t_cmd *cmd, t_pipeline *pl)
{
	char	*path;

	path = get_command_path(cmd->args[0], pl->shell->envp);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	if (!ft_strcmp(path, "PERMISSION_DENIED"))
	{
		write(2, "minishell: ", 11);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": Permission denied\n", 20);
		exit(126);
	}
	execve(path, cmd->args, pl->shell->envp);
	write(2, "minishell: ", 11);
	perror(cmd->args[0]);
	exit(126);
}

void	execute_child_cmd(t_cmd *cmd, t_pipeline *pl)
{
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		execute_builtin_child(cmd, pl);
	else
		execute_external_child(cmd, pl);
	exit(1);
}
