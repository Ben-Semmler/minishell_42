/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:22:03 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/14 15:46:26 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/wait.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>  
# include <fcntl.h>

typedef struct s_inputs
{
	int		argc;
	char	**argv;
	char	*stdin;
}	t_inputs;

typedef struct s_outputs
{
	char	*stdout;
	char	*stderr;
	int		returnval;
}	t_outputs;

typedef struct s_action
{
	char			*command;
	int				argc;
	char			**argv;
	char			*relation;
	bool			fork;
	struct s_action	*next;
}	t_action;


typedef struct s_cmd t_cmd;

typedef struct s_cmd
{
	char	**input;
	char	*output;

	void	(*in_fun)(t_cmd *cmd);
	void	(*out_fun)(t_cmd *cmd);
}	t_cmd;

//One allowed Global variable, it's the hash table
// that stores the environment variables
# define ENV_SIZE 2048
# define LOCAL_ENV_SIZE 256

typedef struct s_env
{
	char	*key;
	char	*data;
	int		*spot;
}	t_env;

# define ENV_SIZE 2048
extern t_env	*g_env_table;

// env funs
u_int64_t	hash(char *str, int envlen);
t_env		search(char *key);
void		insert(char *key, char *data);
char		*get_key(char *str);
char		*get_data(char *str);
void		import_env(char **env);
int			check_env(char **input);
int			insert_data(char *line, char *key);

// check_quotations
char		check_quotations(char to_check, char quotations);

// command_cd
int			command_cd(const t_inputs *input);
int			cd_absolute(char **argv);
int			cd_relative2(char *ext, char *cwdext, char **argv);
int			cd_relative(char **argv);

// command_echo
int			command_echo(const t_inputs *input);
int			get_echo_len(char **argv);

// command_enviroment_utils
char		*get_data(char *str);
int			command_env(void);
int			get_env_len(char *str);

// command_enviroment
void		import_env(char **env);
int			insert_data(char *line, char *key);
int			command_export(t_inputs *input);
int			unset(t_inputs *input);
char		*get_key(char *str);

// command_pwd
int			command_pwd(void);

// ft_joinfree
char		*ft_joinfree(char *str1, int free1, char *str2, int free2);

// get_options_utils
int			get_arg_size(char *input, bool include_interpret, int returnval);

// get_options
void		get_options(t_action *action, char *input, int returnval);
int			get_command(t_action *action, char *input, int returnval);
int			get_argn(char *input);
char		*copy_arg(char *input, int returnval);

// hashTable
u_int64_t	hash(char *str, int envlen);
t_env		search(char *key);
void		insert(char *key, char *data);

// main_utils
void		free_split_input(char **s_input);
size_t		action_size(t_action *action);
int			execute_actions2(t_inputs *input,
				t_outputs *outputs, char **stderrs);
int			execute_actions(t_action *action, bool *run);
void		switch_relation(t_action *action, t_inputs *input,
				t_outputs 	*output, bool *run);

// main
bool		*return_run(bool *run);
void		handle_sig(int sig);
int			inti(int argc, char **argv, char **env, bool *run);
void		run_action(t_action *action, t_inputs *input,
				t_outputs *output, bool *run);

// read_fd
char		*read_fd(int *fd, bool print);

// redirections_left
void		redir_left(char *command, t_outputs *output);
char		*read_file(char *filename);
void		insert_doc(char *command, t_outputs *output);

// redirections_right
void		write_to_file(char *input, char *file);
void		write_to_file_append(char *input, char *file);

// run_cmd_exec
void		run_cmd_exec2(char *dir, char *path, char **args, char *command);
int			run_cmd_exec(char *command, t_inputs *input, t_outputs *output);
void		next_dir2(bool reset, int *path_pos, char *path, int *size);
char		*next_dir(bool reset, const char *path, char *command);
char		**make_args(char *command, char **args);

// run_executable
int			run_executable2(int *filedes, char *cwd,
				t_inputs *input, t_outputs *output);
int			run_executable(const t_inputs *input, t_outputs *output);

// split_actions_utils
void		fill_action(t_action *action, char *input, int size, int returnval);
t_action	*init_next_action(t_action *action);
char		*ft_strncpy(char *src, int size);
int			check_pipe_chars(char *input);
char		*find_relation(char *input);

// split_ations
int			inti_split_actions(t_action	*actions, t_action	*tempaction);
t_action	*split_actions(char *input, int returnval);
int			find_next_seperator(char *input);
t_action	*redir_reverse(t_action *action, char *input,
				int *k, int returnval);

// switch_command
int			switch_command(char *command, t_inputs *input,
				t_outputs *output, bool *run);

#endif
