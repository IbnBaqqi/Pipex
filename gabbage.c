/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gabbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:40:33 by sabdulba          #+#    #+#             */
/*   Updated: 2024/12/08 12:40:34 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
if (access(file, F_OK) == -1)
		{
			ft_putstr_fd("pipex: no such file or directory: ", 2);
			ft_putendl_fd(file, 2);
			exit(EXIT_FAILURE);
		}
		if (access(file, R_OK) == -1)
		{
			ft_putstr_fd("pipex: permission denied: ", 2);
			ft_putendl_fd(file, 2);
			exit(EXIT_FAILURE);
		}

if (access(file, R_OK) == -1)
		{
			ft_putstr_fd("pipex: permission denied: ", 2);
			ft_putendl_fd(file, 2);
			exit(1);
		}
		if (access(file, W_OK) == -1)
		{
			ft_putstr_fd("pipex: permission denied: ", 2);
			ft_putendl_fd(file, 2);
			exit(1);
		}
*/