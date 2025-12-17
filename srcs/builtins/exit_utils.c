/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:59:13 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/16 11:44:26 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup(char *line, t_token *tokens, t_cmd *cmds, t_shell *shell)
{
	int	i;

	if (line)
		free(line);
	if (tokens)
		free_tokens(tokens);
	if (cmds)
		free_cmds(cmds);
	if (shell && shell->envp)
	{
		i = 0;
		while (shell->envp[i])
			free(shell->envp[i++]);
		free(shell->envp);
	}
	rl_clear_history();
}

int	count_exit_args(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}
