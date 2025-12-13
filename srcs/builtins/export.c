/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:32 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/12 11:25:41 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_arg_validity_export(char *arg)
{
	int index;
	
	index = 0;
	if (!arg || arg[0] == '\0')
    return (0);
	if(ft_isalpha(arg[index]) || arg[index] == '_')
		index++;
	else
		return (0);
	
	while (arg[index] && arg[index] != '=')
	{
		if(ft_isalpha(arg[index]) || ft_isdigit(arg[index]) || arg[index] == '_')
			index++;
		else
			return (0);
	}
	return (1);
}

char *get_key(char *str)
{
    int i = 0;
    while (str[i] && str[i] != '=')
        i++;

    return ft_substr(str, 0, i);
}

char *get_value(char *str)
{
	int i = 0;

	while (str[i] && str[i] != '=')
		i++;

	if (str[i] == '\0')
		return (NULL);

	return ft_strdup(str + i + 1);
}

void    sort_env(char **envp)
{
    int     i;
    int     j;
    char    *tmp;

    if (!envp)
        return;

    i = 0;
    while (envp[i])
    {
        j = i + 1;
        while (envp[j])
        {
            if (ft_strcmp(envp[i], envp[j]) > 0)
            {
                tmp = envp[i];
                envp[i] = envp[j];
                envp[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void	print_export(char **envp)
{
	char **envp_copy;
	envp_copy = dup_env(envp);
	sort_env(envp_copy);

	int i;
	
	i = 0;
	while (envp_copy[i])
{
    char *key = get_key(envp_copy[i]);
    char *value = get_value(envp_copy[i]);  // NULL if no '=' exists

    if (value == NULL)
        printf("declare -x %s\n", key);
    else
        printf("declare -x %s=\"%s\"\n", key, value);
    free(key);
    if (value)
        free(value);
    i++;
}
	free_2d(envp_copy);
}

int builtin_export(char **args, t_shell *shell)
{
    int i = 1;
	
     if (!args || !args[1])  
    {
        print_export(shell->envp);
        shell->last_exit_status = 0;
        return (0);
    }

    shell->last_exit_status = 0;

    while (args[i])
    {
        if (!check_arg_validity_export(args[i]))
        {
            printf("minishell: export: `%s': not a valid identifier\n", args[i]);
            shell->last_exit_status = 1;
        }
        else
        {
			char *key = get_key(args[i]);
			char *value = get_value(args[i]);    // NULL if no '=' present

			if (!key)
			{
				shell->last_exit_status = 1;
				i++;
				continue;
			}
			set_env(key, value, shell);

			free(key);
			if (value)
				free(value);
        }
        i++;
    }
    return shell->last_exit_status;
}
