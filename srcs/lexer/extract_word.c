/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:01:14 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/06 10:58:24 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_seperator(char c) // returns 1 if c is any of the seperators 
{
	return (c == ' ' || c == '\t' || c == '|' || c == '>'
		|| c == '<' || c == '\0');
}

char	*extract_word(char *line, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	while (!is_seperator(line[*i])) // keep looping as long as *i is not a seperator
		(*i)++;
	len = *i - start; // getting word length 
	word = malloc(sizeof(len + 1)); // allocating mem +1 for null terminator
	if (!word)
		return (NULL);
	ft_strncpy(word, line + start, len); // here line + start is creating a new pointer that points to the character at [start pos]
	word[len] = '\0';
	return (word);
}

char	*extract_quoted_word(char *line, int *i, char quote)
{
	int		start;
	int		len;
	char	*word;

	(*i)++; // we skip the first quote
	start = *i;
	while (line[*i] && line[*i] != quote) // keep looping until end of line or the closing quote
		(*i)++;
	if (!line[*i]) // if we reached the end of line and there was not a closing quote
	{
		printf("minishell> syntax error: unclosed quote\n");
		return (NULL);
	}
	len = *i - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strncpy(word, line + start, len); // same as above pointer arithmetic
	word[len] = '\0';
	(*i)++;
	return (word);
}
