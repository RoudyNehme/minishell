/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnehme <rnehme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:01:14 by rnehme            #+#    #+#             */
/*   Updated: 2025/12/06 12:17:29 by rnehme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_word(char *line, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	while (line[*i] && !is_seperator(line[*i]) && line[*i] != '\'' && line[*i] != '"') // keep looping as long as *i is not a seperator
	{
		if(line[*i] == '\\' && line[*i + 1])
			(*i) += 2; // skip backlash and next char
		else
			(*i)++;
	}
	len = *i - start; // getting word length 
	word = malloc(len + 1); // allocating mem +1 for null terminator
	if (!word)
		return (NULL);
	ft_strncpy(word, line + start, len); // here line + start is creating a new pointer that points to the character at [start pos]
	word[len] = '\0';
	return (word);
}

// static void	handle_escape_in_quotes(char *line, int *i, char quote)
// {
// 	// handle escape in double quotes only
// 	if (quote == '"' && line[*i] == '\\' && line[*i + 1])
// 	{
// 		// escapes $ " \ `
// 		if (line[*i + 1] == '$' || line[*i + 1] == '"'
// 			|| line[*i + 1] == '\\' || line[*i + 1] == '`')
// 			(*i) += 2; // skip backslash and escaped char
// 		else
// 			(*i)++; // backslash is literal
// 	}
// 	else
// 		(*i)++;
// }

char *extract_full_word(char *line, int *i)
{
	int start = *i;
	char quote;
	int len = 0;

	// compute length first
	while (line[*i] && !is_seperator(line[*i]) && !is_operator(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[*i];
			(*i)++;
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	len = *i - start;
	return ft_substr(line, start, len);
}
