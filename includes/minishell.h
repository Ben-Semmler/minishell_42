/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:22:03 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/23 12:28:27 by jgobbett         ###   ########.fr       */
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

# include <sys/types.h>
# include <sys/stat.h>
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
}	t_outputs;

typedef struct s_action
{
	char			*command;
	int				argc;
	char			**argv;
	char			*relation;
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
}	t_env;

# define ENV_SIZE 2048
t_env	g_env_table[ENV_SIZE];

// env funs
u_int64_t	hash(char *str, int envlen);
t_env		search(char *key);
void		insert(char *key, char *data);
char 		*get_key(char *str);
char 		*get_data(char *str);
void		command_env(void);
void		import_env(char **env);
int			check_env(char **input);
int 		insert_data(char *line, char *key);

t_action	*split_actions(char *input);
char		*read_stdout(t_action *action, int *filedes);

char		*ft_joinfree(char *str1, int free1, char *str2, int free2);

int			get_command_id(char *input);
void		switch_command(char *command, t_inputs *input);
void		get_options(t_action *action, char *input);
void 		writeToFile(char *stdin, char *file);
void 		writeToFile_append(char *stdin, char *file);
void		readFile(char *command, t_outputs *output);
void		insert_doc(char *command, t_outputs *output);
char		check_quotations(char to_check, char quotations);

void		run_executable(const t_inputs *input);
void		command_echo(const t_inputs *input);
void		command_cd(const t_inputs *input);
void		command_pwd(const t_inputs *input);
void		command_cat(const t_inputs *input);

/*char		*run_executable(char **input);
char		*command_cd(char **s_input);
char		*command_pwd(char **s_input);*/

#endif
