/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:27:08 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/28 00:42:41 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *remove_quote(char *str)
{
    int i;
    char *result;
    char quote_flag;
    int j;

    quote_flag = 0;
    result = malloc(ft_strlen(str) + 1);
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (is_quote(str[i]) && (i == 0 || str[i - 1] != '\\')) // we make sure it's the start of the string so we don't check for i - 1 (otherwise we'd be checking out of bounds)
        {
            if (!quote_flag)
                quote_flag = str[i];
            else if (quote_flag == str[i])
                quote_flag = 0;
            else
                result[j++] = str[i];
        }
        else if (str[i] == '\\' && i + 1 < ft_strlen(str))
        {
            i++;
            result[j++] = str[i];
        }
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}
