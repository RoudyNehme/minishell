/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:42:58 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/04 19:14:20 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parse(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*new_cmd;

	cmds = NULL;
	while (tokens)
	{
		new_cmd = parse_command(&tokens);
		if (!new_cmd)
			return (free_cmds(cmds), NULL);
		add_cmd(&cmds, new_cmd);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}
