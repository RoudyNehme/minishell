/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:53:07 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/16 21:26:08 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_exit_args(char **args)
{
    int	count;

    count = 0;
    while (args[count])
        count++;
    return (count);
}

static void	handle_no_args(t_shell *shell, char *line, t_token *tokens,
        t_cmd *cmds)
{
    write(1, "exit\n", 5);
    cleanup(line, tokens, cmds, shell);
    exit(shell->last_exit_status);
}

static void	handle_invalid_arg(t_shell *shell, char **args, char *line,
        t_token *tokens, t_cmd *cmds)
{
    write(2, "exit\n", 5);
    write(2, "minishell: exit: ", 17);
    write(2, args[1], ft_strlen(args[1]));
    write(2, ": numeric argument required\n", 28);
    cleanup(line, tokens, cmds, shell);
    exit(2);
}

static int	handle_too_many_args(void)
{
    write(2, "exit\n", 5);
    write(2, "minishell: exit: too many arguments\n", 36);
    return (1);
}

int	builtin_exit(char **args, t_shell *shell, char *line,
        t_token *tokens, t_cmd *cmds)
{
    int		arg_count;
    int		exit_code;

    arg_count = count_exit_args(args);
    if (arg_count == 1)
        handle_no_args(shell, line, tokens, cmds);
    if (!is_valid_number(args[1], &exit_code))
        handle_invalid_arg(shell, args, line, tokens, cmds);
    if (arg_count > 2)
        return (handle_too_many_args());
    write(1, "exit\n", 5);
    cleanup(line, tokens, cmds, shell);
    exit((unsigned char)exit_code);
}
