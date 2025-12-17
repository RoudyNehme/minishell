/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:52:48 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 15:59:03 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(1);
	}
	return (fd);
}

static void	write_heredoc_line(int fd, char *line, int expand, t_shell *shell)
{
	char	*expanded;

	if (expand == 1)
	{
		expanded = expand_heredoc_line(line, shell);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	else
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

static int	check_delimiter(char *line, char *delimiter, int fd)
{
	if (line == NULL)
	{
		close(fd);
		exit(0);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		close(fd);
		exit(0);
	}
	return (0);
}

void	heredoc_child_process(t_redir *redir, char *delim, int expand,
		t_shell *shell)
{
	int		fd;
	char	*line;

	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
	fd = open_heredoc_fd(redir->file);
	while (1)
	{
		line = readline("> ");
		check_delimiter(line, delim, fd);
		write_heredoc_line(fd, line, expand, shell);
		free(line);
	}
}
