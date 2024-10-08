/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:46:20 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 15:20:56 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	build_env(t_build_env **final_built_env, char **environ)
{
	int		i;
	char	*aux;
	char	*pwd_short;

	i = 0;
	while (environ[i])
	{
		create_env_stack(environ[i], final_built_env);
		i++;
	}
	if (i == 0)
	{
		aux = ft_getcwd();
		pwd_short = ft_substr(aux, 0, ft_strlen(aux) - 2);
		free(aux);
		aux = ft_strjoin("PWD=", pwd_short);
		create_env_stack(aux, final_built_env);
		free(aux);
		free(pwd_short);
	}
}

void	print_env(t_commands *exec, int flag)
{
	t_build_env	*tmp;

	tmp = exec->envs;
	exec->status = 0;
	if (exec->args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return ;
	}
	while (tmp)
	{
		if (flag)
		{
			ft_putstr_fd ("declare -x ", exec->output_fd);
			ft_putstr_fd(tmp->name_and_value, exec->output_fd);
			ft_putstr_fd ("\n", exec->output_fd);
		}
		else if (tmp->value_exists)
		{
			ft_putstr_fd(tmp->name_and_value, exec->output_fd);
			ft_putstr_fd ("\n", exec->output_fd);
		}
		tmp = tmp->next;
	}
}

int	index_before_separator(char *str, int index)
{
	while (str[index])
	{
		if (!ft_isalpha(str[index]) || ft_isdigit(str[index]))
			if (str[index] != '_' && str[index] != '?')
				return (index);
		index++;
	}
	return (index);
}

int	expand_env2(t_token *expand_arg, t_build_env *expand_env,
			int index, int arg_end)
{
	char	*sub_str;

	while (expand_env && expand_arg->arg[1] && arg_end != index)
	{
		if (expand_env->name && !ft_strncmp(expand_arg->arg + index,
				expand_env->name, arg_end - index))
		{
			sub_str = ft_substr(expand_arg->arg, arg_end,
					ft_strlen(expand_arg->arg) - arg_end);
			expand_arg->arg = ft_strjoin3(expand_arg->arg,
					expand_env->value, index - 1);
			expand_arg->arg = ft_strjoin3(expand_arg->arg, sub_str,
					ft_strlen(expand_arg->arg) + ft_strlen(sub_str));
			free(sub_str);
			return (1);
		}
		expand_env = expand_env->next;
	}
	return (0);
}

void	expand_env(t_token *expand_arg, t_commands *parser, int index)
{
	t_build_env	*expand_env;
	int			arg_end;
	char		*sub_str;

	expand_env = parser->envs;
	if (!ft_strcmp(expand_arg->arg, "$PATH") && parser->private_path)
	{
		free(expand_arg->arg);
		expand_arg->arg = ft_strdup(parser->private_path);
	}
	arg_end = index_before_separator(expand_arg->arg, index);
	if (expand_arg->arg[index] == '?')
	{
		expand_return_value(parser, &(expand_arg->arg), index);
		return ;
	}
	if (expand_env2(expand_arg, expand_env, index, arg_end))
		return ;
	if (expand_arg && expand_arg->arg)
	{
		sub_str = ft_substr(expand_arg->arg, arg_end,
				ft_strlen(expand_arg->arg) - arg_end);
		expand_arg->arg = ft_strjoin3(expand_arg->arg, sub_str, index - 1);
		free(sub_str);
	}
}
