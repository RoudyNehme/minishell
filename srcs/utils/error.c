/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:57:24 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/12 14:42:24 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// to be continued
#include "../../includes/minishell.h"

void error_message(char *msg)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putendl_fd(msg, 2);
}

void error_syntax(char *msg)
{
    ft_putstr_fd("minishell: syntax error", 2);
    if (msg)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(msg, 2);
    }
    ft_putstr_fd("\n", 2);
}

void error_command(char *msg)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(msg, 2);
    ft_putendl_fd(": command not found", 2);
}
void error_file(char *msg)
{
    //will continue later..
}
