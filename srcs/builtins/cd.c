/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:14 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/13 16:08:31 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Builds either "KEY" or "KEY=VALUE" */
static char *build_env_entry(char *key, char *path)
{
	char *temp;
	char *final;

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
static void update_existing_env(t_shell *shell, int index, char *entry)
{
	free(shell->envp[index]);
	shell->envp[index] = entry;
}

typedef struct s_norminette // afyad brilliant suggestion XD
{
	char **new_envp;
	int size;
	int i;
} t_norminette;

static void append_env(t_shell *shell, char *entry)
{
	t_norminette n;

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

void set_env(char *key, char *path, t_shell *shell)
{
	char	*entry;
	int		index;

	entry = build_env_entry(key, path);
	if (!entry)
		return;
	index = get_path_index(shell->envp, key);
	if (index != -1)
		update_existing_env(shell, index, entry);
	else
		append_env(shell, entry);
}

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

static int change_directory_and_update(char *path, t_shell *shell)
{
	char *old_pwd;
	char *new_pwd;

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

static int cd_to_home(t_shell *shell)
{
	char *home_path;
	int ret;

	home_path = get_HOME_path(shell->envp);
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

static int cd_to_path(char *path, t_shell *shell)
{
	return (change_directory_and_update(path, shell));
}

int builtin_cd(char **args, t_shell *shell)
{
	int arg_count;

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
