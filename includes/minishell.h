/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:22:03 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/15 20:28:54 by marvin           ###   ########.fr       */
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

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char	**input;
	char	*output;

	void	(*in_fun)(t_cmd *cmd);
	void	(*out_fun)(t_cmd *cmd);
}	t_cmd;

typedef struct s_env
{
	char	*key;
	char	*data;
	int		*spot;
}	t_env;

//One allowed Global variable, it's the hash table
extern t_env			*g_env_table;

// env funs
u_int64_t	hash(char *str, int envlen);
t_env		search(char *key);
void		insert(char *key, char *data);
char		*get_key(char *str);
char		*get_data(char *str);
void		import_env(char **env);
int			check_env(char **input);
int			insert_data(char *line, char *key);

t_action	*split_actions(char *input, int returnval);
char		*read_fd(int *fd, bool print);
char		*ft_strncpy(char *src, int size);

char		*ft_joinfree(char *str1, int free1, char *str2, int free2);

int			get_command_id(char *input);
int			switch_command(char *command, t_inputs *input,
				t_outputs *output, bool *run);
void		get_options(t_action *action, char *input, int returnval);
char		*read_file(char *filename);
void		redir_left(char *command, t_outputs *output);
void		write_file(char *stdin, char *file);
void		write_file_append(char *stdin, char *file);
void		insert_doc(char *command, t_outputs *output);
char		check_quotations(char to_check, char quotations);

int			run_executable(const t_inputs *input, t_outputs *output);
int			command_echo(const t_inputs *input);
int			command_cd(const t_inputs *input);
int			command_pwd(void);
int			command_cat(const t_inputs *input, t_outputs *output);
int			unset(t_inputs *input);
int			command_export(t_inputs *input);
int			command_env(void);
int			run_cmd_exec(char *command, t_inputs *input, t_outputs *output);

#endif