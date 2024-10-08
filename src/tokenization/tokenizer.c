/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:16:43 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 02:59:11 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_enum(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if ((!ft_strcmp(tmp->arg, "<") || !ft_strcmp(tmp->arg, "<<")
				|| !ft_strcmp(tmp->arg, ">") || !ft_strcmp(tmp->arg, ">>"))
			&& tmp->double_quotes_used == false
			&& tmp->single_quotes_used == false)
			tmp->type = REDIRECT;
		else if (!ft_strcmp(tmp->arg, "|") && tmp->double_quotes_used == false
			&& tmp->single_quotes_used == false)
			tmp->type = PIPE;
		else
			tmp->type = WORD;
		tmp = tmp -> next;
	}
}

int	token_input(t_commands *command)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (check_quotes_number(command))
		return (1);
	while (command->line[i])
	{
		len = ft_token_len(command->line, i);
		if (len > 0 && create_stack(command, len, i))
		{
			ft_putstr_fd("Error allocating memory", 2);
			free_structs(command, 1);
			exit (1);
		}
		skip_spaces(command->line, &i);
		i += len;
	}
	set_enum(command->tokens);
	create_expand_env_variables(command);
	join_args(command);
	return (0);
}

int	check_redirect(char *s, size_t index)
{
	if (s[index] == '<' && s[index + 1] && s[index + 1] == '<')
		return (2);
	else if (s[index] == '>' && s[index + 1] && s[index + 1] == '>')
		return (2);
	return (1);
}

int	check_separator(char *s, size_t index, size_t i)
{
	if (s[index] && (s[index] == '<' || s[index] == '>'))
		return (check_redirect(s, index));
	else if (s[index] && s[index] == '|')
		return (1);
	else if (s[index] && s[index] == '\'')
		return (check_quotes(s, index));
	else if (s[index] && s[index] == '\"')
		return (check_double_quotes(s, index));
	else if (s[index] && s[index] == '$')
	{
		i++;
		index++;
		while (s[index] && !ft_strchr(SEPARATORS, s[index])
			&& s[index] != 10 && (s[index] < 9 || s[index] > 13))
		{
			i++;
			index++;
		}
		return (i);
	}
	return (0);
}

size_t	ft_token_len(char *s, size_t index)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	skip_spaces(s, &index);
	j = check_separator(s, index, i);
	if (j != 0)
		return (j);
	while (s[index] && !ft_strchr(SEPARATORS, s[index])
		&& s[index] != 10 && (s[index] < 9 || s[index] > 13))
	{
		i++;
		index++;
	}
	return (i);
}
