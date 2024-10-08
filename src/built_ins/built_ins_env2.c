/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_env2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:54:40 by discallow         #+#    #+#             */
/*   Updated: 2024/10/02 13:04:16 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_build_env	*ft_last_env_node(t_build_env *head)
{
	if (!head)
		return (NULL);
	while (head -> next)
		head = head->next;
	return (head);
}

void	get_env_name_value(t_build_env *node)
{
	int	i;

	i = 0;
	while (node->name_and_value[i])
	{
		if (node->name_and_value[i] == '=')
		{
			node->name = ft_substr(node->name_and_value, 0, i);
			node->value = ft_substr(node->name_and_value, i + 1,
					ft_strlen(node->name_and_value) - i);
			if (node->value)
				node->value_exists = true;
			return ;
		}
		i++;
	}
}

void	create_env_stack_helper(char *str, t_build_env **a,
					t_build_env **node, int len)
{
	t_build_env	*last_node;
	int			i;

	i = 0;
	while (i < len)
	{
		(*node)->name_and_value[i] = str[i];
		i++;
	}
	get_env_name_value(*node);
	if (!(*a))
	{
		*a = (*node);
		(*node)-> previous = NULL;
	}
	else
	{
		last_node = ft_last_env_node(*a);
		last_node -> next = (*node);
		(*node)-> previous = last_node;
	}
}

void	create_env_stack(char *str, t_build_env **a)
{
	t_build_env	*node;
	int			len;

	len = ft_strlen(str);
	node = ft_calloc(1, sizeof(t_build_env));
	if (!node)
	{
		ft_putstr_fd("Error allocating memory", 2);
		exit (1);
	}
	node -> name_and_value = ft_calloc(len + 1, sizeof(char));
	if (!(node->name_and_value))
	{
		ft_putstr_fd("Error allocating memory", 2);
		exit (1);
	}
	node -> next = NULL;
	create_env_stack_helper(str, a, &node, len);
}

void	expand_return_value(t_commands *parser, char **expand_arg, int index)
{
	char	*str;
	char	*str2;

	str2 = NULL;
	str = ft_itoa(parser->status);
	str2 = ft_substr((*expand_arg), index + 1, ft_strlen(*expand_arg));
	str = ft_strjoin3(str, str2, ft_strlen(str) + ft_strlen(str2));
	free(str2);
	str2 = ft_substr(*expand_arg, 0, index - 1);
	free (*expand_arg);
	*expand_arg = ft_strjoin3(str2, str, ft_strlen(str) + ft_strlen(str2));
	free(str);
}
