/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:40 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 14:45:10 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_arg_validity(char *arg)
{
	int	index;

	index = 0;
	if (!arg || arg[0] == '\0')
		return (0);
	if (ft_isalpha(arg[index]) || arg[index] == '_')
		index++;
	else
		return (0);
	while (arg[index])
	{
		if (ft_isalpha(arg[index]) || ft_isdigit(arg[index])
			|| arg[index] == '_')
			index++;
		else
			return (0);
	}
	return (1);
}

static char	**create_new_envp(t_shell *shell, int key_index, int size)
{
	char	**new_envp;
	int		old;
	int		new;

	new_envp = malloc(sizeof(char *) * size);
	if (!new_envp)
		return (NULL);
	old = 0;
	new = 0;
	while (shell->envp[old])
	{
		if (old != key_index)
		{
			new_envp[new] = ft_strdup(shell->envp[old]);
			if (!new_envp[new])
			{
				while (--new >= 0)
					free(new_envp[new]);
				return (free(new_envp), NULL);
			}
			new++;
		}
		old++;
	}
	return (new_envp[new] = NULL, new_envp);
}

static int	remove_env_var(t_shell *shell, int key_index)
{
	int		size;
	char	**new_envp;

	size = 0;
	while (shell->envp[size])
		size++;
	new_envp = create_new_envp(shell, key_index, size);
	if (!new_envp)
	{
		shell->last_exit_status = 1;
		return (1);
	}
	free_2d(shell->envp);
	shell->envp = new_envp;
	return (0);
}

static int	process_unset_arg(char *arg, t_shell *shell)
{
	int	key_index;

	if (!check_arg_validity(arg))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", arg);
		shell->last_exit_status = 1;
		return (1);
	}
	key_index = get_path_index(shell->envp, arg);
	if (key_index != -1)
		return (remove_env_var(shell, key_index));
	return (0);
}

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;

	if (!args || !args[1])
	{
		shell->last_exit_status = 0;
		return (0);
	}
	shell->last_exit_status = 0;
	i = 1;
	while (args[i])
	{
		process_unset_arg(args[i], shell);
		i++;
	}
	return (shell->last_exit_status);
}
