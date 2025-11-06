/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:14 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/06 16:36:16 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_cd(char **args, t_shell *shell)
{
	(void)shell;
	if (!args[1])
	{
		printf("cd: missing argument\n");
		return (1);
	}
	if (chdir(args[1]) != 0)
		perror("cd");
	return (0);
}
