/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:14 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/19 02:34:02 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_parent_in_deleted_dir(t_shell *shell)
{
	char	*parent;
	int		can_access;

	parent = get_parent_from_pwd(shell);
	if (!parent)
		return (shell->last_exit_status = 1, 1);
	can_access = (access(parent, F_OK) == 0);
	if (can_access)
	{
		if (chdir(parent) == 0)
		{
			set_env("PWD", parent, shell);
			free(parent);
			return (shell->last_exit_status = 0, 0);
		}
	}
	ft_putendl_fd("cd: error retrieving current directory: getcwd: "
		"cannot access parent directories: No such file or directory", 2);
	set_env("PWD", parent, shell);
	free(parent);
	return (shell->last_exit_status = 1, 1);
}

static int	change_directory_and_update(char *path, t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		free(old_pwd);
		return (shell->last_exit_status = 1, 1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		new_pwd = ft_strdup(path);
	if (old_pwd)
		set_env("OLDPWD", old_pwd, shell);
	if (new_pwd)
		set_env("PWD", new_pwd, shell);
	free(old_pwd);
	free(new_pwd);
	return (shell->last_exit_status = 0, 0);
}

static int	cd_to_home(t_shell *shell)
{
	char	*home_path;
	int		ret;

	home_path = get_home_path(shell->envp);
	if (!home_path)
	{
		printf("minishell: cd: HOME not set\n");
		shell->last_exit_status = 1;
		return (1);
	}
	ret = change_directory_and_update(home_path, shell);
	return (ret);
}

static int	cd_to_path(char *path, t_shell *shell)
{
	char	*current;

	if (ft_strcmp(path, "..") == 0)
	{
		current = getcwd(NULL, 0);
		if (!current)
			return (cd_parent_in_deleted_dir(shell));
		free(current);
	}
	return (change_directory_and_update(path, shell));
}

int	builtin_cd(char **args, t_shell *shell)
{
	int	arg_count;

	arg_count = 0;
	while (args && args[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		printf("minishell: cd: too many arguments\n");
		shell->last_exit_status = 1;
		return (1);
	}
	if (arg_count == 1)
		return (cd_to_home(shell));
	if (arg_count == 2)
		return (cd_to_path(args[1], shell));
	return (0);
}
