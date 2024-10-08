/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_open_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 06:15:52 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 04:37:56 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	open_append_file(t_commands *parser, char *path)
{
	if (parser->output_fd > 2)
		close (parser->output_fd);
	parser->output_fd_path = path;
	parser->output_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (parser->output_fd == -1)
	{
		printf("%s: %s\n", path, strerror(errno));
		parser->status = 1;
		return (1);
	}
	return (0);
}

int	open_truncate_file(t_commands *parser, char *path)
{
	if (parser->output_fd > 2)
		close (parser->output_fd);
	parser->output_fd_path = path;
	parser->output_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (parser->output_fd == -1)
	{
		printf("%s: %s\n", path, strerror(errno));
		parser->status = 1;
		return (1);
	}
	return (0);
}

int	open_read_file(t_commands *parser, char *path)
{
	if (parser->input_fd > 2)
		close (parser->input_fd);
	parser->input_fd_path = path;
	parser->input_fd = open(path, O_RDONLY);
	if (parser->input_fd == -1)
	{
		printf("%s: %s\n", path, strerror(errno));
		parser->status = 1;
		return (1);
	}
	return (0);
}

int	open_here_doc(t_commands *parser, t_token *cur, t_token *args_extract)
{
	if (parser->input_fd > 2)
		close (parser->input_fd);
	parser->input_fd_path = cur->arg;
	setup_here_doc(parser, cur, args_extract);
	close (parser->input_fd);
	parser->input_fd = parser->here_doc_pipes[0];
	return (parser->status);
}

int	open_file(t_token *cur, t_commands *parser, char *path, t_token *args)
{
	if (!ft_strcmp(cur->arg, ">>"))
		return (open_append_file(parser, path));
	else if (!ft_strcmp(cur->arg, ">"))
		return (open_truncate_file(parser, path));
	else if (!ft_strcmp(cur->arg, "<"))
		return (open_read_file(parser, path));
	else
		return (open_here_doc(parser, cur->next, args));
	return (0);
}
