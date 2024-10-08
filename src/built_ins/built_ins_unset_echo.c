/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_unset_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 01:46:52 by discallow         #+#    #+#             */
/*   Updated: 2024/10/02 15:18:03 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	delete_node(t_build_env **envs)
{
	t_build_env	*tmp;

	tmp = (*envs)->next;
	if (tmp)
		tmp -> previous = (*envs)->previous;
	(*envs)->previous->next = tmp;
	free((*envs)->name_and_value);
	free((*envs)->name);
	free((*envs)->value);
	free((*envs));
}

void	build_unset(t_commands *exec)
{
	t_commands	*tmp;
	t_build_env	*envs;
	int			i;

	i = -1;
	tmp = exec;
	exec->status = 0;
	while (tmp->args[++i])
	{
		envs = exec->envs;
		if (exec->private_path && !ft_strcmp("PATH", tmp->args[i]))
		{
			free(exec->private_path);
			exec->private_path = NULL;
		}
		while (envs)
		{
			if (!ft_strcmp(envs->name, tmp->args[i]))
			{
				delete_node(&envs);
				break ;
			}
			envs = envs ->next;
		}
	}
}

int	check_echo_flag(t_commands *exec, int i)
{
	int	j;

	j = 0;
	while (exec->args[++i])
	{
		if (exec->args[i][0] == '-')
		{
			while (exec->args[i][++j])
			{
				if (exec->args[i][j] != 'n')
					return (i);
			}
		}
		else if (exec->args[i][0] != '-')
			return (i);
		j = 0;
	}
	return (i);
}

void	built_echo(t_commands *exec)
{
	int		i;
	bool	flag;

	exec->status = 0;
	if (!exec->args[1])
	{
		ft_putstr_fd("\n", exec->output_fd);
		return ;
	}
	flag = true;
	i = 0;
	i = check_echo_flag(exec, i);
	if (i > 1)
		flag = false;
	if (i > 0 && exec->args[i])
	{
		ft_putstr_fd(exec->args[i], exec->output_fd);
		while (exec->args[++i])
		{
			ft_putstr_fd(" ", exec->output_fd);
			ft_putstr_fd(exec->args[i], exec->output_fd);
		}
	}
	if (flag)
		ft_putstr_fd("\n", exec->output_fd);
}
