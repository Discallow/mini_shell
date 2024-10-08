/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:47:39 by discallow         #+#    #+#             */
/*   Updated: 2024/10/02 13:03:58 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	validate_var_name(char *s)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*s) || ft_isdigit(*s))
		if (*s != '_')
			return (1);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]))
			if (s[i] != '_')
				return (1);
		i++;
	}
	return (0);
}

int	check_valid_name_value(char *str, int index, t_commands *exec)
{
	t_build_env	*tmp;

	tmp = exec->envs;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name_and_value, str, index))
		{
			free(tmp->name_and_value);
			free(tmp->value);
			free(tmp->name);
			tmp->name_and_value = ft_strdup(str);
			tmp->name = ft_substr(tmp->name_and_value, 0, index);
			tmp->value = ft_substr(tmp->name_and_value, index + 1,
					ft_strlen(tmp->name_and_value) - index);
			tmp->value_exists = false;
			if (tmp->value && ft_strcmp(tmp->value, ""))
				tmp->value_exists = true;
			return (1);
		}
		tmp = tmp -> next;
	}
	create_env_stack(str, &(exec->envs));
	return (0);
}

void	build_export2(int i, t_commands *tmp, t_commands *exec)
{
	int	j;

	j = 0;
	while (tmp->args[i][j])
	{
		if (tmp->args[i][j] == '=')
		{
			check_valid_name_value(tmp->args[i], j, exec);
			return ;
		}
		j++;
	}
	check_valid_name_value(tmp->args[i], j, exec);
}

void	build_export(t_commands *exec)
{
	t_commands	*tmp;
	int			i;

	i = 1;
	tmp = exec;
	if (!exec->args[1])
	{
		print_env(exec, 1);
		return ;
	}
	while (tmp->args[i])
	{
		if (validate_var_name(tmp->args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(tmp->args[i], 2);
			ft_putstr_fd("\': not a valid identifier", 2);
			ft_putstr_fd ("\n", 2);
			exec->status = 1;
		}
		else
			build_export2(i, tmp, exec);
		i++;
	}
}
