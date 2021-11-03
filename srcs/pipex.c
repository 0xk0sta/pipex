#include "../includes/pipex.h"
#include <sys/wait.h>

static void	here_doc_handler(t_data *vars, char *delimiter)
{
	char	*del;

	if (pipe(vars->fd) == -1)
		exit(ft_error(vars, 2));
	vars->c_pid = fork();
	if (vars->c_pid == -1)
		exit(ft_error(vars, 3));
	if (vars->c_pid == 0)
	{
		close(vars->fd[0]);
		del = ft_strjoin(delimiter, "\n");
		vars->line = get_next_line(STDIN_FILENO);
		while (vars->line)
		{
			if (ft_strncmp(vars->line, del, ft_strlen(del) + 1) == 0)
			{
				close(vars->fd[1]);
				free(vars->line);
				exit(0);
			}
			fill_stdin(vars);
		}
	}
	else
		close_and_wait(vars);
}

static void	init_struct(t_data *vars)
{
	vars->c_path = NULL;
	vars->index = 0;
	vars->path = NULL;
	vars->outfile = NULL;
	vars->infile = NULL;
	vars->envp = NULL;
}

static void	pipe_handler(t_data *vars, char *cmd)
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
		close(vars->fd[1]);
		get_path_index(vars, cmd);
	}
	else
	{
		close(vars->fd[1]);
		dup2(vars->fd[0], STDIN_FILENO);
		close(vars->fd[0]);
		waitpid(vars->c_pid, NULL, 0);
	}
}

void	pipex(t_data *vars, char **cmd, int argc, int i)
{
	while (i < (argc - 2))
		pipe_handler(vars, cmd[i++]);
	dup2(vars->out_fd, STDOUT_FILENO);
	close(vars->out_fd);
	get_path_index(vars, cmd[i]);
}

void leaks()
{
	system("lsof -c pipex");
	system("leaks -q pipex");
}

int	main(int argc, char **argv)
{
	t_data		vars;
	extern char	**environ;

	atexit(leaks);
	if (argc < 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
		return (0);
	}
	init_struct(&vars);
	simple_parse(argv, &vars, environ, argc);
	if (argc >= 5 && ft_strcmp(argv[1], "here_doc") != 0)
	{
		open_files(&vars);
		dup2(vars.in_fd, STDIN_FILENO);
		close(vars.in_fd);
		pipex(&vars, argv, argc, 2);
	}
	else if (argc > 5 && ft_strcmp(argv[1], "here_doc") == 0)
	{
		here_doc_handler(&vars, argv[2]);
		vars.out_fd = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		pipex(&vars, argv, argc, 3);
	}
}
