/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:19:53 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/14 15:12:04 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd_exec2(char *dir, char *path, char **args, char *command)
{
	dir = next_dir(true, path, command);
	while (dir != NULL)
	{
		execve(dir, args, NULL);
		free(dir);
		dir = next_dir(false, path, command);
	}
	perror(ft_joinfree("minishell: ", 0,
			ft_strjoin(command, ": command not found"), 1));
	exit(127);
}

int	run_cmd_exec(char *command, t_inputs *input, t_outputs *output)
{
	char	*path;
	char	*dir;
	char	**args;
	pid_t	p;
	int		filedes[2];

	path = search("PATH").data;
	args = make_args(command, input->argv);
	pipe(filedes);
	p = fork();
	if (p == 0)
	{
		dup2(filedes[1], STDERR_FILENO);
		run_cmd_exec2(dir, path, args, command);
	}
	close(filedes[1]);
	output->stderr = read_fd(filedes, false);
	waitpid(p, &filedes[1], 0);
	free(args);
	return (WEXITSTATUS(filedes[1]));
}

void	next_dir2(bool reset, int *path_pos, char *path, int *size)
{
	if (reset)
		*path_pos = 0;
	if ((size_t)path_pos >= ft_strlen(path))
		return (NULL);
	*size = 0;
	while (path[*path_pos + *size] && path[*path_pos + *size] != ':')
		*size += 1;
}

char	*next_dir(bool reset, const char *path, char *command)
{
	char		*new_dir;
	int			size;
	int			pos;
	int			cmd_pos;
	static int	path_pos = 0;

	pos = 0;
	new_dir = malloc(sizeof(char) * (size + ft_strlen(command) + 1));
	while (pos < size)
	{
		new_dir[pos] = path[path_pos + pos];
		pos++;
	}
	new_dir[pos] = '/';
	pos++;
	cmd_pos = 0;
	while (command[cmd_pos])
	{
		new_dir[pos + cmd_pos] = command[cmd_pos];
		cmd_pos++;
	}
	new_dir[pos + cmd_pos] = 0;
	path_pos += size + 1;
	return (new_dir);
}

char	**make_args(char *command, char **args)
{
	char	**newargs;
	int		size;
	int		pos;

	size = 0;
	while (args[size] != NULL)
		size++;
	newargs = malloc(sizeof(char *) * (size + 1));
	newargs[0] = command;
	pos = 1;
	while (pos < size + 1)
	{
		newargs[pos] = args[pos - 1];
		pos++;
	}
	newargs[pos] = NULL;
	return (newargs);
}
