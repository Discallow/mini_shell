/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 04:50:24 by discallow         #+#    #+#             */
/*   Updated: 2024/10/02 15:13:40 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	heredoc2(t_build_env *expand_env, char **line, int index, int arg_end)
{
	char	*sub_str;

	if (!ft_strncmp(*line + index, expand_env->name, arg_end - index))
	{
		sub_str = ft_substr(*line, arg_end, ft_strlen(*line) - arg_end);
		*line = ft_strjoin3(*line, expand_env->value, index - 1);
		*line = ft_strjoin3(*line, sub_str,
				ft_strlen(*line) + ft_strlen(sub_str));
		free(sub_str);
		return (1);
	}
	return (0);
}

char	*expand_heredoc_env(char *line, t_commands *parser, int index)
{
	t_build_env	*expand_env;
	int			arg_end;
	char		*sub_str;

	expand_env = parser->envs;
	arg_end = index_before_separator(line, index);
	if (line[index] == '?')
	{
		expand_return_value(parser, &line, index);
		return (line);
	}
	while (expand_env && arg_end != index)
	{
		if (heredoc2(expand_env, &line, index, arg_end))
			return (line);
		expand_env = expand_env->next;
	}
	if (line)
	{
		sub_str = ft_substr(line, arg_end, ft_strlen(line) - arg_end);
		line = ft_strjoin3(line, sub_str, index - 1);
		free(sub_str);
	}
	return (line);
}

char	*check_expansion_here_doc_env(char *line, t_commands *parser)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '$' && line[index + 1]
			&& !ft_strchr(SEPARATORS, line[index + 1]))
		{
			line = expand_heredoc_env(line, parser, index + 1);
			index = 0;
		}
		else
			index++;
	}
	return (line);
}
