/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:55:19 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 00:02:07 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_cmd *cmd, t_pipeline *pl)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_pipes(pl);
	close_all_pipes(pl);
	apply_redirs_single(cmd);
	execute_child_cmd(cmd, pl);
}

int	fork_all_commands(t_pipeline *pl)
{
	t_cmd	*curr;

	curr = pl->cmd_list;
	pl->current_index = 0;
	while (curr)
	{
		pl->child_pids[pl->current_index] = fork();
		if (pl->child_pids[pl->current_index] < 0)
		{
			cleanup_fork_error(pl);
			return (1);
		}
		if (pl->child_pids[pl->current_index] == 0)
			child_process(curr, pl);
		curr = curr->next;
		pl->current_index++;
	}
	return (0);
}

void	wait_all_children(t_pipeline *pl)
{
	int	status;
	int	j;

	j = 0;
	while (j < pl->cmd_count)
	{
		if (waitpid(pl->child_pids[j], &status, 0) != -1)
		{
			if (j == pl->cmd_count - 1)
			{
				if (WIFEXITED(status))
					pl->shell->last_exit_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					pl->shell->last_exit_status = 128 + WTERMSIG(status);
			}
		}
		j++;
	}
}
