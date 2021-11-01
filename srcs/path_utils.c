#include "../includes/pipex.h"

void	execute_cmd(t_data *vars)
{
	execve(vars->c_path, vars->cmd, vars->envp);
	perror("execve");
}

void	get_path_index(t_data *vars, char *cmd)
{
	int		check;
	char	*tmp;

	check = 0;
	vars->index = 0;
	vars->cmd = ft_split(cmd, ' ');
	while (vars->path[vars->index++])
	{
		vars->c_path = ft_strjoin(vars->path[vars->index], "/");
		tmp = vars->c_path;
		free(vars->c_path);
		vars->c_path = ft_strjoin(tmp, vars->cmd[0]);
		if (access(vars->c_path, X_OK) == 0 && ++check)
			break ;
		free(vars->c_path);
	}
	if (check != 0)
		execute_cmd(vars);
	else
	{
		write(1, "Error: Invalid command\n", 23);
		ft_free_mtx(vars);
		exit(1);
	}
}
