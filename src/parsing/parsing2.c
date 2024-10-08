/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:40:35 by discallow         #+#    #+#             */
/*   Updated: 2024/09/30 17:45:48 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	parse_simple_command(t_commands *parser, t_token *tmp)
{
	t_token	*args_extracted;

	args_extracted = NULL;
	if (tmp->previous)
	{
		parser->input_fd = parser->pipes[parser->index - 1][0];
	}
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			create_new_stack(tmp->arg, &args_extracted, parser);
		}
		tmp = tmp->next;
	}
	build_args(parser, args_extracted);
	if (args_extracted)
	{
		free_tmp_struct(&args_extracted);
		parser->simple_command = true;
		exec_command(parser);
	}
}

void	re_initiate_struct(t_commands **parser)
{
	int	i;

	i = 0;
	if ((*parser)->input_fd > 2)
		close ((*parser)->input_fd);
	if ((*parser)->output_fd > 2)
		close ((*parser)->output_fd);
	if ((*parser)->args)
	{
		while ((*parser)->args[i])
		{
			free((*parser)->args[i]);
			i++;
		}
		free((*parser)->args);
	}
	(*parser)->input_fd = 0;
	(*parser)->output_fd = 1;
	(*parser)->input_fd_path = NULL;
	(*parser)->output_fd_path = NULL;
	(*parser)->args = NULL;
}
