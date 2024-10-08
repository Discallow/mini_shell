/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_exit_pwd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:24:37 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 15:15:21 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	built_pwd(t_commands *exec)
{
	char	*cwd1;

	if (exec->args[1] && exec->args[1][0] == '-')
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd(exec->args[1], 2);
		ft_putstr_fd(": invalid option\npwd: usage: pwd\n", 2);
		exec->status = 2;
		return ;
	}
	cwd1 = ft_calloc(ft_strlen(exec->cwd), sizeof(char));
	if (cwd1 == NULL || exec->cwd == NULL)
	{
		if (exec->cwd == NULL)
			ft_putstr_fd("pwd: environment or path error\n", 2);
		else if (cwd1 == NULL)
			exit_error_memory_allocation(exec);
		exec->status = 1;
		return ;
	}
	exec->status = 0;
	ft_strlcpy(cwd1, exec->cwd, ft_strlen(exec->cwd) - 1);
	ft_putstr_fd (cwd1, exec->output_fd);
	ft_putstr_fd ("\n", exec->output_fd);
	free(cwd1);
}

int	check_exit_arguments(t_commands *exec)
{
	int	i;

	i = 0;
	while (exec->args[1][i])
	{
		if (!ft_isdigit(exec->args[1][i]))
		{
			free_structs(exec, 1);
			exit (1);
		}
		i++;
	}
	return (1);
}

int	check_valid_exit(t_commands *exec)
{
	int	i;

	i = 0;
	if (exec->args[1] && (exec->args[1][0] == '-' || exec->args[1][0] == '+'))
		i++;
	while (exec->args[1] && exec->args[1][i])
	{
		if (!ft_strcmp("", exec->args[1]) || !ft_isdigit(exec->args[1][i]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(exec->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_structs(exec, 1);
			exit (2);
		}
		i++;
	}
	if (exec->args[1] && exec->args[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		if (check_exit_arguments(exec))
			return (1);
	}
	return (0);
}

void	build_exit(t_commands *exec, int flag)
{
	int	exit_status;

	exit_status = 0;
	if (check_valid_exit(exec))
		return ;
	if (exec->args[1])
		exit_status = ft_atol(exec->args[1]);
	if (exit_status > 256)
	{
		free_structs(exec, 1);
		exec->status = exit_status % 256;
		ft_putstr_fd("exit\n", 1);
		if (!flag)
			exit(exit_status % 256);
	}
	else
	{
		exec->status = exit_status;
		ft_putstr_fd("exit\n", 1);
		if (!flag)
		{
			free_structs(exec, 1);
			exit(exit_status);
		}
	}
}
