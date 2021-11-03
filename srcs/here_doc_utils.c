#include "../includes/pipex.h"

void	close_and_wait(t_data *vars)
{
	close(vars->fd[1]);
	dup2(vars->fd[0], STDIN_FILENO);
	close(vars->fd[0]);
	waitpid(vars->c_pid, NULL, 0);
}

void	fill_stdin(t_data *vars)
{
	ft_putstr_fd(vars->line, vars->fd[1]);
	free(vars->line);
	vars->line = get_next_line(STDIN_FILENO);
}
