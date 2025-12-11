/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:49:13 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/11 14:42:25 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void free_args(char **args)
{
    int i;

    if(!args)
        return ;
    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

static void free_redirs(t_redir *redirs)
{
    t_redir *temp;
    while (redirs)
    {
        temp = redirs;
        redirs = redirs->next;
        free(temp->file);
        free(temp);
    }
}

void free_cmds(t_cmd *head)
{
    t_cmd *temp;

    while(head)
    {
        temp = head;
        head = head->next;
        free_args(temp->args);
        free_redirs(temp->redirs);
        free(temp);
    }
}
