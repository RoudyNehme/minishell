/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:18:02 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/06 15:26:35 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *expand_arg(char *arg, t_shell *shell)
{
	char *expanded;
	char *no_quotes;

	expanded = expand_variable(arg, shell);
	if (!expanded)
		return (NULL);
	no_quotes = handle_escapes(expanded);
	free(expanded);
	return (no_quotes);
}

static void expand_command_args(t_cmd *cmd, t_shell *shell)
{
	int i;
	char *expanded;

	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_arg(cmd->args[i], shell);
		if (expanded)
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

static int should_expand_redir(t_token_type type)
{
	return (type == REDIR_IN ||
			type == REDIR_OUT ||
			type == REDIR_APPEND);
}

static void expand_redirections(t_redir *redirs, t_shell *shell)
{
	char *expanded;

	while (redirs)
	{
		if (should_expand_redir(redirs->type))
		{
			expanded = expand_arg(redirs->file, shell);
			if (expanded)
			{
				free(redirs->file);
				redirs->file = expanded;
			}
		}
		redirs = redirs->next;
	}
}

void expand_commands(t_cmd *cmds, t_shell *shell)
{
	t_cmd *current;

	current = cmds;
	while (current)
	{
		expand_command_args(current, shell);
		if (current->redirs)
			expand_redirections(current->redirs, shell);
		current = current->next;
	}
}
