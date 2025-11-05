/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:08:20 by rnehme            #+#    #+#             */
/*   Updated: 2025/11/04 17:09:16 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_args(char **args)
{
    int j;

    printf("Args: ");
    if (args)
    {
        j = 0;
        while (args[j])
        {
            printf("[%s] ", args[j]);
            j++;
        }
    }
    printf("\n");
}

static void print_redir_type(t_token_type type, char *file)
{
    if (type == REDIR_IN)
        printf("  < %s\n", file);
    else if (type == REDIR_OUT)
        printf("  > %s\n", file);
    else if (type == REDIR_APPEND)
        printf("  >> %s\n", file);
    else if (type == HEREDOC)
        printf("  << %s\n", file);
}

static void print_redirs(t_redir *redirs)
{
    t_redir *current;

    current = redirs;
    if (current)
    {
        printf("Redirections:\n");
        while (current)
        {
            print_redir_type(current->type, current->file);
            current = current->next;
        }
    }
}

void print_cmds(t_cmd *cmds)
{
    t_cmd *current;
    int i;

    current = cmds;
    i = 1;
    while (current)
    {
        printf("\n=== Command %d ===\n", i);
        print_args(current->args);
        print_redirs(current->redirs);
        current = current->next;
        i++;
    }
    printf("\n");
}
