/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 04:19:28 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 14:48:21 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	total_len;
	char	*buffer;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	buffer = (char *)malloc((total_len + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	ft_strlcpy(buffer, s1, ft_strlen(s1) + 1);
	ft_strlcat(buffer, s2, total_len + 1);
	if (s1)
		free(s1);
	return (buffer);
}

void	are_quotes_used_to_expand_here_doc(t_token *tmp)
{
	if (tmp->next && (tmp->next->single_quotes_used
			|| tmp->next->double_quotes_used))
		tmp->quotes_used = true;
	if (tmp && (tmp->single_quotes_used || tmp->double_quotes_used))
		tmp->quotes_used = true;
}

void	join_args(t_commands *node)
{
	t_token	*tmp;
	t_token	*free_tmp;
	t_token	*join_node;

	tmp = node->tokens;
	while (tmp)
	{
		while (tmp && !tmp->is_space_between_words && tmp->type == WORD
			&& tmp->next && tmp->next->type == WORD)
		{
			join_node = tmp->next;
			are_quotes_used_to_expand_here_doc(tmp);
			tmp->is_space_between_words = join_node->is_space_between_words;
			tmp->arg = ft_strjoin2(tmp->arg, join_node->arg);
			if (!tmp->arg)
				exit_error_memory_allocation(node);
			free_tmp = join_node;
			join_node = join_node ->next;
			tmp->next = join_node;
			free(free_tmp->arg);
			free(free_tmp);
		}
		if (tmp)
			tmp = tmp->next;
	}
}
