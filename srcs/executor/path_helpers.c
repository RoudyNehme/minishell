/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:25:50 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 20:28:10 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_direct_path(char *cmd)
{
	if (access(cmd, F_OK) != 0)
		return (NULL);
	if (access(cmd, X_OK) != 0)
		return (ft_strdup("PERMISSION_DENIED"));
	return (ft_strdup(cmd));
}

char	*build_full_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	if (dir[0] == '\0')
		tmp = ft_strdup("./");
	else
		tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*check_path_access(char *full, char **paths)
{
	if (access(full, F_OK) == 0 && access(full, X_OK) == -1)
	{
		free_split(paths);
		return (ft_strdup("PERMISSION_DENIED"));
	}
	if (access(full, X_OK) == 0)
	{
		free_split(paths);
		return (full);
	}
	return (NULL);
}

char	*search_in_paths(char *cmd, char **paths)
{
	int		i;
	char	*full;
	char	*result;

	i = 0;
	while (paths[i])
	{
		full = build_full_path(paths[i], cmd);
		result = check_path_access(full, paths);
		if (result)
			return (result);
		free(full);
		i++;
	}
	free_split(paths);
	return (NULL);
}
