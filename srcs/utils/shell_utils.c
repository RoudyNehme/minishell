/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:30:00 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/17 16:30:00 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_shlvl_value(char **envp)
{
	char	*shlvl_str;
	int		shlvl;

	if (!envp)
		return (0);
	shlvl_str = get_env_value("SHLVL", envp);
	if (!shlvl_str)
		return (0);
	shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		return (0);
	if (shlvl > 999)
		return (1);
	return (shlvl);
}

void	increment_shlvl(t_shell *shell)
{
	int		shlvl;
	char	*new_shlvl;

	shlvl = get_shlvl_value(shell->envp);
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return ;
	set_env("SHLVL", new_shlvl, shell);
	free(new_shlvl);
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = dup_env(envp);
	shell->cmds = NULL;
	shell->last_exit_status = 0;
	signal(SIGINT, sigint_prompt_handler);
	signal(SIGQUIT, SIG_IGN);
	increment_shlvl(shell);
}

int	handle_signal_interrupt(t_shell *shell, char *line)
{
	shell->last_exit_status = 130;
	g_signal = 0;
	if (line)
		free(line);
	return (1);
}
