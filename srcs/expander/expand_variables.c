/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 21:22:31 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/05 21:22:33 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char get_quote_type(char *str)
{
	int len;

	if (!str || !*str)
		return (0);

	len = ft_strlen(str);

	// Check if starts and ends with same quote
	if (len >= 2)
	{
		if (str[0] == '\'' && str[len - 1] == '\'')
			return ('\'');
		if (str[0] == '"' && str[len - 1] == '"')
			return ('"');
	}

	return (0); // No quotes
}

// Remove outer quotes (first and last character)
static char *remove_outer_quotes(char *str)
{
	int len;
	char *result;
	int i;

	len = ft_strlen(str);

	// String must be at least 2 chars and start/end with quotes
	if (len < 2 || !get_quote_type(str))
		return (ft_strdup(str));

	// Allocate without first and last char
	result = malloc(len - 1);
	if (!result)
		return (NULL);

	i = 0;
	while (i < len - 2)
	{
		result[i] = str[i + 1];
		i++;
	}
	result[len - 2] = '\0';

	return (result);
}

static int get_env_var_len(char *str)
{
	int len;
	
	len = 0;
	while(str[len] && is_valid_char(str[len]))
		len++;
	return (len);
}

static char *expand_exit_status(char **result, int *i, t_shell *shell)
{
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
}

static char *expand_env_var(char **result, char *str, int *i, t_shell *shell)
{
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*temp;
	
	(*i)++; // skip the $
	var_len = get_env_var_len(str + *i); // get the len of the variable (after the $)
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

static char *expand_vars_in_string(char *str, t_shell *shell)
{
	char *result;
	int i;
	char temp[2];
	char *joined;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		// Check for escaped $
		if (str[i] == '\\' && str[i + 1] == '$')
		{
			temp[0] = '$';
			temp[1] = '\0';
			joined = ft_strjoin(result, temp);
			free(result);
			result = joined;
			i += 2;
		}
		// Check for $ expansion
		else if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				result = expand_exit_status(&result, &i, shell);
			else
				result = expand_env_var(&result, str, &i, shell);

			if (!result)
				return (NULL);
		}
		// Regular character
		else
		{
			temp[0] = str[i];
			temp[1] = '\0';
			joined = ft_strjoin(result, temp);
			free(result);
			result = joined;
			i++;
		}
	}
	return (result);
}

// Expand variables based on quote type
char *expand_variable(char *str, t_shell *shell)
{
	char quote_type;
	char *without_quotes;
	char *expanded;

	quote_type = get_quote_type(str);
	// Case 1: Single quotes - NO expansion, just remove quotes
	if (quote_type == '\'')
		return (remove_outer_quotes(str));
	// Case 2: Double quotes - expand, then remove quotes
	if (quote_type == '"')
	{
		without_quotes = remove_outer_quotes(str);
		if (!without_quotes)
			return (NULL);
		expanded = expand_vars_in_string(without_quotes, shell);
		free(without_quotes);
		return (expanded);
	}
	// Case 3: No quotes - expand normally
	return (expand_vars_in_string(str, shell));
}
