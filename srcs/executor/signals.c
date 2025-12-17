/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:28:18 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/17 15:48:59 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t g_signal = 0;

void sigint_prompt_handler(int sig)
{
    g_signal = sig;
    write(1, "\n", 1);
    rl_on_new_line(); //pause, 
    rl_replace_line("", 0);
    rl_redisplay();
}

void sigint_heredoc_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(130);
}
