/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:16:31 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/05 13:56:04 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	ENV_VAR,
	SQUOTE,
	DQUOTE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**envp;
	t_cmd	*cmds;
	int		last_exit_status;	
}	t_shell;

#define SUCCESS 0
#define ERROR_SYNTAX 2
#define ERROR_CMD_NOT_FOUND 127
#define ERROR_GENERAL 1

int			is_operator(char c);
void		free_tokens(t_token *head);
void		add_token(t_token **head, t_token *new);
t_token		*create_token(t_token_type token_type, char *value);
void		free_tokens(t_token *head);
t_token		*handle_operator(char *line, int *i);
char		*extract_word(char *line, int *i);
char		*extract_quoted_word(char *line, int *i, char quote);
t_token		*tokenizer(char *line);
void		print_tokens(t_token *head);
t_cmd		*parse_command(t_token **tokens);
void		free_cmds(t_cmd *head);
int			count_args(t_token *tokens);
void		add_redir(t_redir **head, t_redir *new);
t_redir		*create_redir(t_token_type type, char *file);
void		add_cmd(t_cmd **head, t_cmd *new);
t_cmd		*create_cmd(void);
void		print_cmds(t_cmd *cmds);
t_cmd		*parse(t_token *tokens);
int			is_valid_char(char c);
int			is_quote(char c);
char		*get_env_var(char *name, char **envp);
char		*expand_variable(char *str, t_shell *shell);
char		*handle_escapes(char *str);
void		expand_commands(t_cmd *cmds, t_shell *shell);



// ---------------- BUILTINS ----------------
int builtin_echo(char **args);
int builtin_pwd(void);
int builtin_cd(char **args, t_shell *shell);
int builtin_env(t_shell *shell);
int builtin_export(char **args, t_shell *shell);
int builtin_unset(char **args, t_shell *shell);
int builtin_exit(char **args, t_shell *shell, char *line, t_token *tokens, t_cmd *cmds);
int is_builtin(char *cmd);
int run_builtin(char **args, t_shell *shell, char *line, t_token *tokens, t_cmd *cmds);
int get_path_index(char **envp, char *key);
void free_2d(char **arr);
char **dup_env(char **real_env);
void set_env(char *key, char *value, t_shell *shell);

#endif
