/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:27:09 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/11 16:39:29 by rberdkan         ###   ########.fr       */
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
	//printf("%s\n", cmd_red->file);
	int file_len = ft_strlen(cmd_red->file);
	//printf("%c \n",cmd_red->file[file_len-1]);
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

int process_heredocs(t_cmd *cmd_list, t_shell *shell)
{
	   t_cmd *current_cmd;
	   t_redir *current_redir;
	   int	should_expand;
	   int fd;
	   int pid;

	   (void)shell;
    int i;

    current_cmd = cmd_list;
    i = 1;
    while (current_cmd)
    {
		current_redir = current_cmd->redirs;
		while(current_redir)
		{
			if(current_redir->type == HEREDOC)
			{
				should_expand = should_expand_heredoc(current_redir);
				if(setup_heredoc_file(current_redir) != 0)
					return (1);
				pid = fork();
				
				if(pid == -1)
				{
					write(2, "minishell: fork: ", 17);
					write(2, strerror(errno), ft_strlen(strerror(errno)));
					write(2, "\n", 1);
					shell->last_exit_status = 1;
					unlink(current_redir->file);
					return (1);
				}
				if(pid == 0)
				{
					signal(SIGINT, sigint_prompt_handler);
					signal(SIGQUIT, SIG_IGN);
					fd = open(current_redir->file, O_WRONLY | O_CREAT | O_TRUNC);
				}
				//waitpid(child, &status, 0)

			}
			current_redir = current_redir->next;
		}
    }
    printf("\n");
	return (0);
}