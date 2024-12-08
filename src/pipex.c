/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:09:53 by sabdulba          #+#    #+#             */
/*   Updated: 2024/12/07 17:50:04 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
//pipe is FIFO
/* void	exec(char *cmd, char **env)
{
	char	**n_cmd;
	char	*path;

	n_cmd = ft_split(cmd, ' ');
	path = get_path(n_cmd[0], env);
	//ft_printf("%s\n", path);
/ 	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(n_cmd[0], 2);
		free_tab(n_cmd);
		exit(126);
	} // add the end comment later

	if (access(path, F_OK) == -1)  // File doesn't exist
    {
        ft_putstr_fd("pipex: command not found: ", 2);
        ft_putendl_fd(n_cmd[0], 2);
        free_tab(n_cmd);
        exit(127);  // Command not found
    }
	//try with else if
	if (execve(path, n_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(n_cmd[0], 2);
		free_tab(n_cmd);
		exit(127);
	}
} */

void exec(char *cmd, char **env)
{
    char **n_cmd;
    char *path;

    n_cmd = ft_split(cmd, ' ');
    path = get_path(n_cmd[0], env);

    if (access(path, F_OK) == -1) // File doesn't exist
    {
        ft_putstr_fd("pipex: command not found: ", 2);
        ft_putendl_fd(n_cmd[0], 2);
        free_tab(n_cmd);
        exit(127);
    }
    else if (access(path, X_OK) == -1) // File exists but no execute permissions
    {
        ft_putstr_fd("pipex: permission denied: ", 2);
        ft_putendl_fd(n_cmd[0], 2);
        free_tab(n_cmd);
        exit(126);
    }

    if (execve(path, n_cmd, env) == -1) // execve failed for other reasons
    {
        perror("pipex"); // Use perror to print the specific error
        free_tab(n_cmd);
        exit(127);
    }
}


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
