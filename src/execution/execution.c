/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 02:28:01 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 05:17:04 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_path(t_commands *command)
{
	char	**paths;
	int		i;
	char	*cmd;

	if (command->private_path)
		paths = ft_split(command->private_path, ':');
	else
		paths = ft_split(get_minishell_env(command, "PATH"), ':');
	if (!access(command->args[0], F_OK))
		return (clean_array(paths), 0);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin (paths[i], "/");
		cmd = ft_strjoin2 (cmd, command->args[0]);
		if (cmd == NULL)
			return (ft_putstr_fd("Mem alloc error", 2), -1);
		if (access(cmd, F_OK) == 0)
		{
			free(cmd);
			return (clean_array(paths), 0);
		}
		free(cmd);
	}
	return (clean_array(paths), -1);
}

void	exec_cmd(t_commands	*command)
{
	char	**paths;
	int		i;
	char	*cmd;

	if (command->private_path)
		paths = ft_split(command->private_path, ':');
	else
		paths = ft_split(get_minishell_env(command, "PATH"), ':');
	if (!access(command->args[0], F_OK))
		execve(command->args[0], command->args, command->cur_env);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin (paths[i], "/");
		cmd = ft_strjoin2 (cmd, command->args[0]);
		if (cmd == NULL)
		{
			perror("Mem alloc error");
			exit(1);
		}
		execve(cmd, command->args, command->cur_env);
		free(cmd);
	}
	clean_array(paths);
}

void	parent_process(t_commands *command)
{
	int	i;

	if (command->input_fd > 2)
		close (command->input_fd);
	if (command->output_fd > 2)
		close (command->output_fd);
	set_ignore_mode();
	close_files(command);
	i = -1;
	while (i++ < command->pipe_count)
	{
		if (command->pid[i] > 0)
			waitpid(command->pid[i], &command->status, 0);
	}
}

void	exec_command_2(t_commands *command, int built_in_checked)
{
	if (command->pid[command->index] == 0 && !built_in_checked)
		child_process(command);
	else if (command->pid[command->index] == 0 && built_in_checked)
		child_built_in_process(command);
	else if (command->pid[command->index] > 0
		&& (command->index == command->pipe_count
			|| ((command->simple_command)
				&& command->index +1 == command->pipe_count)))
		parent_process(command);
	status_management(command);
	set_last_com(command);
	set_interactive_mode(&command->status);
}

void	exec_command(t_commands *command)
{
	int	built_in_checked;

	if (!command->pid)
	{
		command->pid = (int *)ft_calloc(command->pipe_count + 1, sizeof(int *));
		if (command->pid == NULL)
		{
			perror("Mem alloc error");
			exit(1);
		}
		command->pid[command->pipe_count + 1] = 0;
	}
	built_in_checked = check_built_ins(command);
	if (!command->pipe_count && built_in_checked)
	{
		execute_built_ins(command, 0);
		set_last_com(command);
		return ;
	}
	set_default_mode();
	pipes_manager (command->index, command->pid);
	exec_command_2(command, built_in_checked);
}
