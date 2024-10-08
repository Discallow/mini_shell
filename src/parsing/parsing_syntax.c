/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:17:52 by discallow         #+#    #+#             */
/*   Updated: 2024/10/02 15:12:39 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_redir_syntax(t_token *tmp)
{
	if (!tmp->next)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	else if (tmp->next->type == REDIRECT || tmp->next->type == PIPE)
	{
		printf("syntax error near unexpected token `%s'\n", tmp->next->arg);
		return (1);
	}
	return (0);
}

int	check_syntax(t_commands *parser)
{
	t_token	*tmp;

	tmp = parser->tokens;
	while (tmp)
	{
		if (tmp->type == REDIRECT)
		{
			if (check_redir_syntax(tmp))
				return (1);
		}
		if (tmp->type == PIPE)
		{
			if (!(tmp->previous) || !(tmp->next) || tmp->next->type == PIPE
				|| tmp->previous->type == REDIRECT)
			{
				ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
				return (1);
			}
		}
		tmp = tmp -> next;
	}
	return (0);
}
