/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:23:41 by discallow         #+#    #+#             */
/*   Updated: 2024/10/08 03:20:00 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all
 --trace-origins=yes --suppressions=readline.supp ./minishell*/

int	main(void)
{
	t_commands	command;
	t_build_env	*build_envs;
	extern char	**environ;

	build_envs = NULL;
	build_env(&build_envs, environ);
	create_env(build_envs, &command);
	command.status = 0;
	while (1)
	{
		set_interactive_mode(&command.status);
		init_struct(&command, build_envs, environ);
		if (start_input(&command))
			return (1);
		reset_global_variable_sign(&command);
		if (ft_strlen(command.line) != 0)
			add_history(command.line);
		if (token_input(&command) && free_structs(&command, 2))
			continue ;
		if (ft_strlen(command.line) == 0 && free_structs(&command, 2))
			continue ;
		parse(&command);
		free_structs(&command, 2);
	}
	return (command.status);
}
