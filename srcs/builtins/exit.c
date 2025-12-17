/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:32:00 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/17 19:18:18 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_exit_arguments(char **args)
{
    int	i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

static void	cleanup_and_exit(t_shell *shell, t_cleanup_data *data, int code)
{
    if (data)
    {
        if (data->line)
            free(data->line);
        if (data->tokens)
            free_tokens(data->tokens);
        if (data->cmds)
            free_cmds(data->cmds);
    }
    if (shell && shell->envp)
        free_2d(shell->envp);
    exit(code);
}

static void	handle_invalid_arg(char *arg, t_shell *shell, t_cleanup_data *data)
{
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putendl_fd(": numeric argument required", 2);
    cleanup_and_exit(shell, data, 2);
}

int	builtin_exit(char **args, t_shell *shell, t_cleanup_data *data)
{
    int	exit_code;
    int	arg_count;

    ft_putendl_fd("exit", 1);
    arg_count = count_exit_arguments(args);
    if (arg_count == 1)
    {
        exit_code = shell->last_exit_status;
        cleanup_and_exit(shell, data, exit_code);
    }
    if (!is_valid_number(args[1], &exit_code))
        handle_invalid_arg(args[1], shell, data);
    if (arg_count > 2)
    {
        ft_putendl_fd("minishell: exit: too many arguments", 2);
        return (1);
    }
    cleanup_and_exit(shell, data, exit_code);
    return (0);
}
