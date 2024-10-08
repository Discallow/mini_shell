/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:27:45 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 15:32:48 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	start_input(t_commands *command)
{
	command->cwd = ft_getcwd();
	if (!(command->cwd))
		return (1);
	command->line = readline(command->cwd);
	if (!command->line)
	{
		free_structs(command, 1);
		exit (0);
	}
	return (0);
}

void	init_struct(t_commands *command, t_build_env *build_envs, char **env)
{
	command->line = NULL;
	command->cwd = NULL;
	command->input_fd = 0;
	command->output_fd = 1;
	command->input_fd_path = NULL;
	command->output_fd_path = NULL;
	command->pid = NULL;
	command->pipes = NULL;
	command->pipe_count = 0;
	command->fd = 0;
	command->args = NULL;
	command->index = 0;
	command->envs = build_envs;
	command->redirect_used_before = 0;
	command->command_executed = 0;
	command->simple_command = 0;
	command->cur_env = env;
	command->tokens = NULL;
	command->here_doc_pipes = NULL;
}

int	check_valid_env(t_build_env *tmp, char *str)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, str))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	create_env(t_build_env *tmp, t_commands *command)
{
	command->private_path = NULL;
	if (check_valid_env(tmp, "PATH"))
		command->private_path = ft_strdup("/usr/local/sbin:/usr/local/bin:" \
		"/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin:/snap/bin");
}
