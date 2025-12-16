/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:14 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 12:30:17 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int builtin_cd(char **args, t_shell *shell)
// {
// 	int	arg_count;

// 	arg_count = 0;
// 	while (args && args[arg_count])
// 		arg_count++;
// 	if (arg_count > 2)
// 	{
// 		printf("minishell: cd: too many arguments\n");
// 		shell->last_exit_status = 1;
// 		return (1);
// 	}
// 	if (arg_count == 1)
// 	{
// 		char	*HOME_path;
// 		char	*old_PWD;
// 		char	*new_PWD;

// 		HOME_path = get_HOME_path(shell->envp);
// 		if (!HOME_path)
// 		{
// 			printf("minishell: cd: HOME not set\n");
// 			shell->last_exit_status = 1;
// 			return (1);
// 		}
// 		old_PWD = getcwd(NULL, 0);
// 		if (!old_PWD)
// 		{
// 			free(HOME_path);
// 			shell->last_exit_status = 1;
// 			return (1);
// 		}
// 		if (chdir(HOME_path) == -1)
// 		{
// 			printf("minishell: cd: %s: %s\n", HOME_path, strerror(errno));
// 			free(old_PWD);
// 			free(HOME_path);
// 			shell->last_exit_status = 1;
// 			return (1);
// 		}
// 		new_PWD = getcwd(NULL, 0);
// 		if (!new_PWD)
// 		{
// 			free(old_PWD);
// 			free(HOME_path);
// 			shell->last_exit_status = 1;
// 			return (1);
// 		}
// 		set_env("OLDPWD", old_PWD, shell);
// 		set_env("PWD", new_PWD, shell);
// 		free(old_PWD);
// 		free(new_PWD);
// 		free(HOME_path);
// 		shell->last_exit_status = 0;
// 		return (0);
// 	}
// 	if (arg_count == 2)
// 	{
// 		char	*old_PWD;
// 		char	*new_PWD;

// 		old_PWD = getcwd(NULL, 0);
// 		if (!old_PWD)
// 		{
// 			shell->last_exit_status = 1;
// 			return (1);
// 		}
// 		if (chdir(args[1]) == -1)
// 		{
// 			printf("minishell: cd: %s: %s\n", args[1], strerror(errno));
// 			free(old_PWD);
// 			shell->last_exit_status = 1;
// 			return (1);
// 		}
// 		new_PWD = getcwd(NULL, 0);
// 		if (!new_PWD)
// 		{
// 			free(old_PWD);
// 			shell->last_exit_status = 1;
// 			return (1);
// 		}
// 		set_env("OLDPWD", old_PWD, shell);
// 		set_env("PWD", new_PWD, shell);
// 		free(old_PWD);
// 		free(new_PWD);
// 		shell->last_exit_status = 0;
// 		return (0);
// 	}
// 	return (0);
// }

static int	change_directory_and_update(char *path, t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (shell->last_exit_status = 1, 1);
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		free(old_pwd);
		return (shell->last_exit_status = 1, 1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(old_pwd);
		return (shell->last_exit_status = 1, 1);
	}
	set_env("OLDPWD", old_pwd, shell);
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
	free(home_path);
	return (ret);
}

static int	cd_to_path(char *path, t_shell *shell)
{
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
