#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
typedef struct s_data
{
	int		index;
	int		in_fd;
	int		out_fd;
	char	**cmd;
	char	*infile;
	char	*outfile;
	char	**path;
	char	*c_path;
	char	**envp;
	char	*line;
	pid_t	c_pid;
	int		new_stdin;
	int		new_stdout;
	int		new_stderr;
	int		fd[2];
}t_data;
void	ft_free_mtx(t_data *vars);
int		ft_error(t_data *vars, int etype);
int		check_file_access(t_data *vars);
void	simple_parse(char **args, t_data *vars, char **envp, int argc);
void	open_files(t_data *vars);
void	execute_cmd(t_data *vars, int check);
void	close_and_wait(t_data *vars);
void	fill_stdin(t_data *vars);
void	get_path_index(t_data *vars, char *cmd);
#endif
