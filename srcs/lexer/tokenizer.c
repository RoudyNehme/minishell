/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:07:42 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/01 13:32:58 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void skip_whitespace(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static void tokenizer_helper(t_token **head, char *line, int *i)
{
	char *word;

	if (is_operator(line[*i]))
		add_token(head, handle_operator(line, i));
	else if (line[*i] == '\'' || line[*i] == '"')
	{
		word = extract_quoted_word(line, i, line[*i]);
		if (word)
		{
			add_token(head, create_token(WORD, word));
			free(word);
		}
	}
	else
	{
		word = extract_word(line, i);
		add_token(head, create_token(WORD, word));
		free(word);
	}
}

t_token *tokenizer(char *line)
{
	t_token *head;
	int i;

	head = NULL;
	i = 0;
	while (line[i])
	{
		skip_whitespace(line, &i);
		if (!line[i])
			break;
		tokenizer_helper(&head, line, &i);
	}
	return (head);
}