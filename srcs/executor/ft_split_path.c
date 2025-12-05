/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:57:23 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/24 20:05:56 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	count_fields(const char *s)
{
	int count;
	int i;

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
		len = 0;

		/* Count characters until ':' or end */
		while (path[start + len] && path[start + len] != ':')
			len++;

		/* Extract substring for this field */
		result[i] = ft_substr(path, start, len);
		if (!result[i])
			return (free_array(result, i - 1));

		i++;

		/* Move start to next segment */
		if (path[start + len] == ':')
			start = start + len + 1;
		else
			start = start + len;
	}

	result[i] = NULL;
	return (result);
}

