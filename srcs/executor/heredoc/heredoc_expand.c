/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:08:22 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 16:04:06 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*hd_expand_exit_status(char *expanded, t_shell *shell, int *i)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(shell->last_exit_status);
	tmp = ft_strjoin(expanded, status);
	free(expanded);
	free(status);
	*i += 2;
	return (tmp);
}

static char	*hd_expand_variable(char *expanded, char *line, int *i,
		char **envp)
{
	int		start;
	char	*var_name;
	char	*value;
	char	*tmp;

	start = *i + 1;
	*i = start;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	var_name = ft_substr(line, start, *i - start);
	value = get_env_value(var_name, envp);
	if (value)
		tmp = ft_strjoin(expanded, value);
	else
		tmp = ft_strdup(expanded);
	free(expanded);
	free(var_name);
	return (tmp);
}

static char	*hd_expand_regular_char(char *expanded, char c)
{
	char	str[2];
	char	*tmp;

	str[0] = c;
	str[1] = '\0';
	tmp = ft_strjoin(expanded, str);
	free(expanded);
	return (tmp);
}

char	*expand_heredoc_line(char *line, t_shell *shell)
{
	int		i;
	char	*expanded;

	i = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
			expanded = hd_expand_exit_status(expanded, shell, &i);
		else if (line[i] == '$' && line[i + 1] != '\0'
			&& (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
			expanded = hd_expand_variable(expanded, line, &i, shell->envp);
		else
		{
			expanded = hd_expand_regular_char(expanded, line[i]);
			i++;
		}
	}
	return (expanded);
}
