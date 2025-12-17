/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:28:18 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/13 02:33:47 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

void sigint_prompt_handler(int sig)
{
    g_signal = sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void sigint_heredoc_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(130);
}

void sigint_exec_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
}

void sigquit_exec_handler(int sig)
{
    (void)sig;
    write(1, "Quit (core dumped)\n", 19);
}

void setup_signals(void)
{
    signal(SIGINT, sigint_prompt_handler);
    signal(SIGQUIT, SIG_IGN);
}
