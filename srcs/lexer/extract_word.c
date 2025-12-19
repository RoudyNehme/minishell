/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:01:14 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/19 02:45:22 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_quote(char *line, int *i, char quote)
{
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

char	*extract_full_word(char *line, int *i)
{
	int		start;
	int		len;
	char	quote;

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
