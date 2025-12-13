/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:27:09 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/13 02:56:40 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *generate_hd_filename(void)
{
	static int	hd_id;
	char *num;
	char *filename;

	num = ft_itoa(hd_id++);
	filename = ft_strjoin("/tmp/hd_", num);
	
	free(num);
	return filename;
}

int setup_heredoc_file(t_redir *cmd_red)
{
    char *filename;
    int   fd;

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
	int file_len = ft_strlen(cmd_red->file);
	if((cmd_red->file[0] == '\"' || cmd_red->file[0] == '\'')
		&& cmd_red->file[0] == cmd_red->file[file_len-1])
	{
		char *old_cmd_red = cmd_red->file;
		cmd_red->file = ft_substr(old_cmd_red,1,file_len -2);
		free(old_cmd_red);
		return (0);
	}
	return (1);
}

int has_heredoc(t_cmd *cmd_list)
{
    t_cmd   *current_cmd;
    t_redir *current_redir;

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

char	*expand_line(char *line, t_shell *shell)
{
	int		i;
	char	*expanded;
	char	*tmp;

	i = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			char *status = ft_itoa(shell->last_exit_status);
			tmp = ft_strjoin(expanded, status);
			free(expanded);
			free(status);
			expanded = tmp;
			i += 2;
		}
		else if (line[i] == '$' && line[i + 1] != '\0' &&
         (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
		{
			int     start;
			char    *var_name;
			char    *value;

			start = i + 1;
			i = start;

			while (ft_isalnum(line[i]) || line[i] == '_')
				i++;

			var_name = ft_substr(line, start, i - start);
			value = get_env_value(var_name, shell->envp);

			if (value)
				tmp = ft_strjoin(expanded, value);
			else
				tmp = ft_strdup(expanded);

			free(expanded);
			free(var_name);
			expanded = tmp;
		}
		else
		{
			char c[2];

			c[0] = line[i];
			c[1] = '\0';
			tmp = ft_strjoin(expanded, c);
			free(expanded);
			expanded = tmp;
			i++;
		}
	}
	return (expanded);
}

int process_heredocs(t_cmd *cmd_list, t_shell *shell)
{
    t_cmd   *current_cmd;
    t_redir *current_redir;
    int      should_expand;
    int      fd;
    int      pid;
    int      status;
    char    *line;
    char    *delimiter;

    current_cmd = cmd_list;

    while (current_cmd)
    {
        current_redir = current_cmd->redirs;

        while (current_redir)
        {
            if (current_redir->type == HEREDOC)
            {
                should_expand = should_expand_heredoc(current_redir);
                delimiter = ft_strdup(current_redir->file);
				if (!delimiter)
        			return (1);
                if (setup_heredoc_file(current_redir) != 0)
                    return (1);
                pid = fork();
                if (pid == -1)
                {
                    write(2, "minishell: fork: ", 17);
                    write(2, strerror(errno), ft_strlen(strerror(errno)));
                    write(2, "\n", 1);
                    unlink(current_redir->file);
                    shell->last_exit_status = 1;
                    return (1);
                }
                if (pid == 0)
                {
                    signal(SIGINT, sigint_heredoc_handler);
                    signal(SIGQUIT, SIG_IGN);

                    fd = open(current_redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
                    if (fd < 0)
                    {
                        write(2, "minishell: ", 11);
                        write(2, current_redir->file, ft_strlen(current_redir->file));
                        write(2, ": ", 2);
                        write(2, strerror(errno), ft_strlen(strerror(errno)));
                        write(2, "\n", 1);
                        exit(1);
                    }

                    while (1)
                    {
                        line = readline("> ");

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
                        if (should_expand == 1)
                        {
							char *expanded = expand_line(line, shell);
							write(fd, expanded, ft_strlen(expanded));
                            write(fd, "\n", 1);
                            free(expanded);
                        }
                        else
                        {
                            write(fd, line, ft_strlen(line));
                            write(fd, "\n", 1);
                        }
                        free(line);
                    }
                }
                waitpid(pid, &status, 0);
				if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT) ||
					(WIFEXITED(status) && WEXITSTATUS(status) == 130))
				{
					unlink(current_redir->file);
					free(delimiter);
					shell->last_exit_status = 130;
					return (1);
				}
				free(delimiter);
            }
            current_redir = current_redir->next;
        }
        current_cmd = current_cmd->next;
    }
    return (0);
}

