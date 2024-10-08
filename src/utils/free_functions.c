/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:02:57 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 03:05:46 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_pipes(t_commands *command, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(command->pipes[i]);
		i++;
	}
}

void	free_structs3(t_commands *command, int i)
{
	if (command->pipes)
	{
		i = 0;
		while (i < command->pipe_count)
		{
			free(command->pipes[i]);
			i++;
		}
		free(command->pipes);
	}
	if (command->pid)
		free(command->pid);
	if (command->cwd)
		free(command->cwd);
	if (command->line)
		free(command->line);
	if (command->here_doc_pipes)
		free(command->here_doc_pipes);
}

void	free_structs2(t_commands *command)
{
	int	i;

	i = 0;
	if (command)
	{
		if (command->args)
		{
			while (command->args[i])
			{
				free(command->args[i]);
				i++;
			}
			free(command->args);
		}
		free_structs3(command, i);
	}
}

void	free_envs(t_commands *command)
{
	t_build_env	*tmp2;

	while (command && command->envs)
	{
		tmp2 = command->envs;
		command->envs = command->envs->next;
		free(tmp2->name);
		free(tmp2->value);
		free(tmp2->name_and_value);
		free(tmp2);
	}
	command->envs = NULL;
	if (command->private_path)
		free(command->private_path);
}

int	free_structs(t_commands *command, int flag)
{
	t_token		*tmp;

	if (!command)
		return (1);
	if (flag != 2)
		free_envs(command);
	while (command->tokens)
	{
		tmp = command->tokens;
		command->tokens = command->tokens->next;
		if (tmp->arg)
			free(tmp->arg);
		free(tmp);
	}
	free_structs2(command);
	if (flag == 1)
		rl_clear_history();
	return (1);
}
