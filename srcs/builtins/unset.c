/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:40 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/15 22:14:56 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_arg_validity(char *arg)
{
	int index;
	
	index = 0;
	if (!arg || arg[0] == '\0')
    return (0);
	if(ft_isalpha(arg[index]) || arg[index] == '_')
		index++;
	else
		return (0);
	while (arg[index])
	{
		if(ft_isalpha(arg[index]) || ft_isdigit(arg[index]) || arg[index] == '_')
			index++;
		else
			return (0);
	}
	return (1);
}

int builtin_unset(char **args, t_shell *shell)
{
    int i;

    if (!args || !args[1])
    {
        shell->last_exit_status = 0;
        return (0);
    }

    shell->last_exit_status = 0;
    i = 1;

    while (args[i])
    {
        if (!check_arg_validity(args[i]))
        {
            printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
            shell->last_exit_status = 1;
        }
        else
        {
            int key_index = get_path_index(shell->envp, args[i]);

            if (key_index != -1)
            {
                int size = 0;
                while (shell->envp[size])
                    size++;
                char **new_envp = malloc(sizeof(char *) * size);
                if (!new_envp)
				{
					shell->last_exit_status = 1;
                    return (1);
				}

                int old_i = 0;
                int new_i = 0;

                while (shell->envp[old_i])
                {
                    if (old_i == key_index)
                        old_i++;
                    new_envp[new_i] = ft_strdup(shell->envp[old_i]);
                    if (!new_envp[new_i])
                    {
                        while (--new_i >= 0)
                            free(new_envp[new_i]);
                        free(new_envp);
						shell->last_exit_status = 1;
                        return (1);
                    }
                    new_i++;
                    old_i++;
                }
                new_envp[new_i] = NULL;
                free_2d(shell->envp);

                shell->envp = new_envp;
            }
        }
        i++;
    }
    return (shell->last_exit_status);
}

