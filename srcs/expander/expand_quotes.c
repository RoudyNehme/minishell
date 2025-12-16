/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:27:08 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/16 14:35:04 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	should_open_or_close_quote(char *s, int i, char *q)
{
	if (is_quote(s[i]) && (i == 0 || s[i - 1] != '\\'))
	{
		if (!*q)
			*q = s[i];
		else if (*q == s[i])
			*q = 0;
		else
			return (0);
		return (1);
	}
	return (0);
}

static int	handle_char(char *s, char *d, int i, int *j)
{
	static char	q = 0;

	if (s[i] == '\\' && i + 1 < ft_strlen(s))
	{
		i++;
		d[(*j)++] = s[i];
		return (i + 1);
	}
	if (should_open_or_close_quote(s, i, &q))
		return (i + 1);
	d[(*j)++] = s[i];
	return (i + 1);
}

char	*handle_escapes(char *s)
{
	char	*d;
	int		i;
	int		j;

	d = malloc(ft_strlen(s) + 1);
	if (!d)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
		i = handle_char(s, d, i, &j);
	d[j] = '\0';
	return (d);
}
