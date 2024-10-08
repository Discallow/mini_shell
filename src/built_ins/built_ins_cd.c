/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:15:31 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 15:19:08 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_old_path(t_commands *exec)
{
	t_build_env	*envs;
	char		*aux;
	char		*pwd;

	envs = exec->envs;
	pwd = NULL;
	while (envs)
	{
		if (!ft_strcmp("PWD", envs->name))
		{
			pwd = envs->value;
			break ;
		}
		envs = envs ->next;
	}
	aux = ft_strjoin("OLDPWD=", pwd);
	check_valid_name_value(aux, 6, exec);
	free(aux);
	aux = ft_getcwd();
	pwd = ft_substr(aux, 0, ft_strlen(aux) - 2);
	free (aux);
	aux = ft_strjoin("PWD=", pwd);
	check_valid_name_value(aux, 3, exec);
	free(aux);
	free(pwd);
}

int	build_cd2(t_commands *exec)
{
	if (exec->args[2])
	{
		ft_putstr_fd ("cd: too many arguments\n", 2);
		exec->status = 1;
		return (1);
	}
	if (access(exec->args[1], F_OK) != 0 || access(exec->args[1], X_OK) != 0)
	{
		ft_putstr_fd (exec->args[0], 2);
		ft_putstr_fd (": ", 2);
		ft_putstr_fd (exec->args[1], 2);
		if (access(exec->args[1], F_OK) != 0)
			ft_putstr_fd (": No such file or directory\n", 2);
		else
			ft_putstr_fd (": Permission denied\n", 2);
		exec->status = 1;
		return (1);
	}
	return (0);
}

void	build_cd(t_commands *exec)
{
	if (!exec->args[1] || ft_strcmp(exec->args[1], "~") == 0)
	{
		if (chdir(get_minishell_env(exec, "HOME")) != 0)
		{
			perror("cd faild");
			exec->status = 1;
		}
		set_old_path(exec);
		return ;
	}
	if (build_cd2(exec))
		return ;
	if (chdir(exec->args[1]) != 0)
	{
		perror("cd failed:");
		exec->status = 1;
		return ;
	}
	set_old_path(exec);
	exec->status = 0;
}
