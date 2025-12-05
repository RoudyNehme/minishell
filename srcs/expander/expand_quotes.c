/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:27:08 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/05 13:52:52 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *handle_escapes(char *str)
{
    int i;
    char *result;
    int j;

    result = malloc(ft_strlen(str) + 1); // malloc'd string for the size of str plus null terminator
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '\\' && str[i + 1]) // 
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
