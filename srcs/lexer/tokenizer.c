/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberdkan <rberdkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:07:42 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/18 22:42:15 by rberdkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_whitespace(char *line, int *i) // skip whitespace func
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static int	bad_operator(char c)
{
	return (c == '|' || c == '.' || c == '\\' || c == '/');
}

static int	is_trailing_operator(char *line, int i)
{
	if (!bad_operator(line[i]))
		return (0);
	i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (!line[i]);
}

static void	tokenizer_helper(t_token **head, char *line, int *i) // handles the input if operator quoted(double ""or single '') or just naked word
{
	char	*word;

	if (is_operator(line[*i]))
		add_token(head, handle_operator(line, i));
	else if (!is_seperator(line[*i]))
	{
		word = extract_full_word(line, i);
		if (word)
		{
			add_token(head, create_token(WORD, word));
			free(word);
		}
	}
}

t_token	*tokenizer(char *line) // takes the user input and loops until the end ('\0'); returns the head pointer to the first token of the list
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (line[i])
	{
		skip_whitespace(line, &i);
		if (!line[i])
			break ;
		if (is_trailing_operator(line, i))
		{
			free_tokens(head);
			ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
			ft_putchar_fd(line[i], 2);
			ft_putstr_fd("'\n", 2);
			return (NULL);
		}
		tokenizer_helper(&head, line, &i);
	}
	return (head);
}
