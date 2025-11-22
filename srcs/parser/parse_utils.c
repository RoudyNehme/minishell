/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:55:23 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/06 13:42:09 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// create the cmd struct and assign its args redirs and next to NULL (will modify later)
t_cmd *create_cmd(void)
{
	t_cmd	*new;
	
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->redirs = NULL;
	new->next = NULL;
	return (new);
}
// add the cmd at the end of the list where next = null
void add_cmd(t_cmd **head, t_cmd *new)  
{
	t_cmd	*current;

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
// same as create_cmd
t_redir *create_redir(t_token_type type, char *file)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type; // to get which type of redir (passed as param)
	new->file = ft_strdup(file); // here it copies the file name (cat < "in.txt" > "out.txt")
	if (!new->file)
		return (free(new), NULL); // if strdup failed it frees the previously allocated memmory and returns NULL
	new->next = NULL;
	return (new);
}
// like add_cmd jusr for redirections
void add_redir(t_redir **head, t_redir *new)
{
	t_redir	*current;
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
// counts args (only words)
int count_args(t_token *tokens) 
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}
