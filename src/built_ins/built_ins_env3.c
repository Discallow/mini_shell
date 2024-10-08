/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_env3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:28:06 by discallow         #+#    #+#             */
/*   Updated: 2024/10/08 03:12:36 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	create_expand_env_variables2(t_commands *parser, int index, t_token *tmp)
{
	int	check_if_valid_expand;

	if (tmp->arg[index] == '$')
		check_if_valid_expand = index_before_separator(tmp->arg, index + 1);
	if (tmp->arg[index] == '$' && tmp->arg[index + 1]
		&& check_if_valid_expand != index + 1 && !tmp->single_quotes_used)
	{
		expand_env(tmp, parser, index + 1);
		index = 0;
	}
	else
		index++;
	return (index);
}

void	create_expand_env_variables(t_commands *parser)
{
	t_token		*tmp;
	int			index;

	tmp = parser->tokens;
	while (tmp)
	{
		index = 0;
		if (!ft_strcmp(tmp->arg, "<<") && tmp->next)
			tmp = tmp -> next;
		else if (!ft_strcmp(tmp->arg, "$") && tmp->next
			&& tmp->is_space_between_words == false)
		{
			free(tmp->arg);
			tmp->arg = ft_strdup("");
			tmp = tmp->next;
		}
		else
			while (tmp->arg && tmp->arg[index])
				index = create_expand_env_variables2(parser, index, tmp);
		tmp = tmp -> next;
	}
}

char	*get_minishell_env(t_commands *commands, char *var)
{
	char		*minishell_env_value;
	t_build_env	*envs;

	minishell_env_value = NULL;
	envs = commands->envs;
	while (envs)
	{
		if (!ft_strcmp(var, envs->name))
		{
			minishell_env_value = envs->value;
			break ;
		}
		envs = envs ->next;
	}
	return (minishell_env_value);
}
