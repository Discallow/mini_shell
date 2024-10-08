/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:44:33 by discallow         #+#    #+#             */
/*   Updated: 2024/10/03 15:26:23 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	setup_default_ctrl_backslash_handler(void)
{
	struct sigaction	sa_default;

	sa_default.sa_handler = SIG_DFL;
	sa_default.sa_flags = SA_RESTART;
	sigemptyset(&sa_default.sa_mask);
	if (sigaction(SIGQUIT, &sa_default, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	set_interactive_mode(int *exit_status)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_interactive_ctrl_c;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction");
		*exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	set_default_mode(void)
{
	setup_default_ctrl_c_handler();
	setup_default_ctrl_backslash_handler();
}

void	reset_global_variable_sign(t_commands *command)
{
	if (g_sigint == 130)
	{
		g_sigint = !g_sigint;
		command->status = 130;
	}
}
