/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:32:09 by asofia-g          #+#    #+#             */
/*   Updated: 2024/10/03 15:35:53 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//Handler for SIGINT (Ctrl-C): displays a new prompt on a new line
void	handle_interactive_ctrl_c(int sig)
{
	char	*cwd;

	if (sig == SIGINT)
	{
		g_sigint = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		cwd = ft_getcwd();
		if (!cwd)
			return ;
		printf("\n%s", cwd);
		free(cwd);
	}
}

/*if on a child process, ctrl C is ignored
(using SIG_IGN, insted handle_interactive_ctrl_c)*/
void	setup_default_ctrl_c_handler(void)
{
	struct sigaction	sa_default;

	sa_default.sa_handler = SIG_DFL;
	sa_default.sa_flags = SA_RESTART;
	sigemptyset(&sa_default.sa_mask);
	if (sigaction(SIGINT, &sa_default, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	handle_heredoc_ctrl_c(int sig)
{
	if (sig == SIGINT)
		g_sigint = 130;
}

/*set ctrl c to print a new line (handle_heredoc_ctrl_c) with exit code 130
set ctrl \ to do nothing*/
void	set_heredoc_mode(void)
{
	struct sigaction	sa_heredoc;
	struct sigaction	sa_quit;

	sa_heredoc.sa_handler = handle_heredoc_ctrl_c;
	sa_heredoc.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_heredoc.sa_mask);
	if (sigaction(SIGINT, &sa_heredoc, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	set_ignore_mode(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = SIG_IGN;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}
