/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:05:14 by discallow         #+#    #+#             */
/*   Updated: 2024/10/02 15:21:28 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	parse(t_commands *parser)
{
	t_token	*tmp;
	t_token	*cur;

	set_default_mode();
	tmp = parser->tokens;
	cur = parser->tokens;
	get_pipe_count(parser);
	alloc_mem(parser);
	if (check_syntax(parser))
		return ;
	open_first_pipes(parser);
	while (cur)
	{
		open_pipes(parser);
		if (cur->type == REDIRECT)
			check_redirection(parser, &cur, &tmp);
		if (cur && cur->type == PIPE)
			check_pipes(parser, &cur, &tmp);
		if (cur)
			cur = cur->next;
	}
	if (tmp)
		parse_simple_command(parser, tmp);
}
