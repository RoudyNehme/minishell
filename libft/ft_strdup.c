/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:14:30 by rnehme            #+#    #+#             */
/*   Updated: 2025/10/29 15:41:59 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strdup(const char *s)
{
	int			i;
	int			j;
	char		*dest;

	i = 0;
	j = ft_strlen(s);
	dest = (char *)malloc(sizeof(*dest) * (j + 1));
	while (i < j)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	if (!(dest))
	{
		return (NULL);
	}
	return (dest);
}
