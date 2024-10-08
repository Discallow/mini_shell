/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:59:58 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 14:54:39 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	redir_parser2(t_commands *parser, t_token *cur, t_token *args_extract)
{
	build_args(parser, args_extract);
	if (cur && cur->type == PIPE && parser->output_fd == 1)
	{
		parser->redirect_used_before = true;
		parser->output_fd = parser->pipes[parser->index][1];
	}
	if (args_extract)
	{
		free_tmp_struct(&args_extract);
		parser->command_executed = true;
		exec_command(parser);
	}
}

int	exit_redir_parser(t_commands *parser, t_token **cur, t_token **tmp)
{
	if (parser->status == 130)
	{
		close_files(parser);
		*cur = NULL;
		return (1);
	}
	*tmp = *cur;
	parser->command_executed = true;
	return (0);
}

t_token	*redir_parser(t_commands *parser, t_token *tmp, t_token **cur)
{
	t_token	*args_extract;

	args_extract = NULL;
	if (tmp->type == PIPE)
		parser->input_fd = parser->pipes[parser->index -1][0];
	while (tmp != *cur)
	{
		if (tmp->type == REDIRECT)
		{
			if (open_file(tmp, parser, tmp->next->arg, args_extract))
			{
				free_tmp_struct(&args_extract);
				if (exit_redir_parser(parser, cur, &tmp))
					return (NULL);
				break ;
			}
			tmp = tmp -> next;
		}
		else if (tmp->type == WORD)
			create_new_stack(tmp->arg, &args_extract, parser);
		if (tmp)
			tmp = tmp->next;
	}
	redir_parser2(parser, *cur, args_extract);
	return (tmp);
}

t_token	*check_multiple_redirect(t_token *cur)
{
	t_token	*tmp;

	tmp = cur;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (tmp);
		tmp = tmp -> next;
	}
	if (tmp)
		tmp = tmp -> next;
	return (tmp);
}

void	check_redirection(t_commands *parser, t_token **cur, t_token **tmp)
{
	(*cur) = check_multiple_redirect(*cur);
	(*tmp) = redir_parser(parser, *tmp, cur);
	re_initiate_struct(&parser);
	if ((*cur) && (*cur)->type == PIPE)
	{
		parser->input_fd = parser->pipes[parser->index][0];
		parser->index++;
		if (*cur)
			(*cur) = (*cur)->next;
	}
}
