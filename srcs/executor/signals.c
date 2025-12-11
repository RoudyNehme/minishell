/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:28:18 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/11 14:33:41 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int g_signal = 0;

void sigint_prompt_handler(int sig)
{
	g_signal = sig;
	write(1,"\n",1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
void	sigint_heredoc_handler(int sig)
{
	(void)sig;
    write(1, "\n", 1);
    exit(130); 
}