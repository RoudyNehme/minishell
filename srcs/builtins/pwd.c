/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:20:15 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/18 17:20:17 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(t_shell *shell)
{
    char	*pwd;
    char	*pwd_env;

    pwd = getcwd(NULL, 0);
    if (pwd)
    {
        printf("%s\n", pwd);
        free(pwd);
        return (0);
    }
    pwd_env = get_env_value("PWD", shell->envp);
    if (pwd_env)
    {
        printf("%s\n", pwd_env);
        return (0);
    }
    return (1);
}