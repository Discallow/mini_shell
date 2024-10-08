/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_here_doc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:20:23 by discallow         #+#    #+#             */
/*   Updated: 2024/10/08 03:18:03 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	g_sigint = 0;

static int	ft_strcmp2(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (i);
	while ((str1[i] || str2[i]) && str1[i] == str2[i])
		i++;
	if (str1[i] == '\n' && str2[i] == '\0' && i > 0)
		i--;
	else if (str1[i] == '\n' && str2[i] == '\0')
		return (0);
	return (str1[i] - str2[i]);
}

void	close_everything(t_commands *parser, t_token *args_extract)
{
	int	i;

	i = 0;
	while (i < parser->pipe_count)
	{
		if (parser->pipes[i][0] > 2)
			close(parser->pipes[i][0]);
		if (parser->pipes[i][1] > 2)
			close(parser->pipes[i][1]);
		i++;
	}
	close (parser->here_doc_pipes[0]);
	close (parser->here_doc_pipes[1]);
	free_tmp_struct(&args_extract);
	free_structs(parser, 1);
}

int	setup_heredoc2(t_commands *parser, t_token *cur)
{
	char	*line;

	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	if (g_sigint == 130)
	{
		parser->status = 130;
		return (130);
	}
	if (!line || (ft_strcmp2(line, cur->arg) == 0))
	{
		if (!line)
			write(1, "\n", 1);
		free(line);
		return (1);
	}
	else
	{
		if (!cur->quotes_used && !cur->double_quotes_used
			&& !cur->single_quotes_used)
			line = check_expansion_here_doc_env(line, parser);
		write(parser->input_fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

void	alloc_mem_here_doc(t_commands *parser)
{
	if (parser->here_doc_pipes)
		free(parser->here_doc_pipes);
	parser->here_doc_pipes = ft_calloc(2, sizeof(int));
	if (parser->here_doc_pipes == NULL)
		exit_error_memory_allocation(parser);
	if (pipe(parser->here_doc_pipes) == -1)
	{
		perror("pipe");
		exit(free_structs(parser, 1));
	}
}

int	setup_here_doc(t_commands *parser, t_token *cur, t_token *args_extract)
{
	pid_t	pid;

	alloc_mem_here_doc(parser);
	parser->input_fd = parser->here_doc_pipes[1];
	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	if (pid == 0)
	{
		set_heredoc_mode();
		while (1)
		{
			if (setup_heredoc2(parser, cur))
				break ;
		}
		close_everything(parser, args_extract);
		exit (parser->status);
	}
	set_ignore_mode();
	waitpid(pid, &parser->status, 0);
	status_management(parser);
	return (parser->status);
}
