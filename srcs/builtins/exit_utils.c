/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:59:13 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/18 23:38:46 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup(char *line, t_token *tokens, t_cmd *cmds, t_shell *shell)
{
    (void)shell;  // ← ADD THIS LINE
    if (line)
        free(line);
    if (tokens)
        free_tokens(tokens);
    if (cmds)
        free_cmds(cmds);
}

int	count_exit_args(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}
