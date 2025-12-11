/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:27:08 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/11 17:10:08 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int handle_char(char *s, char *d, int i, int *j, char *q)
{
	if (s[i] == '\\' && i + 1 < ft_strlen(s)) // handle escape
	{
		i++; // skip the backslash
		d[(*j)++] = s[i];
		return (i + 1); // return incremented i
	}
	if (is_quote(s[i]) && (i == 0 || s[i - 1] != '\\'))
	{
		if (!*q)
			*q = s[i]; // open quote
		else if (*q == s[i])
			*q = 0; // close quote
		else
			d[(*j)++] = s[i]; // inside other quote type: copy char
		return (i + 1);
	}
	d[(*j)++] = s[i];
	return (i + 1);
}

char *handle_escapes(char *s)
{
	char	*d;
	int		i;
	int		j;
	char	q;

	d = malloc(ft_strlen(s) + 1);
	if (!d)
		return (NULL);
	i = 0;
	j = 0;
	q = 0;
	while (s[i])
		i = handle_char(s, d, i, &j, &q);
	d[j] = '\0';
	return (d);
}
