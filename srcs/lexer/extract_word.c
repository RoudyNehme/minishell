/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:01:14 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/05 13:39:11 by rnehme           ###   ########.fr       */
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
	while (line[*i] && !is_seperator(line[*i]) && line[*i] != '\'' && line[*i] != '"') // keep looping as long as *i is not a seperator
	{
		if(line[*i] == '\\' && line[*i + 1])
			(*i) += 2; // skip backlash and next char
		else
			(*i)++;
	}
	len = *i - start; // getting word length 
	word = malloc(len + 1); // allocating mem +1 for null terminator
	if (!word)
		return (NULL);
	ft_strncpy(word, line + start, len); // here line + start is creating a new pointer that points to the character at [start pos]
	word[len] = '\0';
	return (word);
}

static void	handle_escape_in_quotes(char *line, int *i, char quote)
{
	// handle escape in double quotes only
	if (quote == '"' && line[*i] == '\\' && line[*i + 1])
	{
		// escapes $ " \ `
		if (line[*i + 1] == '$' || line[*i + 1] == '"'
			|| line[*i + 1] == '\\' || line[*i + 1] == '`')
			(*i) += 2; // skip backslash and escaped char
		else
			(*i)++; // backslash is literal
	}
	else
		(*i)++;
}

char	*extract_quoted_word(char *line, int *i, char quote)
{
	int		start;
	int		len;
	char	*word;
	int		j;

	start = *i;
	(*i)++; // skip opening quote

	while (line[*i] && line[*i] != quote) // loop until end of line or ending quote
		handle_escape_in_quotes(line, i, quote);
	if (!line[*i])
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (NULL);
	}
	(*i)++;
	len = *i - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = line[start + j];
		j++;
	}
	word[len] = '\0';
	return (word);
}
