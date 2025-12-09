/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:01:14 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/09 11:19:18 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *extract_word(char *line, int *i)
{
	int start;
	int len;
	char *word;

	start = *i;
	while (line[*i] && !is_seperator(line[*i]) && line[*i] != '\'' && line[*i] != '"')
	{
		if (line[*i] == '\\' && line[*i + 1])
			(*i) += 2;
		else
			(*i)++;
	}
	len = *i - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strncpy(word, line + start, len);
	word[len] = '\0';
	return (word);
}

static int process_quote(char *line, int *i, char quote)
{
	(*i)++; // Skip opening quote
	while (line[*i] && line[*i] != quote)
		(*i)++;

	if (line[*i] == quote)
	{
		(*i)++;		// Skip closing quote
		return (1); // Success
	}
	return (0); // Unclosed quote
}

char *extract_full_word(char *line, int *i)
{
	int start;
	int len;
	char quote;

	start = *i;
	while (line[*i] && !is_seperator(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[*i];
			if (!process_quote(line, i, quote))
			{
				ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
				return (NULL);
			}
		}
		else
			(*i)++;
	}
	len = *i - start;
	return (ft_substr(line, start, len));
}
