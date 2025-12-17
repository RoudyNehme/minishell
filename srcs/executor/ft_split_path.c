/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:57:23 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 20:33:18 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_fields(const char *s)
{
	int	count;
	int	i;

	if (!s || *s == '\0')
		return (1);
	count = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == ':')
			count++;
		i++;
	}
	return (count);
}

static char	**free_array(char **arr, int n)
{
	while (n >= 0)
		free(arr[n--]);
	free(arr);
	return (NULL);
}

static int	get_field_len(const char *path, int start)
{
	int	len;

	len = 0;
	while (path[start + len] && path[start + len] != ':')
		len++;
	return (len);
}

static int	update_start(const char *path, int start, int len)
{
	if (path[start + len] == ':')
		return (start + len + 1);
	else
		return (start + len);
}

char	**ft_split_path(const char *path)
{
	char	**result;
	int		fields;
	int		i;
	int		start;
	int		len;

	if (!path)
		return (NULL);
	fields = count_fields(path);
	result = malloc(sizeof(char *) * (fields + 1));
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	while (i < fields)
	{
		len = get_field_len(path, start);
		result[i] = ft_substr(path, start, len);
		if (!result[i])
			return (free_array(result, i - 1));
		start = update_start(path, start, len);
		i++;
	}
	result[i] = NULL;
	return (result);
}
