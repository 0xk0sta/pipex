#include "../includes/pipex.h"
#include <sys/wait.h>

void	here_doc_handler(t_data *vars, char *delimiter)
{
	if (pipe(vars->fd) == -1)
		exit(ft_error(vars, 2));
	vars->c_pid = fork();
	if (vars->c_pid == -1)
		exit(ft_error(vars, 3));
	if (vars->c_pid == 0)
	{
		close(vars->fd[0]);
		vars->line = get_next_line(STDIN_FILENO);
		write(vars->fd[1], &vars->line, ft_strlen(vars->line));
		while (vars->line)
		{
			vars->line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(vars->line, delimiter, ft_strlen(delimiter)) == 0)
				break ;
			write(vars->fd[1], &vars->line, ft_strlen(vars->line));
		}
	}
	else
	{
		close(vars->fd[1]);
		dup2(vars->fd[0], STDIN_FILENO);
		waitpid(vars->c_pid, NULL, 0);
	}
}

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

void	pipex(t_data *vars, char **cmd, int argc, int i)
{
	while (i < (argc - 2))
		pipe_handler(vars, cmd[i++]);
	dup2(vars->out_fd, STDOUT_FILENO);
	get_path_index(vars, cmd[argc - 2]);
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
	init_struct(&vars);
	simple_parse(argv, &vars, environ, argc);
	if (argc >= 5 && ft_strcmp(argv[1], "here_doc") != 0)
	{
		open_files(&vars);
		dup2(vars.in_fd, STDIN_FILENO);
		pipex(&vars, argv, argc, 2);
	}
	else if (argc > 5 && ft_strcmp(argv[1], "here_doc") == 0)
	{
		vars.out_fd = open(argv[argc - 1], O_APPEND | O_CREAT, 0644);
		here_doc_handler(&vars, argv[2]);
		pipex(&vars, argv, argc, 3);
	}
}
