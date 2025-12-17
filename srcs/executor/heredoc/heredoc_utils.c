/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:51:36 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 16:04:57 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_hd_filename(void)
{
	static int	hd_id;
	char		*num;
	char		*filename;

	num = ft_itoa(hd_id++);
	filename = ft_strjoin("/tmp/hd_", num);
	free(num);
	return (filename);
}

int	setup_heredoc_file(t_redir *cmd_red)
{
	char	*filename;
	int		fd;

	filename = generate_hd_filename();
	if (!filename)
		return (1);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("minishell: heredoc");
		free(filename);
		return (1);
	}
	close(fd);
	free(cmd_red->file);
	cmd_red->file = filename;
	cmd_red->type = REDIR_IN;
	return (0);
}

int	should_expand_heredoc(t_redir *cmd_red)
{
	int		file_len;
	char	*old_cmd_red;

	file_len = ft_strlen(cmd_red->file);
	if ((cmd_red->file[0] == '\"' || cmd_red->file[0] == '\'')
		&& cmd_red->file[0] == cmd_red->file[file_len - 1])
	{
		old_cmd_red = cmd_red->file;
		cmd_red->file = ft_substr(old_cmd_red, 1, file_len - 2);
		free(old_cmd_red);
		return (0);
	}
	return (1);
}

int	has_heredoc(t_cmd *cmd_list)
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
				return (1);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}
