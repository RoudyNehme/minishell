/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:38:31 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 00:00:01 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pipeline(t_pipeline *pl, t_cmd *cmd_list, t_shell *shell)
{
	pl->cmd_count = count_cmds(cmd_list);
	pl->pipes_count = pl->cmd_count - 1;
	pl->current_index = 0;
	pl->shell = shell;
	pl->cmd_list = cmd_list;
}

void	execute_pipeline(t_cmd *cmd_list, t_shell *shell, char *line,
	t_token *tokens)
{
	t_pipeline	pl;

	(void)line;
	(void)tokens;
	init_pipeline(&pl, cmd_list, shell);
	if (create_pipes_pl(&pl) == -1)
		return ;
	setup_ignore_signals();
	if (fork_all_commands(&pl) != 0)
	{
		setup_interactive_signals();
		shell->last_exit_status = 1;
		return ;
	}
	close_all_pipes(&pl);
	wait_all_children(&pl);
	setup_interactive_signals();
}
