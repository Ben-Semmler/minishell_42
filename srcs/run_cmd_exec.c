/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:31:00 by marvin            #+#    #+#             */
/*   Updated: 2022/11/15 18:05:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_dir(bool reset, const char *PATH, char *command);
char	**make_args(char *command, char **args);
bool	does_stdout_swp_exist(void);

void	run_cmd_exec2(char *path, char **args, char *command)
{
	char	*dir;

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
	char	**args;
	pid_t	p;
	int		filedes[2];
	int		wstatus;

	path = search("PATH").data;
	args = make_args(command, input->argv);
	pipe(filedes);
	p = fork();
	if (p == 0)
	{
		dup2(filedes[1], STDERR_FILENO);
		run_cmd_exec2(path, args, command);
	}
	close(filedes[1]);
	output->stderr = read_fd(filedes, false);
	waitpid(p, &wstatus, 0);
	free(args);
	return (WEXITSTATUS(wstatus));
}

char	*next_dir2(char *command, int *size, int *path_pos, const char *path)
{
	char	*new_dir;
	int		cmd_pos;
	int		pos;

	new_dir = malloc(sizeof(char) * (*size + ft_strlen(command) + 1));
	pos = 0;
	while (pos < *size)
	{
		new_dir[pos] = path[*path_pos + pos];
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
	*path_pos += *size + 1;
	return (new_dir);
}

char	*next_dir(bool reset, const char *path, char *command)
{
	int			size;
	static int	path_pos = 0;

	if (reset)
		path_pos = 0;
	if ((size_t)path_pos >= ft_strlen(path))
		return (NULL);
	size = 0;
	while (path[path_pos + size] && path[path_pos + size] != ':')
		size++;
	return (next_dir2(command, &size, &path_pos, path));
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
