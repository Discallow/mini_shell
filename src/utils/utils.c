/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:34:11 by asofia-g          #+#    #+#             */
/*   Updated: 2024/10/03 03:22:14 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	close_files(t_commands *command)
{
	int	j;

	j = 0;
	while (j < command->pipe_count && command->pipes[j])
	{
		if (command->pipes[j][0] > 2)
			close(command->pipes[j][0]);
		if (command->pipes[j][1] > 2)
			close(command->pipes[j][1]);
		j++;
	}
}

void	set_last_com(t_commands *command)
{
	char	*last_com;

	last_com = ft_strjoin("_=", command->args[0]);
	check_valid_name_value(last_com, 1, command);
	free(last_com);
}

char	*ft_getcwd(void)
{
	char	*cwd;
	char	*cwd1;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd() error");
		return (NULL);
	}
	cwd1 = ft_strjoin(cwd, "$ ");
	free (cwd);
	return (cwd1);
}

void	alloc_mem(t_commands *parser)
{
	int	i;

	i = 0;
	if (!parser->pipe_count)
		return ;
	parser->pipes = ft_calloc((parser->pipe_count + 1), sizeof(int *));
	if (parser->pipes == NULL)
		exit_error_memory_allocation(parser);
	while (i < (parser->pipe_count))
	{
		parser->pipes[i] = ft_calloc(2, sizeof(int));
		if (parser->pipes[i] == NULL)
		{
			free_pipes(parser, i);
			exit_error_memory_allocation(parser);
		}
		i++;
	}
}

char	*ft_strjoin3(char *s1, char *s2, int index)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	j = 0;
	buffer = ft_calloc(sizeof(char *), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!buffer)
		return (NULL);
	while (s1 && s1[i] && i < index)
	{
		buffer[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		buffer[i + j] = s2[j];
		j++;
	}
	if (s1)
		free(s1);
	return (buffer);
}
