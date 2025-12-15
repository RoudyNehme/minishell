/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:50 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/14 18:05:51 by rnehme           ###   ########.fr       */
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

static int	check_digit_overflow(long long num, int sign, char c)
{
    if (sign == 1 && (num > (LLONG_MAX - (c - '0')) / 10))
        return (0);
    if (sign == -1 && (num > (-(LLONG_MIN + (c - '0'))) / 10))
        return (0);
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
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        if (!check_digit_overflow(num, sign, str[i]))
            return (0);
        num = num * 10 + (str[i] - '0');
        i++;
    }
    if (result)
        *result = num * sign;
    return (1);
}

static void	handle_exit_code(long long exit_code, t_shell *shell, \
    char *line, t_token *tokens, t_cmd *cmds)
{
    exit_code = exit_code % 256;
    if (exit_code < 0)
        exit_code += 256;
    cleanup(line, tokens, cmds, shell);
    exit((int)exit_code);
}

int	builtin_exit(char **args, t_shell *shell, char *line, \
    t_token *tokens, t_cmd *cmds)
{
    int			arg_count;
    long long	exit_code;

    printf("exit\n");
    arg_count = 0;
    while (args && args[arg_count])
        arg_count++;
    if (arg_count == 1)
    {
        cleanup(line, tokens, cmds, shell);
        exit(shell->last_exit_status);
    }
    if (!ft_is_valid_long_long(args[1], &exit_code))
    {
        printf("minishell: exit: %s: numeric argument required\n", args[1]);
        shell->last_exit_status = 2;
        cleanup(line, tokens, cmds, shell);
        exit(2);
    }
    if (arg_count > 2)
    {
        printf("minishell: exit: too many arguments\n");
        return (shell->last_exit_status = 1, 1);
    }
	return (handle_exit_code(exit_code, shell, line, tokens, cmds), 0);
}
