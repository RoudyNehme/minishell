/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:07:27 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/14 10:18:06 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// temporary prototypes
int builtin_echo(char **args);
int builtin_pwd(void);
int builtin_cd(char **args, t_shell *shell);
int builtin_env(t_shell *shell);
int builtin_export(char **args, t_shell *shell);
int builtin_unset(char **args, t_shell *shell);
int builtin_exit(char **args, t_shell *shell, char *line, t_token *tokens, t_cmd *cmds);
int is_builtin(char *cmd);
int run_builtin(char **args, t_shell *shell, char *line, t_token *tokens, t_cmd *cmds);

char **dup_env(char **real_env)
{
	int size;

	size = 0;
	while (real_env[size])
		size++;
	char **copy_env;
	
	copy_env = malloc(sizeof(char *) * (size + 1));
	if(!copy_env)
		return (NULL);
	int i;

	i = 0;
	while (i < size)
	{
		copy_env[i] = ft_strdup(real_env[i]);
		i++;
	}
	copy_env[size] = NULL;
	return (copy_env);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_shell shell;
    shell.envp = dup_env(envp);
    shell.last_exit_status = 0;

	return (0);

}
