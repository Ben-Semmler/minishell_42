#include "minishell.h"

char	*back_dir(char *cwd);
char	**make_args(char *command, char **args);

int	run_cmd_exec(char *command, t_inputs *input, t_outputs *output)
{
	char	*cwd;
	char	*cwdcmd;
	char	**args;
	pid_t	p;
	int		filedes[2];
	int		wstatus;

	//Create buffer with size of PATH_MAX, fill using getcwd to get
	//the working directory
	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
	{
		free(cwd);
		//output->stderr = ft_joinfree("./", 0, ft_strjoin(input->argv[0]""))
		return (1);
	}
	args = make_args(command, input->argv);
	pipe(filedes);
	p = fork();

	bool	islinux = true;
	if (p == 0)
	{
		while ((dup2(filedes[1], STDERR_FILENO) == -1) && (errno == EINTR))
			;
		if (!islinux)
		{
			while (cwd != NULL)
			{
				cwdcmd = ft_joinfree(cwd, 0, ft_strjoin("/", command), 1);
				execve(cwdcmd, args, NULL);
				free(cwdcmd);
				cwd = back_dir(cwd);
			}
		}
		else
			execve(ft_strjoin("/usr/sbin/", command), args, NULL);
		perror(ft_joinfree("minishell: ", 0, ft_strjoin(command, ": command not found"), 1));
		exit(127);
	}
	close(filedes[1]);
	output->stderr = read_fd(filedes, false);
	waitpid(p, &wstatus, 0);
	free(cwd);
	free(args);
	return (WEXITSTATUS(wstatus));
}

char	*back_dir(char *cwd)
{
	char	*newcwd;
	int		size;
	int		pos;

	size = ft_strlen(cwd);
	while (cwd[size] != '/')
		size--;
	if (size == 0)
		return (NULL);
	newcwd = malloc(sizeof(char) * size);
	pos = 0;
	while (pos < size)
	{
		newcwd[pos] = cwd[pos];
		pos++;
	}
	newcwd[pos] = 0;
	free(cwd);
	return (newcwd);
}

char	**make_args(char *command, char **args)
{
	char	**newargs;
	int		size;
	int		pos;

	size = 0;
	while (args[size] != NULL)
		size++;
	newargs = malloc(sizeof(char*) * (size + 1));
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
