/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:50 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/06 16:36:51 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_exit(char **args, t_shell *shell)
{
	(void)args;
	(void)shell;
	printf("exit\n");
	exit(0);
	return (0);
}
