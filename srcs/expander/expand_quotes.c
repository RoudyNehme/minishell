/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:27:08 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/06 15:06:56 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

static int handle_esc(char *s, char *d, int i, int *j)
{
    if (s[i] == '\\' && i + 1 < ft_strlen(s))
    {
        i++;
        d[(*j)++] = s[i];
        return (i + 1);
    }
    d[(*j)++] = s[i];
    return (i + 1);
}

static int handle_quote_char(char *s, char *d, int i, int *j, char *q)
{
    if (is_quote(s[i]) && (i == 0 || s[i - 1] != '\\'))
    {
        if (!*q)
            *q = s[i];
        else if (*q == s[i])
            *q = 0;
        else
            d[(*j)++] = s[i];
        return (i + 1);
    }
    return (-1);
}

char *handle_escapes(char *s)
{
    char *d;
    int i;
    int j;
    char q;
    int result;

    d = malloc(ft_strlen(s) + 1);
    if (!d)
        return (NULL);
    i = 0;
    j = 0;
    q = 0;
    while (s[i])
    {
        result = handle_quote_char(s, d, i, &j, &q);
        if (result != -1)
            i = result;
        else
            i = handle_esc(s, d, i, &j);
    }
    d[j] = '\0';
    return (d);
}
