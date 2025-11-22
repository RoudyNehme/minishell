/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:06 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/06 22:48:56 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_pwd(void)
{
	char	*pwd;
	
	pwd = getcwd(NULL,0);
	if(!pwd)
	{
		perror("minishell: pwd: ");
		return (1);
	}
	printf("%s\n",pwd);
	free(pwd);
	return (0);
}
