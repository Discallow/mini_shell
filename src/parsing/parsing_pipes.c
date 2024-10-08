/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:26:45 by discallow         #+#    #+#             */
/*   Updated: 2024/09/30 17:39:19 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*pipes_parser(t_commands *parser, t_token *tmp, t_token *cur)
{
	t_token	*args_extracted;

	args_extracted = NULL;
	while (tmp != cur)
	{
		if (tmp->type == WORD)
			create_new_stack(tmp->arg, &args_extracted, parser);
		tmp = tmp->next;
	}
	build_args(parser, args_extracted);
	parser->output_fd = parser->pipes[parser->index][1];
	if (args_extracted)
	{
		free_tmp_struct(&args_extracted);
		parser->command_executed = true;
		exec_command(parser);
	}
	return (tmp);
}

void	get_pipe_count(t_commands *parser)
{
	t_token	*tmp;

	tmp = parser->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
			parser->pipe_count = parser->pipe_count + 1;
		tmp = tmp->next;
	}
}

void	check_pipes(t_commands *parser, t_token **cur, t_token **tmp)
{
	if (parser->redirect_used_before == true)
		parser->redirect_used_before = false;
	if ((*tmp)->previous)
		parser->input_fd = parser->pipes[parser->index -1][0];
	(*tmp) = pipes_parser(parser, (*tmp), (*cur));
	re_initiate_struct(&parser);
	parser->index++;
}

void	open_first_pipes(t_commands *parser)
{
	if (parser->index == parser->pipe_count)
		return ;
	if (pipe(parser->pipes[parser->index]) == -1)
	{
		perror("pipe");
		exit(free_structs(parser, 1));
	}
	if (parser->index + 1 == parser->pipe_count)
		return ;
	if (pipe(parser->pipes[parser->index + 1]) == -1)
	{
		perror("pipe");
		exit(free_structs(parser, 1));
	}
}

void	open_pipes(t_commands *parser)
{
	if (parser->index < 2 || parser->index == parser->pipe_count
		|| !parser->command_executed)
		return ;
	parser->command_executed = false;
	if (parser->index < parser->pipe_count)
	{
		if (pipe(parser->pipes[parser->index]) == -1)
		{
			perror("pipe");
			exit(free_structs(parser, 1));
		}
	}
}
