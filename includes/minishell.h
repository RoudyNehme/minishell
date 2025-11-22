/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:24:13 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/20 17:49:59 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
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
void *expand_var(char *str, t_shell *shell);

#endif
