/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:32:51 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/16 12:59:04 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*handle_redirect_out(char *line, int *i)
{
	if (line[*i + 1] == '>') // then here checks the right next char if also the same before incrementing *i and creating a token
	{
		*i += 2;
		return (create_token(REDIR_APPEND, ">>"));
	}
	(*i)++;
	return (create_token(REDIR_OUT, ">"));
}

static t_token	*handle_redirect_in(char *line, int *i)
{
	if (line[*i + 1] == '<') // same here
	{
		*i += 2;
		return (create_token(HEREDOC, "<<"));
	}
	(*i)++;
	return (create_token(REDIR_IN, "<"));
}

// old version 
// t_token *handle_operator(char *line, int *i)
// {
// 	if (line[*i] == '|')
// 	{
// 		(*i)++;
// 		return (create_token(PIPE, "|"));
// 	}
// 	else if (line[*i] == '>')
// 		return (handle_redirect_out(line, i));
// 	else if (line[*i] == '<')
// 		return (handle_redirect_in(line, i));
// 	return (NULL);
// }
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
