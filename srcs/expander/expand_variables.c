/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:18:33 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/19 15:21:55 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int get_env_var_len(char *str)
{
    int len;
    
    len = 0;
    while(str[len])
        len++;
    return len;
}

char *expan_var(char *str, t_shell *shell)
{
    int len;
    int i = 0;
    while(str[i])
    {
        if(str[i] == '$')
        {
            i++;
            len = ft_strlen(str);
            while(shell->envp[i])
            {
                if(ft_strncmp(shell->envp[i], get_env_var_len(str), len) == 0)
                    return shell->envp[i] + len + 1;
                i++;
            }
        }
        i++;
    }
}

int main(void)
{
    t_shell shell;

    // fake environment variables
    char *envp[] = {
        "USER=johndoe",
        "HOME=/home/johndoe",
        "PATH=/usr/bin:/bin",
        "SHELL=/bin/bash",
        NULL};

    shell.envp = envp;

    printf("Input: $USER → %s\n", expan_var("$USER", &shell));
    printf("Input: $HOME → %s\n", expan_var("$HOME", &shell));
    printf("Input: $PATH → %s\n", expan_var("$PATH", &shell));
    printf("Input: $SHELL → %s\n", expan_var("$SHELL", &shell));
    printf("Input: $NOTHING → %s\n", expan_var("$NOTHING", &shell));

    return 0;
}
