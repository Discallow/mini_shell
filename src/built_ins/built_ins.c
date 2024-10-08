/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:14:10 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 03:17:10 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	execute_built_ins(t_commands *exec, int flag)
{
	if (!ft_strcmp("exit", exec->args[0]))
		return (build_exit(exec, flag), 1);
	else if (!ft_strcmp("env", exec->args[0]))
		return (print_env(exec, 0), 1);
	else if (!ft_strcmp("pwd", exec->args[0]))
		return (built_pwd(exec), 1);
	else if (!ft_strcmp("echo", exec->args[0]))
		return (built_echo(exec), 1);
	else if (!ft_strcmp("unset", exec->args[0]))
		return (build_unset(exec), 1);
	else if (!ft_strcmp("cd", exec->args[0]))
		return (build_cd(exec), 1);
	else if (!ft_strcmp("export", exec->args[0]))
		return (build_export(exec), 1);
	return (0);
}

int	check_built_ins(t_commands *exec)
{
	if (!ft_strcmp("exit", exec->args[0]))
		return (1);
	else if (!ft_strcmp("env", exec->args[0]))
		return (1);
	else if (!ft_strcmp("pwd", exec->args[0]))
		return (1);
	else if (!ft_strcmp("echo", exec->args[0]))
		return (1);
	else if (!ft_strcmp("unset", exec->args[0]))
		return (1);
	else if (!ft_strcmp("cd", exec->args[0]))
		return (1);
	else if (!ft_strcmp("export", exec->args[0]))
		return (1);
	return (0);
}
