#include "../includes/pipex.h"

void	ft_free_mtx(t_data *vars)
{
	int	i;

	i = -1;
	while (vars->path[++i])
		free(vars->path[i]);
	free(vars->path);
}
