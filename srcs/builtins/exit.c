/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:50 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/14 18:05:51 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_numeric(char *str)
{
	int i  = 0;
	if(str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return(0);
		i++;
	}
	return (1);
}

void cleanup(char *line, t_token *tokens, t_cmd *cmds, t_shell *shell)
{
	if(line)
		free(line);
	if(tokens)
		free_tokens(tokens);
	if(cmds)
		free_cmds(cmds);
	if (shell && shell->envp)
	{
		int	i;
	
		i = 0;
		while (shell->envp[i])
			free(shell->envp[i++]);
		free(shell->envp);
	}
	rl_clear_history();
		
}

int builtin_exit(char **args, t_shell *shell, char *line, t_token *tokens, t_cmd *cmds)
{
	printf("exit\n");
	int arg_count = 0;
	while (args && args[arg_count])
		arg_count ++;
	if(arg_count == 1)
	{
		cleanup(line, tokens, cmds, shell);
		exit(shell->last_exit_status);
	}
	if(arg_count > 2)
	{
		printf("minishell: exit: too many arguments\n");
		shell->last_exit_status = 1;
		return (1);
	}
	if(!ft_is_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		shell->last_exit_status = 2;
		cleanup(line, tokens, cmds, shell);
		exit(2);
	}
	int exit_code;

	exit_code = atoi(args[1]) % 256;
	if(exit_code < 0)
		exit_code += 256;
    cleanup(line, tokens, cmds, shell);
	exit(exit_code);
}
