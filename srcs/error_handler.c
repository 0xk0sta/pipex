#include "../includes/pipex.h"

int	ft_error(t_data *vars, int etype)
{
	if (etype == 1)
	{
		ft_free_mtx(vars);
		return (1);
	}
	if (etype == 2)
	{
		ft_free_mtx(vars);
		return (1);
	}
	if (etype == 3)
	{
		ft_free_mtx(vars);
		close(vars->fd[0]);
		close(vars->fd[0]);
		return (1);
	}
	return (0);
}
