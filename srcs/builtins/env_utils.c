/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 08:58:08 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/16 14:46:30 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Duplicates the environment variables into a new array.
 * Returns a copy of the environment or NULL on error.
 */
char	**dup_env(char **real_env)
{
	int		size;
	char	**copy_env;
	int		i;

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

/* Builds either "KEY" or "KEY=VALUE" */
static char	*build_env_entry(char *key, char *path)
{
	char	*temp;
	char	*final;

	if (path == NULL)
		return (ft_strdup(key));
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	final = ft_strjoin(temp, path);
	free(temp);
	return (final);
}

/* Replaces an existing KEY or VALUE in envp */
static void	update_existing_env(t_shell *shell, int index, char *entry)
{
	free(shell->envp[index]);
	shell->envp[index] = entry;
}

static void	append_env(t_shell *shell, char *entry)
{
	t_norminette	n;

	n.size = 0;
	n.i = -1;
	while (shell->envp[n.size])
		n.size++;
	n.new_envp = malloc(sizeof(char *) * (n.size + 2));
	if (!n.new_envp)
		return (free(entry));
	while (++n.i < n.size)
	{
		n.new_envp[n.i] = ft_strdup(shell->envp[n.i]);
		if (!n.new_envp[n.i])
		{
			while (--n.i >= 0)
				free(n.new_envp[n.i]);
			free(n.new_envp);
			return (free(entry));
		}
	}
	n.new_envp[n.size] = entry;
	n.new_envp[n.size + 1] = NULL;
	free_2d(shell->envp);
	shell->envp = n.new_envp;
}

void	set_env(char *key, char *path, t_shell *shell)
{
	char	*entry;
	int		index;

	entry = build_env_entry(key, path);
	if (!entry)
		return ;
	index = get_path_index(shell->envp, key);
	if (index != -1)
		update_existing_env(shell, index, entry);
	else
		append_env(shell, entry);
}
