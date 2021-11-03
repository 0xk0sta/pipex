#include "../includes/pipex.h"

int	is_path_set(char **envp)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			j++;
			break ;
		}
	}
	if (j == 0)
		return (-1);
	return (i);
}

void	simple_parse(char **args, t_data *vars, char **envp, int argc)
{
	int		i;
	char	*tmp;

	if (ft_strncmp(args[1], "here_doc", 8) != 0)
	{
		vars->infile = ft_strdup(args[1]);
		vars->outfile = ft_strdup(args[argc - 1]);
	}
	vars->envp = envp;
	i = is_path_set(envp);
	if (i < 0)
	{
		vars->path = NULL;
		return ;
	}
	else
	{
		tmp = ft_substr(envp[i], 5, (ft_strlen(envp[i]) - 5));
		vars->path = ft_split(tmp, ':');
		free(tmp);
	}
}

void	open_files(t_data *vars)
{
	vars->in_fd = open(vars->infile, O_RDONLY);
	if (vars->in_fd <= 0)
	{
		write(2, "Error: Invalid infile\n", 22);
		free(vars->infile);
		free(vars->outfile);
		ft_free_mtx(vars);
		exit(1);
	}
	vars->out_fd = open(vars->outfile, O_WRONLY | O_TRUNC);
	if (vars->out_fd <= 0)
	{
		vars->out_fd = open(vars->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (vars->out_fd <= 0)
		{
			write(2, "Error: Couldn't create outfile\n", 31);
			ft_free_mtx(vars);
			free(vars->infile);
			free(vars->outfile);
			exit(1);
		}
	}
	free(vars->infile);
	free(vars->outfile);
}
