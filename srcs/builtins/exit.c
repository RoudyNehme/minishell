/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:50 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/19 02:32:27 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_no_args(t_shell *shell, t_cleanup_data *data)
{
	cleanup(data->line, data->tokens, data->cmds, shell);
	rl_clear_history();
	if (shell->envp)
		free_2d(shell->envp);
	exit(shell->last_exit_status);
	return (0);
}

static int	handle_too_many_args(t_shell *shell)
{
	ft_putendl_fd("bash: exit: too many arguments", 2);
	shell->last_exit_status = 1;
	return (1);
}

static void	handle_invalid_number(char *arg, t_shell *shell,
									t_cleanup_data *data)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	shell->last_exit_status = 2;
	cleanup(data->line, data->tokens, data->cmds, shell);
	rl_clear_history();
	if (shell->envp)
		free_2d(shell->envp);
	exit(2);
}

static void	handle_valid_exit(long long code, t_shell *shell,
								t_cleanup_data *data)
{
	int	exit_code;

	exit_code = (int)(code % 256);
	if (exit_code < 0)
		exit_code += 256;
	cleanup(data->line, data->tokens, data->cmds, shell);
	rl_clear_history();
	if (shell->envp)
		free_2d(shell->envp);
	exit(exit_code);
}

int	builtin_exit(char **args, t_shell *shell, t_cleanup_data *data)
{
	int			arg_count;
	long long	exit_code;

	printf("exit\n");
	arg_count = count_exit_args(args);
	if (arg_count == 1)
		return (handle_no_args(shell, data));
	if (!ft_is_valid_long_long(args[1], &exit_code))
		handle_invalid_number(args[1], shell, data);
	if (arg_count > 2)
		return (handle_too_many_args(shell));
	handle_valid_exit(exit_code, shell, data);
	return (0);
}
