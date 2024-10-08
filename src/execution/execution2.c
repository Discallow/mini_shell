/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:00:13 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 05:14:23 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	child_built_in_process(t_commands *command)
{
	execute_built_ins(command, 1);
	close_files(command);
	free_structs(command, 0);
	exit(command->status);
}

void	child_process_2(t_commands *command)
{
	if (command->args[0][0] != '.' && command->args[0][1] != '/')
	{
		ft_putstr_fd (command->args[0], 2);
		ft_putstr_fd (": command not found\n", 2);
		free_structs(command, 0);
		exit(127);
	}
	if (!check_path(command) && access(command->args[0], X_OK) != 0)
	{
		ft_putstr_fd ("Permission denied: ", 2);
		ft_putstr_fd (command->args[0], 2);
		ft_putstr_fd ("\n", 2);
		free_structs(command, 0);
		exit(126);
	}
	free_structs(command, 0);
	status_management(command);
	exit(command->status);
}

void	child_process(t_commands *command)
{
	dup2 (command->input_fd, STDIN_FILENO);
	dup2 (command->output_fd, STDOUT_FILENO);
	if (command->input_fd > 2)
		close (command->input_fd);
	if (command->output_fd > 2)
		close (command->output_fd);
	close_files(command);
	if (!ft_strcmp("", command->args[0]))
	{
		ft_putstr_fd (command->args[0], 2);
		ft_putstr_fd (": command not found\n", 2);
		free_structs(command, 0);
		exit(127);
	}
	check_path(command);
	exec_cmd (command);
	child_process_2(command);
}

void	*pipes_manager(int id, int *pid)
{
	pid[id] = fork();
	if (pid[id] < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	return (NULL);
}

void	status_management(t_commands *command)
{
	if (WIFEXITED(command->status))
	{
		command->status = WEXITSTATUS(command->status);
		return ;
	}
	else if (WIFSIGNALED(command->status))
	{
		command->status = 128 + WTERMSIG(command->status);
		return ;
	}
}
