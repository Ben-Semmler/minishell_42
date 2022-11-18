/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <bsemmler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:22:03 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/18 16:59:58 by bsemmler         ###   ########.fr       */
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

typedef struct s_container
{
	int		i1;
	int		i2;
	int		i3;
	int		i4;
	char	c1;
	char	c2;
	char	c3;
	char	*cp1;
	bool	b;
}	t_container;

typedef struct s_args
{
	int		argc;
	char	**argv;
}	t_args;

typedef struct s_action
{
	char			*command;
	t_args			args;
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
char		*read_fd(int fd, bool print);
char		*ft_strncpy(char *src, int size);

char		*ft_joinfree(char *str1, int free1, char *str2, int free2);

int			get_command_id(char *input);
int			switch_command(char *command, t_args *args, bool *run);
void		get_options(t_action *action, char *input, int returnval);
char		*read_file(char *filename);
int			write_file(char *file, int infd);
int			write_file_append(char *file, int infd);
int			redir_left(char *command, int outfd);
int			insert_doc(char *command, int outfd);
char		check_quotations(char to_check, char quotations);

int			run_executable(const t_args *args);
int			command_echo(const t_args *args);
int			command_cd(const t_args *args);
int			command_pwd(void);
int			unset(t_args *args);
int			command_export(t_args *args);
int			command_env(void);
int			run_cmd_exec(char *command, t_args *args);
bool		*return_run(bool *run);

#endif