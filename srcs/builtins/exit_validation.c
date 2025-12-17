/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:11:18 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/16 11:32:39 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parse_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	check_overflow(long long num, int sign, char c)
{
	if (sign == 1 && (num > (LLONG_MAX - (c - '0')) / 10))
		return (0);
	if (sign == -1 && (num > (-(LLONG_MIN + (c - '0'))) / 10))
		return (0);
	return (1);
}

static int	validate_and_parse(char *str, int *i,
								int sign, long long *num)
{
	while (str[*i])
	{
		if (str[*i] < '0' || str[*i] > '9')
			return (0);
		if (!check_overflow(*num, sign, str[*i]))
			return (0);
		*num = *num * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (1);
}

int	ft_is_valid_long_long(char *str, long long *result)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	num = 0;
	if (!str || !str[0])
		return (0);
	sign = parse_sign(str, &i);
	if (!str[i])
		return (0);
	if (!validate_and_parse(str, &i, sign, &num))
		return (0);
	if (result)
		*result = num * sign;
	return (1);
}
