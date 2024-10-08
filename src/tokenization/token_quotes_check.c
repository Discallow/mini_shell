/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:05:44 by discallow         #+#    #+#             */
/*   Updated: 2024/09/30 17:31:03 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	check_double_quotes(char *str, size_t index)
{
	size_t	i;

	i = 1;
	index++;
	while (str[index] && str[index] != '\"')
	{
		i++;
		index++;
	}
	return (i + 1);
}

size_t	check_quotes(char *str, size_t index)
{
	size_t	i;

	i = 1;
	index++;
	while (str[index] && str[index] != '\'')
	{
		i++;
		index++;
	}
	return (i + 1);
}

int	double_quotes_closed(t_commands *command, int *i)
{
	(*i)++;
	if (!command->line[*i])
		return (1);
	while (command->line[*i])
	{
		if (command->line[*i] == '\"')
			return (0);
		(*i)++;
	}
	return (1);
}

int	single_quotes_closed(t_commands *command, int *i)
{
	(*i)++;
	if (!command->line[*i])
		return (1);
	while (command->line[*i])
	{
		if (command->line[*i] == '\'')
			return (0);
		(*i)++;
	}
	return (1);
}

int	check_quotes_number(t_commands *command)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (command->line[i])
	{
		if (command->line[i] == '\'')
			single_quotes = single_quotes_closed(command, &i);
		else if (command->line[i] == '\"')
			double_quotes = double_quotes_closed(command, &i);
		if (command->line[i])
			i++;
	}
	if (single_quotes || double_quotes)
	{
		ft_putstr_fd("Invalid number of quotes\n", 2);
		return (1);
	}
	return (0);
}
