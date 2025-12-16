/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:21:20 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 12:49:11 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void execute_pipeline(t_cmd *cmd_list, t_shell *shell, char *line, t_token *tokens)
{
    //write(2, "\n=== PIPELINE START ===\n", 24);
	
    int cmd_count;
    int pipes_count;
    int i;
    t_cmd *current_command;
    int command_index;

    t_cleanup_data data;

    data.line = line;
    data.tokens = tokens;
    data.cmds = cmd_list;

    cmd_count = count_cmds(cmd_list);
	
    pipes_count = cmd_count - 1;
    int	pipes[pipes_count][2];
    
    // Create all pipes
    i = 0;
    while (i < pipes_count)
    {
        if (pipe(pipes[i]) == -1)
        {
            int j = 0;
            while (j < i)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }
            write(2, "minishell: ", 11);
            write(2, strerror(errno), ft_strlen(strerror(errno)));
            write(2, "\n", 1);
            shell->last_exit_status = 1;
            return;
        }
        i++;
    }
    
    // Fork and execute all commands
    pid_t children_ids[cmd_count];
    current_command = cmd_list;
    command_index = 0;
    
    while (current_command)
    {
        children_ids[command_index] = fork();
        
        if (children_ids[command_index] < 0)
        {
            // Fork failed - cleanup
            int j = 0;
            while (j < pipes_count)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }
            int k = 0;
            while (k < command_index)
            {
                kill(children_ids[k], SIGKILL);
                waitpid(children_ids[k], NULL, 0);
                k++;
            }
            perror("minishell: fork");
            shell->last_exit_status = 1;
            return;
        }
        
        if (children_ids[command_index] == 0)  // Child process
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			
			// Setup pipe connections
			if (pipes_count > 0)
			{
				if (command_index == 0)
				{
					if (dup2(pipes[0][1], STDOUT_FILENO) == -1)
					{
						perror("minishell: dup2");
						exit(1);
					}
				}
				else if (command_index == cmd_count - 1)
				{
					if (dup2(pipes[command_index - 1][0], STDIN_FILENO) == -1)
					{
						perror("minishell: dup2");
						exit(1);
					}
				}
				else
				{
					if (dup2(pipes[command_index - 1][0], STDIN_FILENO) == -1)
					{
						perror("minishell: dup2");
						exit(1);
					}
					if (dup2(pipes[command_index][1], STDOUT_FILENO) == -1)
					{
						perror("minishell: dup2");
						exit(1);
					}
				}
			}
			
			// Close all pipes
			i = 0;
			while (i < pipes_count)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				i++;
			}
			
			//write(2, "  Applying redirections\n", 25);
			apply_redirs_single(current_command);
			
			//write(2, "  About to execute\n", 19);
            // Check if command exists
            if (!current_command->args || !current_command->args[0])
                exit(0);
            // Execute command
            if (is_builtin(current_command->args[0]))
            {
                int exit_code = run_builtin(current_command->args, shell, &data);
                exit(exit_code);
            }
            else
            {
                char *path = get_command_path(current_command->args[0], shell->envp);
                
                if (!path)
                {
                    write(2, "minishell: ", 11);
                    write(2, current_command->args[0], ft_strlen(current_command->args[0]));
                    write(2, ": command not found\n", 20);
                    exit(127);
                }
                
                if (!ft_strcmp(path, "PERMISSION_DENIED"))
                {
                    write(2, "minishell: ", 11);
                    write(2, current_command->args[0], ft_strlen(current_command->args[0]));
                    write(2, ": Permission denied\n", 20);
                    exit(126);
                }
                
                execve(path, current_command->args, shell->envp);
                
                // If execve returns, it failed
                write(2, "minishell: ", 11);
                perror(current_command->args[0]);
                exit(126);
            }
            
            // Safety exit - should never reach here
            exit(1);
        }
        
        // Parent continues
        current_command = current_command->next;
        command_index++;
    }
    // Parent closes all pipes
    i = 0;
    while (i < pipes_count)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }    
    // Wait for all children
    int status;
    int j = 0;
    while (j < cmd_count)
    {
        if (waitpid(children_ids[j], &status, 0) != -1)
        {
            // Only capture exit status of last command
            if (j == cmd_count - 1)
            {
                if (WIFEXITED(status))
                    shell->last_exit_status = WEXITSTATUS(status);
                else if (WIFSIGNALED(status))
                    shell->last_exit_status = 128 + WTERMSIG(status);
            }
        }
        j++;
    }
}
