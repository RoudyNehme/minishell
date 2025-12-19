/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:32:51 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/19 02:44:43 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*handle_redirect_out(char *line, int *i)
{
	if (line[*i + 1] == '>')
	{
		*i += 2;
		return (create_token(REDIR_APPEND, ">>"));
	}
	(*i)++;
	return (create_token(REDIR_OUT, ">"));
}

static t_token	*handle_redirect_in(char *line, int *i)
{
	if (line[*i + 1] == '<')
	{
		*i += 2;
		return (create_token(HEREDOC, "<<"));
	}
	(*i)++;
	return (create_token(REDIR_IN, "<"));
}

t_token	*handle_operator(char *line, int *i)
{
	if (line[*i] == '<')
		return (handle_redirect_in(line, i));
	else if (line[*i] == '>')
		return (handle_redirect_out(line, i));
	else if (line[*i] == '|')
	{
		(*i)++;
		return (create_token(PIPE, "|"));
	}
	return (NULL);
}
