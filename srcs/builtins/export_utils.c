/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:32 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/19 02:35:49 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_arg_validity_export(char *arg)
{
	int	index;

	index = 0;
	if (!arg || arg[0] == '\0')
		return (0);
	if (ft_isalpha(arg[index]) || arg[index] == '_')
		index++;
	else
		return (0);
	while (arg[index] && arg[index] != '=')
	{
		if (ft_isalpha(arg[index]) || ft_isdigit(arg[index])
			|| arg[index] == '_')
			index++;
		else
			return (0);
	}
	return (1);
}

char	*get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	return (ft_strdup(str + i + 1));
}

void	sort_env(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	if (!envp)
		return ;
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
	char	**envp_copy;
	int		i;
	char	*key;
	char	*value;

	envp_copy = dup_env(envp);
	sort_env(envp_copy);
	i = 0;
	while (envp_copy[i])
	{
		key = get_key(envp_copy[i]);
		value = get_value(envp_copy[i]);
		if (value == NULL)
			printf("declare -x %s\n", key);
		else
			printf("declare -x %s=\"%s\"\n", key, value);
		free(key);
		i++;
		if (value)
			free(value);
	}
	free_2d(envp_copy);
}
