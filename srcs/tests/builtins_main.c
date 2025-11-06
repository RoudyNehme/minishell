/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:07:27 by rberdkan          #+#    #+#             */
/*   Updated: 2025/11/06 22:52:00 by rberdkan         ###   ########.fr       */
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
int builtin_exit(char **args, t_shell *shell);
int is_builtin(char *cmd);
int run_builtin(char **args, t_shell *shell);

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_shell shell;
    shell.envp = envp;
    shell.last_exit_status = 0;

    printf("=== Builtins Testing ===\n");

    // char *echo_args[] = {"echo","-nr","hello", "world", NULL};
    // run_builtin(echo_args, &shell);
	char *args[] = {"pwd", NULL};
	run_builtin(args,&shell);

    return 0;
}
