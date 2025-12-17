/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:54:17 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 00:13:16 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_first_cmd(t_pipeline *pl)
{
	if (dup2(pl->pipes[0][1], STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		exit(1);
	}
}

void	setup_last_cmd(t_pipeline *pl)
{
	if (dup2(pl->pipes[pl->current_index - 1][0], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		exit(1);
	}
}

void	setup_middle_cmd(t_pipeline *pl)
{
	if (dup2(pl->pipes[pl->current_index - 1][0], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		exit(1);
	}
	if (dup2(pl->pipes[pl->current_index][1], STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		exit(1);
	}
}

void	setup_child_pipes(t_pipeline *pl)
{
	if (pl->pipes_count <= 0)
		return ;
	if (pl->current_index == 0)
		setup_first_cmd(pl);
	else if (pl->current_index == pl->cmd_count - 1)
		setup_last_cmd(pl);
	else
		setup_middle_cmd(pl);
}
