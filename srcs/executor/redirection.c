/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:06:26 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/07 01:22:15 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	apply_redirs_single(t_cmd *cmd)
{
	t_redir	*cmd_red;
	int		fd;

	cmd_red = cmd->redirs;
	while (cmd_red)
	{
		if (cmd_red->type == REDIR_IN)
		{
			fd = open(cmd_red->file, O_RDONLY);
			if (fd < 0)
			{
				write(2, "minishell: ", 11);
				write(2, cmd_red->file, ft_strlen(cmd_red->file));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				exit(1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				write(2, "minishell: ", 11);
				write(2, cmd_red->file, ft_strlen(cmd_red->file));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				close(fd);
				exit(1);
			}
			close(fd);
		}
		else if (cmd_red->type == REDIR_OUT)
		{
			fd = open(cmd_red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				write(2, "minishell: ", 11);
				write(2, cmd_red->file, ft_strlen(cmd_red->file));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				write(2, "minishell: ", 11);
				write(2, cmd_red->file, ft_strlen(cmd_red->file));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				close(fd);
				exit(1);
			}
			close(fd);
		}
		else if (cmd_red->type == REDIR_APPEND)
		{
			fd = open(cmd_red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				write(2, "minishell: ", 11);
				write(2, cmd_red->file, ft_strlen(cmd_red->file));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				write(2, "minishell: ", 11);
				write(2, cmd_red->file, ft_strlen(cmd_red->file));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				close(fd);
				exit(1);
			}
			close(fd);
		}
		else if (cmd_red->type == HEREDOC)
		{
			
		}
		cmd_red = cmd_red->next;
	}
}
