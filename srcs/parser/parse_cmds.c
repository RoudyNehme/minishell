/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:12:40 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/10 14:01:26 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_redir(t_token_type type)
{
	return (type == REDIR_APPEND || type == REDIR_IN
		|| type == REDIR_OUT || type == HEREDOC);
}

// creates and adds the redir token
static int	handle_redir_token(t_cmd *cmd, t_token **tokens)
{
	t_token_type	redir_type;

	redir_type = (*tokens)->type; // get the token type (redir in or out, heredoc or append)
	*tokens = (*tokens)->next; // skip to the next (maybe filename)
	if (*tokens && (*tokens)->type == WORD) // checks if the next token is not null and it is a file
	{
		add_redir(&cmd->redirs, create_redir(redir_type, (*tokens)->value)); // adds the redir to cmd->redirs
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
	cmd->args[*i] = dup; // add the dup (malloc'd) string to the args array
	(*i)++;
	*tokens = (*tokens)->next;
	return (1);
}

static int	fill_command_args(t_cmd *cmd, t_token **tokens)
{
	int	i;

	i = 0;
	while (*tokens && (*tokens)->type != PIPE) // loop over the tokens and fill the args accordingly and split on pipes
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
		else // shouldn't enter this but it's set here to be safe
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
