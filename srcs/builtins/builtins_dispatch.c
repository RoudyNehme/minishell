/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:14:29 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/18 17:38:37 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		return (builtin_pwd(shell));
	if (!ft_strcmp(args[0], "cd"))
		return (builtin_cd(args, shell));
	if (!ft_strcmp(args[0], "env"))
		return (builtin_env(shell));
	if (!ft_strcmp(args[0], "export"))
		return (builtin_export(args, shell));
	if (!ft_strcmp(args[0], "unset"))
		return (builtin_unset(args, shell));
	if (!ft_strcmp(args[0], "exit"))
	{
		return (builtin_exit(args, shell, data));
	}
	return (0);
}
