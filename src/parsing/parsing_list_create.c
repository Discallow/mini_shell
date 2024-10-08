/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:47:02 by discallow         #+#    #+#             */
/*   Updated: 2024/09/30 17:46:53 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	build_args_helper(t_commands *parser, t_token *new_stack,
	t_token *last_node, t_token *tmp)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (i <= last_node->index)
	{
		j = 0;
		len = ft_strlen(tmp->arg);
		parser->args[i] = ft_calloc(len + 1, sizeof(char));
		if (parser->args[i] == NULL)
		{
			free_tmp_struct(&new_stack);
			ft_putstr_fd("Error allocating memory", 2);
			exit (free_structs(parser, 1));
		}
		while (j < len)
		{
			parser->args[i][j] = tmp->arg[j];
			j++;
		}
		i++;
		tmp = tmp -> next;
	}
}

void	build_args(t_commands *parser, t_token *new_stack)
{
	t_token	*last_node;
	t_token	*tmp;

	if (!new_stack)
		return ;
	tmp = new_stack;
	last_node = ft_last_node(new_stack);
	parser->args = ft_calloc(last_node->index + 2, sizeof(char *));
	if (parser->args == NULL)
	{
		free_tmp_struct(&new_stack);
		ft_putstr_fd("Error allocating memory", 2);
		exit (free_structs(parser, 1));
	}
	build_args_helper(parser, new_stack, last_node, tmp);
}

void	create_new_stack2(char *str, t_token **a, t_token **node, int len)
{
	t_token	*last_node;
	int		i;

	i = 0;
	while (i < len)
	{
		(*node)->arg[i] = str[i];
		i++;
	}
	if (!(*a))
	{
		*a = (*node);
		(*node)-> previous = NULL;
	}
	else
	{
		last_node = ft_last_node(*a);
		last_node -> next = (*node);
		(*node)-> previous = last_node;
		(*node)-> index = (*node)-> previous -> index + 1;
	}
}

void	create_new_stack(char *str, t_token **a, t_commands *parser)
{
	t_token	*node;
	int		len;

	len = ft_strlen(str);
	node = ft_calloc(1, sizeof(t_token));
	if (!node)
	{
		ft_putstr_fd("Error allocating memory", 2);
		exit (free_structs(parser, 1));
	}
	node -> arg = ft_calloc(len + 1, sizeof(char));
	if (!(node->arg))
	{
		free_tmp_struct(&node);
		ft_putstr_fd("Error allocating memory", 2);
		exit (free_structs(parser, 1));
	}
	node -> next = NULL;
	create_new_stack2(str, a, &node, len);
}
