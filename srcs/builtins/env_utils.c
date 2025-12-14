/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 08:58:08 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/14 08:58:18 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Duplicates the environment variables into a new array.
 * Returns a copy of the environment or NULL on error.
 */
char **dup_env(char **real_env)
{
    int size;
    char **copy_env;
    int i;

    size = 0;
    while (real_env[size])
        size++;
    copy_env = malloc(sizeof(char *) * (size + 1));
    if (!copy_env)
        return (NULL);
    i = 0;
    while (i < size)
    {
        copy_env[i] = ft_strdup(real_env[i]);
        i++;
    }
    copy_env[size] = NULL;
    return (copy_env);
}
