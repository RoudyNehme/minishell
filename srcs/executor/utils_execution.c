/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:43:06 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/27 18:08:23 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	count_cmds(t_cmd *cmd)
{
	int count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**get_path(char **envp)
{
	int		i;
	char	*path_str;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_str = envp[i] + 5;
			return (ft_split_path(path_str));
		}
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full;
	char	*tmp;
	int		i;

	// Case: command contains path (relative or absolute)
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (NULL); // file does not exist → command not found

		if (access(cmd, X_OK) != 0)
			return (ft_strdup("PERMISSION_DENIED")); // file exists but cannot execute

		return (ft_strdup(cmd)); // valid executable file
	}

	paths = get_path(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
{
    if (paths[i][0] == '\0')
        tmp = ft_strdup("./");
    else
        tmp = ft_strjoin(paths[i], "/");

    full = ft_strjoin(tmp, cmd);
    free(tmp);

    /* FIX 1 — File exists but is NOT executable */
    if (access(full, F_OK) == 0 && access(full, X_OK) == -1)
    {
        free_split(paths);
        return (ft_strdup("PERMISSION_DENIED"));
    }

    /* FIX 2 — Correctly found an executable */
    if (access(full, X_OK) == 0)
    {
        free_split(paths);
        return (full);
    }

    free(full);
    i++;
}

	free_split(paths);
	return (NULL);
}
