#include "../includes/pipex.h"

static int	get_path(t_data *vars, int check)
{
	char	*tmp;

	vars->index = -1;
	while (vars->path[++vars->index])
	{
		vars->c_path = ft_strjoin(vars->path[vars->index], "/");
		tmp = ft_strdup(vars->c_path);
		free(vars->c_path);
		vars->c_path = ft_strjoin(tmp, vars->cmd[0]);
		free(tmp);
		if (access(vars->c_path, X_OK) == 0 && ++check)
			break ;
		free(vars->c_path);
	}
	return (check);
}

void	execute_cmd(t_data *vars, int check)
{
	if (check == 0)
		execve(vars->c_path, vars->cmd, vars->envp);
	if (check == 1)
		execve(vars->cmd[0], vars->cmd, vars->envp);
	perror("execve");
}

void	get_path_index(t_data *vars, char *cmd)
{
	int		check;

	check = 0;
	vars->cmd = ft_split(cmd, ' ');
	if (cmd[0] == '.' | cmd[0] == '~' | cmd[0] == '/'
		| access(vars->cmd[0], X_OK) == 0)
		execute_cmd(vars, 1);
	else
		check = get_path(vars, check);
	if (check != 0)
		execute_cmd(vars, 0);
	else
	{
		write(2, "Error: Invalid command\n", 23);
		ft_free_mtx(vars);
		exit(1);
	}
}
