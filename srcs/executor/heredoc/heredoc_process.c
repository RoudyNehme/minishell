/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:53:44 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 16:03:42 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_fork_error(t_redir *redir, t_shell *shell)
{
	write(2, "minishell: fork: ", 17);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	unlink(redir->file);
	shell->last_exit_status = 1;
	return (1);
}

static int	handle_heredoc_status(int status, t_redir *redir, char *delim,
		t_shell *shell)
{
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		unlink(redir->file);
		free(delim);
		shell->last_exit_status = 130;
		return (1);
	}
	free(delim);
	return (0);
}

static int	process_single_heredoc(t_redir *redir, t_shell *shell)
{
	int		should_expand;
	char	*delimiter;
	int		pid;
	int		status;

	should_expand = should_expand_heredoc(redir);
	delimiter = ft_strdup(redir->file);
	if (!delimiter)
		return (1);
	if (setup_heredoc_file(redir) != 0)
		return (1);
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(redir, shell));
	if (pid == 0)
		heredoc_child_process(redir, delimiter, should_expand, shell);
	waitpid(pid, &status, 0);
	return (handle_heredoc_status(status, redir, delimiter, shell));
}

int	process_heredocs(t_cmd *cmd_list, t_shell *shell)
{
	t_cmd	*current_cmd;
	t_redir	*current_redir;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		current_redir = current_cmd->redirs;
		while (current_redir)
		{
			if (current_redir->type == HEREDOC)
			{
				if (process_single_heredoc(current_redir, shell) != 0)
					return (1);
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}
