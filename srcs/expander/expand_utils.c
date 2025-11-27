/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:27:29 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/27 23:26:54 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_valid_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

char *get_env_var(char *name, char **envp)
{
    int i;
    int len;
    
    if (!name || !envp)
        return NULL;

    len = ft_strlen(name);
    i = 0;

    while(envp[i])
    {
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1);
        i++;
    }
    return (NULL);
}
