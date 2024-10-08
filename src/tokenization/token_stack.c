/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:01:26 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 02:49:06 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*ft_last_node(t_token *head)
{
	if (!head)
		return (NULL);
	while (head -> next)
		head = head->next;
	return (head);
}

void	create_stack_helper(t_commands *cmd, t_token **node)
{
	t_token	*last_node;

	if (!(cmd->tokens))
	{
		cmd->tokens = *node;
		(*node)-> previous = NULL;
	}
	else
	{
		last_node = ft_last_node(cmd->tokens);
		last_node -> next = *node;
		(*node)-> previous = last_node;
	}
}

void	ignore_quotes(t_commands *cmd, size_t *index, size_t *len, t_token *t)
{
	if (cmd->line[*index] == '\'')
		t->single_quotes_used = true;
	else if (cmd->line[*index] == '\"')
		t->double_quotes_used = true;
	if (cmd->line[*index] == '\"' || cmd->line[*index] == '\'')
	{
		*len = *len - 2;
		(*index)++;
	}
}

int	create_stack(t_commands *cmd, size_t len, size_t index)
{
	t_token	*node;
	size_t	i;

	i = 0;
	skip_spaces(cmd->line, &index);
	node = ft_calloc(1, sizeof(t_token));
	if (!node)
		return (1);
	ignore_quotes(cmd, &index, &len, node);
	node -> arg = ft_calloc(len + 1, sizeof(char));
	if (!(node->arg))
		return (1);
	while (i < len)
	{
		node->arg[i] = cmd->line[index];
		index++;
		i++;
	}
	if (node->double_quotes_used || node->single_quotes_used)
		index += 1;
	if (cmd->line[index] && ft_isspace(cmd->line[index]))
		node->is_space_between_words = true;
	create_stack_helper(cmd, &node);
	return (0);
}

void	skip_spaces(char *line, size_t *i)
{
	size_t	index;

	index = *i;
	while (line[index] && ft_isspace(line[index]))
		index++;
	*i = index;
}
