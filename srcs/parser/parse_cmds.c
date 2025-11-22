/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:12:40 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/18 19:14:03 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir(t_token_type type)
{
	return (type == REDIR_APPEND || type == REDIR_IN
		|| type == REDIR_OUT || type == HEREDOC);
}

// creates and adds the redir token
static int	handle_redir_token(t_cmd *cmd, t_token **tokens)
{
	t_token_type	redir_type;

	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == WORD) // checks if the next token is not null and it is a file
	{
		add_redir(&cmd->redirs, create_redir(redir_type, (*tokens)->value));
		*tokens = (*tokens)->next;
		return (1);
	}
	printf("minishell: error smth near redir\n");
	return (0);
}

static int	handle_word_token(t_cmd *cmd, int *i, t_token **tokens)
{
	char	*dup;

	dup = ft_strdup((*tokens)->value);
	if (!dup)
	{
		cmd->args[*i] = NULL;
		return (0);
	}
	cmd->args[*i] = dup;
	(*i)++;
	*tokens = (*tokens)->next;
	return (1);
}

static int	fill_command_args(t_cmd *cmd, t_token **tokens)
{
	int	i;

	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == WORD)
		{
			if (!handle_word_token(cmd, &i, tokens))
				return (0);
		}
		else if (is_redir((*tokens)->type))
		{
			if (!handle_redir_token(cmd, tokens))
			{
				cmd->args[i] = NULL;
				return (0);
			}
		}
		else
			*tokens = (*tokens)->next;
	}
	cmd->args[i] = NULL;
	return (1);
}

t_cmd	*parse_command(t_token **tokens)
{
	t_cmd	*cmd;
	int		arg_count;

	cmd = create_cmd(); // create a cmd struct 
	if (!cmd)
		return (NULL);
	arg_count = count_args(*tokens); // returns the word tokens count
	cmd->args = malloc(sizeof(char *) * (arg_count + 1)); // allocates mem for the array of args and + 1 for NULL (for later when we use the execve)
	if (!cmd->args)
		return (free(cmd), NULL);
	if (!fill_command_args(cmd, tokens)) // filling commands
		return (free_cmds(cmd), NULL);
	return (cmd);
}
