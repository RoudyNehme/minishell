/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:31:18 by rnehme            #+#    #+#             */
/*   Updated: 2025/10/29 15:41:50 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	strlen;
	size_t	str;

	str = 0;
	strlen = ft_strlen (s);
	if (!s)
		return (0);
	while (start < strlen && (str < len && s[start + str]))
		str++;
	ptr = malloc(sizeof(char) * (str + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (start < strlen && i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
