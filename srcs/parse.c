#include "../includes/pipex.h"

void	simple_parse(char **args, t_data *vars, char **envp, int argc)
{
	int		i;
	char	*tmp;

	i = 0;
	vars->infile = ft_strdup(args[1]);
	vars->outfile = ft_strdup(args[argc - 1]);
	vars->envp = envp;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	tmp = ft_substr(envp[i], 5, (ft_strlen(envp[i]) - 5));
	vars->path = ft_split(tmp, ':');
	free(tmp);
}

void	open_files(t_data *vars)
{
	vars->in_fd = open(vars->infile, O_RDONLY);
	if (vars->in_fd <= 0)
	{
		write(1, "Error: Invalid infile\n", 22);
		free(vars->infile);
		free(vars->outfile);
		ft_free_mtx(vars);
		exit(1);
	}
	vars->out_fd = open(vars->outfile, O_RDWR | O_TRUNC);
	if (vars->out_fd <= 0)
	{
		vars->out_fd = open(vars->outfile, O_CREAT | O_TRUNC, 0644);
		if (vars->out_fd <= 0)
		{
			write(1, "Error: Couldn't create outfile\n", 31);
			ft_free_mtx(vars);
			free(vars->infile);
			free(vars->outfile);
			exit(1);
		}
	}
	free(vars->infile);
	free(vars->outfile);
}
