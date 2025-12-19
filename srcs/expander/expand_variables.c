/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 21:22:31 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/19 02:38:43 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_var_name_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && is_valid_var_char(str[len]))
		len++;
	return (len);
}

char	*expand_exit_status(char **result, int *i, t_shell *shell)
{
	char	*status_str;
	char	*temp;

	status_str = ft_itoa(shell->last_exit_status);
	if (!status_str)
		return (NULL);
	temp = ft_strjoin(*result, status_str);
	free(status_str);
	free(*result);
	*i += 2;
	return (temp);
}

char	*expand_env_var(char **result, char *str, int *i, t_shell *shell)
{
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*temp;

	(*i)++;
	var_len = get_var_name_len(str + *i);
	if (var_len == 0)
	{
		temp = ft_strjoin(*result, "$");
		return (free(*result), temp);
	}
	var_name = ft_substr(str, *i, var_len);
	if (!var_name)
		return (NULL);
	var_value = get_env_value(var_name, shell->envp);
	free(var_name);
	if (var_value)
	{
		temp = ft_strjoin(*result, var_value);
		free(*result);
		*result = temp;
	}
	*i += var_len;
	return (*result);
}

int	should_expand(char *str, int i)
{
	int	in_single_quote;
	int	j;

	in_single_quote = 0;
	j = 0;
	while (j < i)
	{
		if (str[j] == '\'' && (j == 0 || str[j - 1] != '\\'))
			in_single_quote = !in_single_quote;
		j++;
	}
	if (in_single_quote)
		return (0);
	if (i > 0 && str[i - 1] == '\\')
		return (0);
	return (1);
}
