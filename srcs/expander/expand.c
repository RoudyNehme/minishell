/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:18:02 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/22 02:33:34 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int should_expand_redir(t_token_type type)
{
    return(type == REDIR_IN || type == REDIR_OUT
            || type == REDIR_APPEND);
}

static char *expand_arg(char *arg, t_shell *shell)
{
    char *expanded;
    char *no_quotes;

    expanded = expand_variable(arg, shell);
    if (!expanded)
        return (NULL);
    no_quotes = remove_quotes(expanded);
    free(expanded);
    return (no_quotes);
}

static void expand_redirections(t_redir *redirs, t_shell *shell)
{
    char *expanded;

    while(redirs)
    {
        if(should_expand_redir(redirs->type))
        {
            expanded = expand_arg(redirs->file, shell);
            if(expanded)
            {
                free(redirs->file);
                redirs->file = expanded;
            }
        }
        redirs = redirs->next;
    }
}

static void expand_command_args(t_cmd *cmd, t_shell *shell)
{
    int i;
    char *expanded;
    
    i = 0;
    while(cmd->args[i])
    {
        expanded = expand_arg(cmd->args[i], shell);
        if (expanded)
        {
            free(cmd->args[i]);
            cmd->args[i] = expanded;
        }
        i++;
    }
}

void expand_commands(t_cmd *cmds, t_shell *shell)
{
    t_cmd *copy;

    copy = cmds;
    while(copy)
    {
        expand_command_args(copy, shell);
        if(copy->redirs)
            expand_redirections(copy->redirs, shell);
        copy = copy->next;
    }
}
