/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:14:29 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/17 19:07:51 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str)
{
    int	i;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int	is_valid_number(const char *str, int *exit_code)
{
    long long	num;

    if (!is_numeric(str))
        return (0);
    num = ft_atoll(str);
    *exit_code = (unsigned char)num;
    return (1);
}

int	is_builtin(char *name)
{
    if (!name)
        return (0);
    if (ft_strcmp(name, "echo") == 0)
        return (1);
    if (ft_strcmp(name, "cd") == 0)
        return (1);
    if (ft_strcmp(name, "pwd") == 0)
        return (1);
    if (ft_strcmp(name, "export") == 0)
        return (1);
    if (ft_strcmp(name, "unset") == 0)
        return (1);
    if (ft_strcmp(name, "env") == 0)
        return (1);
    if (ft_strcmp(name, "exit") == 0)
        return (1);
    return (0);
}

int	run_builtin(char **args, t_shell *shell, t_cleanup_data *data)
{
    if (!args || !args[0])
        return (0);
    if (!ft_strcmp(args[0], "echo"))
        return (builtin_echo(args));
    if (!ft_strcmp(args[0], "pwd"))
        return (builtin_pwd());
    if (!ft_strcmp(args[0], "cd"))
        return (builtin_cd(args, shell));
    if (!ft_strcmp(args[0], "env"))
        return (builtin_env(shell));
    if (!ft_strcmp(args[0], "export"))
        return (builtin_export(args, shell));
    if (!ft_strcmp(args[0], "unset"))
        return (builtin_unset(args, shell));
    if (!ft_strcmp(args[0], "exit"))
        return (builtin_exit(args, shell, data));
    return (0);
}
