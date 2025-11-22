/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:25 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/12 11:14:43 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;

	if(shell->cmds && shell->cmds->args[1])
	{
		printf("minishell: env: %s: No such file or directory\n", shell->cmds->args[1]);
		return (127);
	}

	while (shell->envp && shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
			printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
}
