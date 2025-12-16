/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:30:00 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/16 15:30:41 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	update_existing_env(t_shell *shell, int index, char *entry)
{
	free(shell->envp[index]);
	shell->envp[index] = entry;
}

static int	copy_env_entries(char **new_envp, char **old_envp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	append_env(t_shell *shell, char *entry)
{
	char	**new_envp;
	int		size;

	size = 0;
	while (shell->envp[size])
		size++;
	new_envp = malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
	{
		free(entry);
		return ;
	}
	if (!copy_env_entries(new_envp, shell->envp, size))
	{
		free(entry);
		return ;
	}
	new_envp[size] = entry;
	new_envp[size + 1] = NULL;
	free_2d(shell->envp);
	shell->envp = new_envp;
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
