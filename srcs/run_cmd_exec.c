#include "minishell.h"

char	*next_dir(bool reset, const char *path, char *command);
char	**make_args(char *command, char **args);
bool	does_stdout_swp_exist(void);

int	run_cmd_exec2(char **args, pid_t	*p, int *filedes, t_inputs *input)
{
	char	*path;
	char	*dir;

	path = search("PATH").data;
	pipe(*filedes);
	*p = fork();
	if (*p == 0)
	{
		dup2(filedes[1], STDERR_FILENO);
		dir = next_dir(true, path, command);
		while (dir != NULL)
		{
			execve(dir, args, NULL);
			free(dir);
			dir = next_dir(false, path, command);
		}
		return (1);
	}
	return (0);
}

int	run_cmd_exec(char *command, t_inputs *input, t_outputs *output)
{
	char	**args;
	pid_t	p;
	int		filedes[2];
	int		wstatus;

	args = make_args(command, input->argv);
	if (run_cmd_exec2(args, &p, &filedes, input))
	{
		perror(ft_joinfree("minishell: ", 0,
				ft_strjoin(command, ": command not found"), 1));
		exit(127);
	}
	close(filedes[1]);
	output->stderr = read_fd(filedes, false);
	waitpid(p, &wstatus, 0);
	free(args);
	return (WEXITSTATUS(wstatus));
}

char	*next_dir(bool reset, const char *PATH, char *command)
{
	char		*new_dir;
	int			size;
	int			pos;
	int			cmd_pos;
	static int	path_pos = 0;

	if (reset)
		path_pos = 0;
	if ((size_t)path_pos >= ft_strlen(PATH))
		return (NULL);
	size = 0;
	while (PATH[path_pos + size] && PATH[path_pos + size] != ':')
		size++;
	new_dir = malloc(sizeof(char) * (size + ft_strlen(command) + 1));
	pos = 0;
	while (pos < size)
	{
		new_dir[pos] = PATH[path_pos + pos];
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
