/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:14 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/23 19:30:21 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_HOME_path(char **envp)
{
    int	i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "HOME=", 5) == 0)
            return (ft_strdup(envp[i] + 5));
        i++;
    }
    return (NULL);
}

int get_path_index(char **envp, char *key)
{
    int i = 0;
    int key_len = ft_strlen(key);

    while (envp[i])
    {
        /* Case 1: KEY=VALUE */
        if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
            return i;

        /* Case 2: KEY (no value) */
        if (ft_strcmp(envp[i], key) == 0)
            return i;

        i++;
    }
    return -1;
}

void free_2d(char **arr)
{
    int i;
    
    i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void	set_env(char *key, char *path, t_shell *shell)
{
    char	*temp_join;
    char	*final_join;
    int		index;
    
/* Case 1: export KEY  → path == NULL  → store only "KEY" */
	if (path == NULL)
	{
		final_join = ft_strdup(key);
		if (!final_join)
			return;
	}
	/* Case 2: export KEY=VALUE → build KEY=VALUE */
	else
	{
		temp_join = ft_strjoin(key, "=");
		if (!temp_join)
			return;
		final_join = ft_strjoin(temp_join, path);
		free(temp_join);
		if (!final_join)
			return;
	}

    index = get_path_index(shell->envp, key);
    if (index != -1)
    {
        free(shell->envp[index]);
        shell->envp[index] = final_join;	
    }
    else
    {
        char	**new_envp;
        int		i;
        int		size;
        
        size = 0;
        while (shell->envp[size])
            size++;
        new_envp = malloc(sizeof(char *) * (size + 2));
        if (!new_envp)
        {
            free(final_join);
            return ;
        }
        i = 0;
        while (i < size)
        {	
            new_envp[i] = ft_strdup(shell->envp[i]);
            if (!new_envp[i])
            {
                while (--i >= 0)
                    free(new_envp[i]);
                free(new_envp);
                free(final_join);
                return ;
            }
            i++;
        }
        new_envp[size] = final_join;
        new_envp[size + 1] = NULL;
        free_2d(shell->envp);
        shell->envp = new_envp;
    }
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
    {
        char *HOME_path;
        char *old_PWD;
        char *new_PWD;

        HOME_path = get_HOME_path(shell->envp);
        if (!HOME_path)
        {
            printf("minishell: cd: HOME not set\n");
            shell->last_exit_status = 1;
            return (1);
        }
        old_PWD = getcwd(NULL, 0);
        if (!old_PWD)
        {
            free(HOME_path);
            shell->last_exit_status = 1;
            return (1);
        }
        if (chdir(HOME_path) == -1)
        {
            printf("minishell: cd: %s: %s\n", HOME_path, strerror(errno));
            free(old_PWD);
            free(HOME_path);
            shell->last_exit_status = 1;
            return (1);
        }
        new_PWD = getcwd(NULL, 0);
        if (!new_PWD)
        {
            free(old_PWD);
            free(HOME_path);
            shell->last_exit_status = 1;
            return (1);
        }
        set_env("OLDPWD", old_PWD, shell);
        set_env("PWD", new_PWD, shell);
        free(old_PWD);
        free(new_PWD);
        free(HOME_path);
        shell->last_exit_status = 0;
        return (0);
    }
    if (arg_count == 2)
    {
        char *old_PWD;
        char *new_PWD;

        old_PWD = getcwd(NULL, 0);
        if (!old_PWD)
        {
            shell->last_exit_status = 1;
            return (1);
        }
        if (chdir(args[1]) == -1)
        {
            printf("minishell: cd: %s: %s\n", args[1], strerror(errno));
            free(old_PWD);
            shell->last_exit_status = 1;
            return (1);
        }
        new_PWD = getcwd(NULL, 0);
        if (!new_PWD)
        {
            free(old_PWD);
            shell->last_exit_status = 1;
            return (1);
        }
        set_env("OLDPWD", old_PWD, shell);
        set_env("PWD", new_PWD, shell);
        free(old_PWD);
        free(new_PWD);
        shell->last_exit_status = 0;
        return (0);
    }
    return (0);
}
