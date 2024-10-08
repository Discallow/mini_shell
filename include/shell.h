/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: discallow <discallow@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 04:58:23 by discallow         #+#    #+#             */
/*   Updated: 2024/07/11 04:58:23 by discallow        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <signal.h>

# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define SEPARATORS " \'\"><|"

typedef struct s_pipes	t_pipes;
typedef struct s_token	t_token;

typedef enum e_token_type
{
	PIPE,
	REDIRECT,
	WORD,
}				t_token_type;

typedef struct s_token
{
	char			*arg;
	int				index;
	t_token_type	type;
	bool			single_quotes_used;
	bool			is_space_between_words;
	bool			double_quotes_used;
	bool			quotes_used;
	struct s_token	*next;
	struct s_token	*previous;
}				t_token;

typedef struct s_build_env
{
	char				*name_and_value;
	char				*name;
	char				*value;
	bool				value_exists;
	struct s_build_env	*next;
	struct s_build_env	*previous;
}				t_build_env;

typedef struct s_commands
{
	char		*line;
	char		*cwd;
	int			input_fd;
	int			output_fd;
	char		*input_fd_path;
	char		*output_fd_path;
	pid_t		*pid;
	int			**pipes;
	int			*here_doc_pipes;
	int			pipe_count;
	int			fd;
	char		**args;
	char		*private_path;
	int			index;
	bool		redirect_used_before;
	bool		command_executed;
	bool		simple_command;
	t_token		*tokens;
	t_build_env	*envs;
	char		**cur_env;
	int			status;
	int			signal_number;
}	t_commands;

extern int				g_sigint;

/*UTILS*/
char	*ft_getcwd(void);
void	alloc_mem(t_commands *parser);
void	close_files(t_commands *command);
void	set_last_com(t_commands *command);
int		start_input(t_commands *command);
void	init_struct(t_commands *command, t_build_env *build_envs, char **env);
void	create_env(t_build_env *tmp, t_commands *command);

/*TOKENZING*/
size_t	ft_token_len(char *s, size_t index);
int		token_input(t_commands *command);
void	set_enum(t_token *token);
int		create_stack(t_commands *cmd, size_t len, size_t index);
t_token	*ft_last_node(t_token *head);
void	skip_spaces(char *line, size_t *i);
char	*ft_strjoin3(char *s1, char *s2, int index);
int		index_before_separator(char *str, int index);
void	expand_return_value(t_commands *parser, char **expand_arg, int index);
void	join_args(t_commands *node);
char	*ft_strjoin2(char *s1, char *s2);

/*PARSING*/
size_t	check_quotes(char *str, size_t index);
size_t	check_double_quotes(char *str, size_t index);
int		check_quotes_number(t_commands *command);
void	parse(t_commands *parser);
char	*check_expansion_here_doc_env(char *line, t_commands *parser);
char	*expand_heredoc_env(char *line, t_commands *parser, int index);
int		heredoc2(t_build_env *expand_env, char **line, int index, int arg_end);
int		check_syntax(t_commands *parser);
void	check_pipes(t_commands *parser, t_token **cur, t_token **tmp);
void	parse_simple_command(t_commands *parser, t_token *tmp);
void	open_first_pipes(t_commands *parser);
void	open_pipes(t_commands *parser);
void	get_pipe_count(t_commands *parser);
void	re_initiate_struct(t_commands **parser);
void	build_args(t_commands *parser, t_token *new_stack);
void	create_new_stack(char *str, t_token **a, t_commands *parser);
void	check_redirection(t_commands *parser, t_token **cur, t_token **tmp);
int		open_file(t_token *cur, t_commands *parser, char *path, t_token *args);
int		setup_here_doc(t_commands *parser, t_token *cur, t_token *args_extract);
void	alloc_mem_here_doc(t_commands *parser);

/*CLEANING PROCESSES*/
int		free_structs(t_commands *command, int flag);
void	free_tmp_struct(t_token **parser_struct);
void	clean_int(int **end);
void	clean_array(char **paths);
void	free_pipes(t_commands *command, int index);
void	free_envs(t_commands *command);
void	exit_error_memory_allocation(t_commands *node);

/*HANDLE SIGNALS*/
void	set_interactive_mode(int *exit_status);
void	set_default_mode(void);
void	setup_default_ctrl_c_handler(void);
void	set_ignore_mode(void);
void	set_heredoc_mode(void);
void	setup_default_ctrl_backslash_handler(void);
void	handle_interactive_ctrl_c(int sig);
void	reset_global_variable_sign(t_commands *command);

/*BUILT_INS*/

int		check_built_ins(t_commands *exec);
void	build_env(t_build_env **final_built_env, char **environ);
void	create_expand_env_variables(t_commands *parser);
int		check_valid_name_value(char *str, int index, t_commands *exec);
int		index_before_separator(char *str, int index);
void	expand_return_value(t_commands *parser, char **expand_arg, int index);
void	built_pwd(t_commands *exec);
void	build_exit(t_commands *exec, int flag);
void	built_echo(t_commands *exec);
void	build_unset(t_commands *exec);
void	print_env(t_commands *exec, int flag);
void	expand_return_value(t_commands *parser, char **expand_arg, int index);
void	expand_env(t_token *expand_arg, t_commands *parser, int index);
void	create_env_stack(char *str, t_build_env **a);
void	build_export(t_commands *exec);
void	build_cd(t_commands *exec);

/*EXECUTION*/
char	*get_minishell_env(t_commands *commands, char *var);
int		check_path(t_commands	*command);
void	exec_cmd(t_commands	*command);
void	child_process(t_commands	*command);
void	child_built_in_process(t_commands *command);
void	parent_process(t_commands	*command);
void	*pipes_manager(int id, int *pid);
void	exec_command(t_commands	*command);
void	status_management(t_commands *command);
int		execute_built_ins(t_commands *exec, int flag);

#endif
