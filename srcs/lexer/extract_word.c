/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:01:14 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/16 12:59:23 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_quote(char *line, int *i, char quote)
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

char	*extract_full_word(char *line, int *i)
{
	int		start;
	int		len;
	char	quote;

	start = *i;
	while (line[*i] && !is_seperator(line[*i])) // loop until end of line or if is a separator
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[*i];
			if (!process_quote(line, i, quote))
			{
				ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2); // in case of an unclosed quote
				return (NULL);
			}
		}
		else
			(*i)++; // anything else continue getting the len
	}
	len = *i - start;
	return (ft_substr(line, start, len)); // returns allocated string
}
