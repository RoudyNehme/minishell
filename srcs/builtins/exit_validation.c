/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:03:03 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/18 23:47:35 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_valid_long_long(char *str, long long *result)
{
    int	i;
    int	sign;

    i = 0;
    sign = 1;
    *result = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    if (!str[i] || !ft_isdigit(str[i]))
        return (0);
    while (str[i] && ft_isdigit(str[i]))
    {
        *result = *result * 10 + (str[i] - '0');
        i++;
    }
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i])
        return (0);
    *result *= sign;
    return (1);
}
