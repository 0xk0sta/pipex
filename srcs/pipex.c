#include "../includes/pipex.h"
#include <sys/wait.h>

void	init_struct(t_data *vars)
{
	vars->c_path = NULL;
	vars->index = 0;
	vars->path = NULL;
	vars->outfile = NULL;
	vars->infile = NULL;
	vars->envp = NULL;
}

void	pipe_handler(t_data *vars, char *cmd)
{
	if (pipe(vars->fd) == -1)
		exit(ft_error(vars, 2));
	vars->c_pid = fork();
	if (vars->c_pid == -1)
		exit(ft_error(vars, 3));
	if (vars->c_pid == 0)
	{
		close(vars->fd[0]);
		dup2(vars->fd[1], STDOUT_FILENO);
		get_path_index(vars, cmd);
	}
	else
	{
		close(vars->fd[1]);
		dup2(vars->fd[0], STDIN_FILENO);
		waitpid(vars->c_pid, NULL, 0);
	}
}

void	pipex(t_data *vars, char **cmd, int argc)
{
	int	i;

	if (argc >= 5 && ft_strcmp(cmd[1], "here_doc") != 0)
	{
		i = 2;
		while (i < (argc - 2))
			pipe_handler(vars, cmd[i++]);
		dup2(vars->out_fd, STDOUT_FILENO);
		get_path_index(vars, cmd[argc - 2]);
	}
	else if (argc > 5 && ft_strcmp(cmd[1], "here_doc") != 0)
		;
	else if (argc > 5 && ft_strcmp(cmd[1], "here_doc") == 0)
		;
}

void leaks()
{
	system("lsof -c pipex");
}

int	main(int argc, char **argv)
{
	t_data		vars;
	extern char	**environ;

	atexit(leaks);
	if (argc < 5)
	{
		write(1, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
		return (0);
	}
	else
	{
		init_struct(&vars);
		simple_parse(argv, &vars, environ, argc);
		open_files(&vars);
		dup2(vars.in_fd, STDIN_FILENO);
		pipex(&vars, argv, argc);
	}
	system("lsof -c pipex");
}
