/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:19:54 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/09 10:21:37 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_seperator(char c) // returns 1 if c is any of the seperators
{
	return (c == ' ' || c == '\t' || c == '|' || c == '>' || c == '<' || c == '\0');
}

int is_operator(char c)
{
	return (c == '<' || c == '>');
}

t_token	*create_token(t_token_type token_type, char *value) // create a token
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = token_type;
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), NULL); // if strdup failed it frees the previously allocated memmory and returns NULL
	new->next = NULL;
	return (new);
}

void	add_token(t_token **head, t_token *new) // add token...
{
	t_token	*current;

	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	free_tokens(t_token *head) // free func for tokens
{
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp);
	}
}

void	print_tokens(t_token *head) // debug func
{
	t_token	*current;
	char	*type_str;

	current = head;
	while (current)
	{
		if (current->type == WORD)
			type_str = "WORD";
		else if (current->type == PIPE)
			type_str = "PIPE";
		else if (current->type == REDIR_APPEND)
			type_str = "REDIR_APPEND";
		else if (current->type == HEREDOC)
			type_str = "HEREDOC";
		else if (current->type == REDIR_IN)
			type_str = "REDIR_IN";
		else if (current->type == REDIR_OUT)
			type_str = "REDIR_OUT";
		else
			type_str = "UNKNOWN";
		printf("[%s: \"%s\"] ", type_str, current->value);
		current = current->next;
	}
	printf("\n");
}
