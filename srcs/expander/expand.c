/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:18:02 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/02 10:32:09 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int should_expand_redirs(t_token_type type)
{
	return(type == REDIR_APPEND
			|| type == REDIR_IN
			|| type == REDIR_OUT);
}

static char *expand_arg(char *arg, t_shell *shell)
{
	char	*expanded;
	char	*no_quotes;
	
	expanded = expand_variable(arg, shell);
	if (!expanded)
		return (NULL);
	no_quotes = remove_quote(expanded);
	free(expanded);
	return(no_quotes);
}

static void expand_command_args(t_cmd *cmds, t_shell *shell)
{
	char	*expanded;
	int		i;

	i = 0;
	while(cmds->args[i])
	{
		expanded = expand_arg(cmds->args[i], shell);
		if(expanded)
		{
			free(cmds->args[i]);
			cmds->args[i] = expanded;
		}
		i++;
	}
}

static void expand_redirections(t_redir *redirs, t_shell *shell)
{
	char	*expanded;
	
	while(redirs)
	{
		if(should_expand_redirs(redirs->type))
		{
			expanded = expand_arg(redirs->file, shell);
			if(expanded)
			{
				free(redirs->file);
				redirs->file = expanded;
			}
		}
		redirs = redirs->next;
	}
}
// main expansion func
void expand_commands(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	
	current = cmds;
	while(current)
	{
		expand_command_args(current, shell);
		if(current->redirs)
			expand_redirections(current->redirs, shell);
		current = current->next;
	}
}
