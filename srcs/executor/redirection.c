/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:06:26 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 21:01:39 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redir_error(char *filename)
{
	write(2, "minishell: ", 11);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(1);
}

static void	handle_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
		print_redir_error(redir->file);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		print_redir_error(redir->file);
	}
	close(fd);
}

static void	handle_redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_redir_error(redir->file);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		print_redir_error(redir->file);
	}
	close(fd);
}

static void	handle_redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		print_redir_error(redir->file);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		print_redir_error(redir->file);
	}
	close(fd);
}

void	apply_redirs_single(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			handle_redir_in(redir);
		else if (redir->type == REDIR_OUT)
			handle_redir_out(redir);
		else if (redir->type == REDIR_APPEND)
			handle_redir_append(redir);
		redir = redir->next;
	}
}
