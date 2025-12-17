/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:50 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 11:44:51 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_no_args(t_shell *shell, t_cleanup_data *data)
{
	cleanup(data->line, data->tokens, data->cmds, shell);
	exit(shell->last_exit_status);
	return (0);
}

static int	handle_too_many_args(t_shell *shell)
{
	printf("minishell: exit: too many arguments\n");
	shell->last_exit_status = 1;
	return (1);
}

static void	handle_invalid_number(char *arg, t_shell *shell,
									t_cleanup_data *data)
{
	printf("minishell: exit: %s: numeric argument required\n", arg);
	shell->last_exit_status = 2;
	cleanup(data->line, data->tokens, data->cmds, shell);
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
