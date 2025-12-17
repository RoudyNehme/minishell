/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:16:07 by rberdkan          #+#    #+#             */
/*   Updated: 2025/12/17 18:08:12 by rnehme           ###   ########.fr       */
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
# include <signal.h>
# include <limits.h>

typedef enum token_type
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    HEREDOC,
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

typedef struct s_pipeline
{
    int		cmd_count;
    int		pipes_count;
    int		current_index;
    t_shell	*shell;
    t_cmd	*cmd_list;
    pid_t	child_pids[1024];
    int		pipes[1024][2];
}	t_pipeline;

typedef struct s_cleanup_data
{
    char *line;
    t_token *tokens;
    t_cmd *cmds;
} t_cleanup_data;

typedef struct s_norminette
{
    char **new_envp;
    int size;
    int i;
} t_norminette;

# define SUCCESS 0
# define ERROR_SYNTAX 2
# define ERROR_CMD_NOT_FOUND 127
# define ERROR_GENERAL 1

extern volatile sig_atomic_t	g_signal;

// ---------------- TOKENIZER & PARSER ----------------
int			is_operator(char c);
void		free_tokens(t_token *head);
void		add_token(t_token **head, t_token *new);
t_token		*create_token(t_token_type token_type, char *value);
t_token		*handle_operator(char *line, int *i);
char		*extract_full_word(char *line, int *i);
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

// ---------------- EXPANDER ----------------
void		expand_commands(t_cmd *cmds, t_shell *shell);
char		*handle_escapes(char *str);
int			is_seperator(char c);
int			is_valid_var_char(char c);
char		*get_env_value(char *name, char **envp);
char		*expand_env_var(char **result, char *str, int *i, t_shell *shell);
int			should_expand(char *str, int i);
char		*expand_variable(char *arg, t_shell *shell);
char		*expand_exit_status(char **result, int *i, t_shell *shell);

// ---------------- BUILTINS ----------------
int			builtin_echo(char **args);
int			builtin_pwd(void);
int			builtin_cd(char **args, t_shell *shell);
int			builtin_env(t_shell *shell);
int			builtin_export(char **args, t_shell *shell);
int			builtin_unset(char **args, t_shell *shell);
int builtin_exit(char **args, t_shell *shell, t_cleanup_data *data);
int is_builtin(char *cmd);
int run_builtin(char **args, t_shell *shell, t_cleanup_data *data);
int get_path_index(char **envp, char *key);
void		free_2d(char **arr);
char		**dup_env(char **real_env);
void		set_env(char *key, char *value, t_shell *shell);
char		*build_env_string(char *key, char *path);
char		*get_home_path(char **envp);///cahnges home to HOME
void		print_export(char **envp);
int			check_arg_validity_export(char *arg);
char		*get_key(char *str);
char		*get_value(char *str);
void		free_resources(t_shell *shell, char *line, t_token *tokens,
                t_cmd *cmds);
void		exit_shell(int code, t_shell *shell, char *line, t_token *tokens,
                t_cmd *cmds);
int count_exit_args(char **args);
int calculate_exit_code(const char *arg);
long long	ft_atoll(const char *str);
int			is_valid_number(const char *str, int *exit_code);
int			wrap_exit_code(const char *arg);
int ft_is_valid_long_long(char *str, long long *result);
void cleanup(char *line, t_token *tokens, t_cmd *cmds, t_shell *shell);

// --------------- EXECUTION ------------------
char		**ft_split_path(const char *path);
int			count_cmds(t_cmd *cmd);
char		**get_path(char **envp);
char		*get_command_path(char *cmd, char **envp);
void		free_split(char **arr);
char		*check_direct_path(char *cmd);
char		*build_full_path(char *dir, char *cmd);
char		*check_path_access(char *full, char **paths);
char		*search_in_paths(char *cmd, char **paths);
void		apply_redirs_single(t_cmd *cmd);
void		execute_single(t_cmd *cmd, t_shell *shell, char *line,
                t_token *tokens);
void		execute_external_command(t_cmd *cmd, t_shell *shell);
int			has_heredoc(t_cmd *cmd_list);
int			process_heredocs(t_cmd *cmd_list, t_shell *shell);
void		execute_pipeline(t_cmd *cmd_list, t_shell *shell, char *line,
                t_token *tokens);

// Pipeline functions
int			create_pipes_pl(t_pipeline *pl);
void		close_all_pipes(t_pipeline *pl);
void		cleanup_fork_error(t_pipeline *pl);
void		setup_first_cmd(t_pipeline *pl);
void		setup_last_cmd(t_pipeline *pl);
void		setup_middle_cmd(t_pipeline *pl);
void		setup_child_pipes(t_pipeline *pl);
void		execute_builtin_child(t_cmd *cmd, t_pipeline *pl);
void		execute_external_child(t_cmd *cmd, t_pipeline *pl);
void		execute_child_cmd(t_cmd *cmd, t_pipeline *pl);
int			fork_all_commands(t_pipeline *pl);
void		wait_all_children(t_pipeline *pl);

// Heredoc functions
char		*generate_hd_filename(void);
int			setup_heredoc_file(t_redir *cmd_red);
int			should_expand_heredoc(t_redir *cmd_red);
char		*expand_heredoc_line(char *line, t_shell *shell);
void		heredoc_child_process(t_redir *redir, char *delim, int expand,
                t_shell *shell);

//----------------SIGNALS -----------------
void		sigint_prompt_handler(int sig);
void		sigint_heredoc_handler(int sig);

#endif
