/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:25:38 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/06 15:26:06 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *append_char(char *result, char c)
{
    char temp[2];
    char *joined;

    temp[0] = c;
    temp[1] = '\0';
    joined = ft_strjoin(result, temp);
    free(result);
    return (joined);
}

static char *process_dollar(char *result, char *str, int *i, t_shell *shell)
{
    if (str[*i + 1] == '?')
        result = expand_exit_status(&result, i, shell);
    else
        result = expand_env_var(&result, str, i, shell);
    return (result);
}

char *expand_variable(char *str, t_shell *shell)
{
    char *result;
    int i;

    result = ft_strdup("");
    if (!result)
        return (NULL);
    i = 0;
    while (str[i])
    {
        if (str[i] == '$' && should_expand(str, i))
        {
            result = process_dollar(result, str, &i, shell);
            if (!result)
                return (NULL);
        }
        else
        {
            result = append_char(result, str[i]);
            i++;
        }
    }
    return (result);
}
