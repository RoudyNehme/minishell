/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:53:54 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 00:11:04 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_created_pipes(t_pipeline *pl, int created)
{
	int	j;

	j = 0;
	while (j < created)
	{
		close(pl->pipes[j][0]);
		close(pl->pipes[j][1]);
		j++;
	}
}

int	create_pipes_pl(t_pipeline *pl)
{
	int	i;

	i = 0;
	while (i < pl->pipes_count)
	{
		if (pipe(pl->pipes[i]) == -1)
		{
			close_created_pipes(pl, i);
			write(2, "minishell: ", 11);
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
			pl->shell->last_exit_status = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

void	close_all_pipes(t_pipeline *pl)
{
	int	i;

	i = 0;
	while (i < pl->pipes_count)
	{
		close(pl->pipes[i][0]);
		close(pl->pipes[i][1]);
		i++;
	}
}

void	cleanup_fork_error(t_pipeline *pl)
{
	int	k;

	close_all_pipes(pl);
	k = 0;
	while (k < pl->current_index)
	{
		kill(pl->child_pids[k], SIGKILL);
		waitpid(pl->child_pids[k], NULL, 0);
		k++;
	}
	perror("minishell: fork");
}
