/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:32 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 11:43:55 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Handle the case of no arguments to export.
 * Prints current environment variables, sorted.
 */
static void	export_no_args(t_shell *shell)
{
	print_export(shell->envp); /* Utility function */
	shell->last_exit_status = 0;
}

/**
 * Handle a single export argument, checking for validity, extracting key/value
 * and setting it in the environment.
 */
static int	handle_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;

	if (!check_arg_validity_export(arg)) /* Utility function */
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	key = get_key(arg);		/* Utility function */
	value = get_value(arg); /* Utility function */
	if (!key)
		return (1);
	set_env(key, value, shell);
	free(key);
	if (value)
		free(value);
	return (0);
}

/**
 * The export built-in. If no arguments are provided, print sorted envp.
 * For arguments, validate and set environment variables.
 */
int	builtin_export(char **args, t_shell *shell)
{
	int	i;

	if (!args || !args[1])
	{
		export_no_args(shell);
		return (0);
	}
	shell->last_exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (handle_export_arg(args[i], shell))
			shell->last_exit_status = 1;
		i++;
	}
	return (shell->last_exit_status);
}
