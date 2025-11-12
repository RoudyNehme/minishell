/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:42:58 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/11 11:02:10 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// main parse command that takest the whole tokens list
t_cmd	*parse(t_token *tokens) 
{
	t_cmd	*cmds;
	t_cmd	*new_cmd;

	cmds = NULL;
	while (tokens)
	{
		new_cmd = parse_command(&tokens);
		if (!new_cmd)
			return (free_cmds(cmds), NULL); // if parsing command failed we free any already allocated mem cmds then returns NULL for error
		add_cmd(&cmds, new_cmd);
		if (tokens && tokens->type == PIPE) // skipping the pipe as it is not a command 
			tokens = tokens->next;
	}
	return (cmds);
}
