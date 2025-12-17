/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:10:16 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 20:17:31 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_command_not_found(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	exit(127);
}

static void	handle_permission_denied(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Permission denied\n", 20);
	exit(126);
}

static void	handle_execve_error(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(126);
}

void	execute_external_command(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	apply_redirs_single(cmd);
	path = get_command_path(cmd->args[0], shell->envp);
	if (!path)
		handle_command_not_found(cmd->args[0]);
	if (!ft_strcmp(path, "PERMISSION_DENIED"))
		handle_permission_denied(cmd->args[0]);
	execve(path, cmd->args, shell->envp);
	handle_execve_error(cmd->args[0]);
}
