/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:32:51 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/11 11:34:46 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*handle_operator(char *line, int *i)
{
	if (line[*i] == '|') // concised from if line[*i] == '|' we increment the (*i)++ then we return...
	{
		(*i)++;
		return (create_token(PIPE, "|"));
	}
	else if (line[*i] == '>') // checks if the *i is a redir 
	{
		if (line[*i + 1] == '>') // then here checks the right next char if also the same before incrementing *i and creating a token 
		{
			*i += 2;
			return (create_token(REDIR_APPEND, ">>"));
		}
		(*i)++;
		return (create_token(REDIR_OUT, ">"));
	}
	else if (line[*i] == '<') // same here
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
