/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:32:51 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/05 17:44:23 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

t_token	*handle_operator(char *line, int *i)
{
	if (line[*i++] == '|') // concised from if line[*i] == '|' we increment the (*i)++ then we return...
		return (create_token(PIPE, "|"));
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
		{
			*i += 2;
			return (create_token(REDIR_APPEND, ">>"));
		}
		(*i)++;
		return (create_token(REDIR_OUT, ">"));
	}
	else if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
		{
			*i += 2;
			return (create_token(HEREDOC, "<<"));
		}
		(*i)++;
		return (create_token(REDIR_IN, "<"));
	}
	return (NULL);
}
