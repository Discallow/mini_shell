/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 01:29:14 by discallow         #+#    #+#             */
/*   Updated: 2024/09/30 17:33:00 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clean_int(int **end)
{
	int		i;

	i = -1;
	while (end[++i])
		free(end[i]);
	free(end);
}

void	clean_array(char **paths)
{
	int		i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

void	exit_error_memory_allocation(t_commands *node)
{
	ft_putstr_fd("Error allocating memory", 2);
	exit (free_structs(node, 1));
}

void	free_tmp_struct(t_token **parser_struct)
{
	t_token	*tmp;

	while (*parser_struct)
	{
		tmp = (*parser_struct);
		(*parser_struct) = (*parser_struct)->next;
		if (tmp->arg)
			free(tmp->arg);
		free(tmp);
	}
	parser_struct = NULL;
}
