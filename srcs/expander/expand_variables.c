/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:18:33 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/02 10:36:13 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int get_env_var_len(char *str)
{
	int len;
	
	len = 0;
	while(str[len] && is_valid_char(len))
		len++;
	return (len);
	int len;
	
	len = 0;
	while(str[len] && is_valid_char(len))
		len++;
	return (len);
}

static char *expand_exit_status(char **result, int *i, t_shell *shell)
{
	char *status_str;
	char *temp;
	char *status_str;
	char *temp;

	status_str = ft_itoa(shell->last_exit_status);
	if(!status_str)
		return (NULL);
	temp = ft_strjoin(*result, status_str);
	free(status_str);
	free(*result);
	*i += 2;
	return (temp);
	status_str = ft_itoa(shell->last_exit_status);
	if(!status_str)
		return (NULL);
	
	temp = ft_strjoin(*result, status_str);
	free(status_str);
	free(*result);
	*i += 2;
	return (temp);
}

static char *expand_env_var(char **result, char *str, int *i, t_shell *shell)
{
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*temp;
	
	(*i)++;
	var_len = get_env_var_len(str + *i);
	
	if(var_len == 0)
	{
		temp = ft_strjoin(*result, "$");
		free(*result);
		return (temp);
	}
	var_name = ft_substr(str, *i, var_len);
	if(!var_name)
		return (NULL);
	var_value = get_env_var(var_name, shell->envp);
	free(var_name);
	if(var_value)
	{
		temp = ft_strjoin(*result, var_value);
		free(*result);
		*result = temp;
	}
	*i += var_len;
	return (*result);
	int var_len;
	char *var_name;
	char *var_value;
	char    *temp;
	
	(*i)++;
	var_len = get_env_var_len(str + *i);
	
	if(var_len == 0)
	{
		temp = ft_strjoin(*result, "$");
		free(*result);
		return (temp);
	}
	var_name = ft_substr(str, *i, var_len);
	if(!var_name)
		return (NULL);
	var_value = get_env_var(var_name, shell->envp);
	free(var_name);
	if(var_value)
	{
		temp = ft_strjoin(*result, var_value);
		free(*result);
		*result = temp;
	}
	*i += var_len;
	return (*result);
}

static int should_expand(char *str, int i)
{
	int j;
	int in_quote;
	
	in_quote = 0;
	j = 0;
	
	while(j < i)
	{
		if(str[j] == '\'' && (j == 0 || str[j - 1] != '\\')) // we check for a single quote && that it isn't backslashed
			in_quote = !in_quote; // we set the opposite of the current value that it holds
		j++;
	}
	if(in_quote) // quote flag is true
		return (0);
	if(i > 0 && str[i - 1] == '\\') // checking if $ is backlashed 
		return (0);
	return (1);
	int j;
	int in_quote;
	
	in_quote = 0;
	j = 0;
	
	while(j < i)
	{
		if(str[j] == '\'' && (j == 0 || str[j - 1] != '\\'))
			in_quote = !in_quote;
		j++;
	}
	if(in_quote)
		return (0);
	if(i > 0 && str[i - 1] == '\\')
		return (0);
	return (1);
}

char *expand_variable(char *str, t_shell *shell)
{
	char	*result;
	int		i;
	char	temp[2];
	
	result = ft_strdup("");
	if(!result)
		return (NULL);
	i = 0;
	while(str[i])
	{
		if(str[i] == '$' && should_expand(str, i) && !is_quote(str[i + 1]))
		{
			if(str[i + 1] == '?')
				result = expand_exit_status(&result, &i, shell);
			else
				result = expand_env_var(&result, str, &i, shell);
			if(!result)
				return (NULL);
		}
		else
		{
			temp[0] = str[i];
			temp[1] = '\0';
			char    *joined;
			joined = ft_strjoin(result, temp);
			free(result);
			result = joined;
			i++;
		}
	}
	return (result);
	char *result;
	int i;
	char temp[2];
	
	result = ft_strdup("");
	if(!result)
		return (NULL);
	i = 0;
	while(str[i])
	{
		if(str[i] == '$' && should_expand(str, i) && str[i + 1] != '\'')
		{
			if(str[i + 1] == '?')
				result = expand_exit_status(&result, &i, shell);
			else
				result = expand_env_var(&result, str, &i, shell);
			if(!result)
				return (NULL);
		}
		else
		{
			temp[0] = str[i];
			temp[1] = '\0';
			char    *joined;
			joined = ft_strjoin(result, temp);
			free(result);
			result = joined;
			i++;
		}
	}
	return (result);
}
