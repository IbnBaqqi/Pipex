/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:09:53 by sabdulba          #+#    #+#             */
/*   Updated: 2024/12/08 17:13:51 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
//pipe is FIFO

//check if file exist, check exists but no x, check execve
void	exec(char *cmd, char **env)
{
	char	**n_cmd;
	char	*path;

	n_cmd = ft_splitplus(cmd, ' ');
	path = get_path(n_cmd[0], env);
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(n_cmd[0], 2);
		free_tab(n_cmd);
		exit(127);
	}
	if (execve(path, n_cmd, env) == -1 || (access(path, X_OK) == -1))
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(n_cmd[0], 2);
		free_tab(n_cmd);
		exit(126);
	}
}
/* void check_char(char )
{
	
} */

void	child(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		ft_printf("./pipex file1 cmd1 cmd2 file2\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(p_fd) == -1)
	{
		perror("Pipe creation failed");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child(av, p_fd, env);
	parent(av, p_fd, env);
}
