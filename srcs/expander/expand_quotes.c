/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:27:08 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/22 13:26:15 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

char *remove_quote(char *str)
{
    int i;
    char *result;
    char quote_flag;
    int j;

    quote_flag = 0;
    result = malloc(ft_strlen(str) + 1);
    if(!result)
        return (NULL);
    i = 0;
    j = 0;
    while(str[i])
    {
        if(is_quote(str[i]))
        {
            if (!quote_flag)
                quote_flag = str[i];
            else if(quote_flag == str[i])
                quote_flag = 0;
            else
                result[j++] = str[i];
        }
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}

int main()
{
    char *str = "\"Helloo";
    printf("%s\n", remove_quote(str));
}
