/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:01:17 by sabdulba          #+#    #+#             */
/*   Updated: 2024/12/08 12:42:21 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	open_file(char *file, int in_or_out)
{
	int	res;

	if (in_or_out == 0)
	{
		check_file_access(file, F_OK, "no such file or directory: ", 0);
		check_file_access(file, R_OK, "permission denied: ", 0);
		res = open(file, O_RDONLY, 0777);
	}
	if (in_or_out == 1)
	{
		check_file_access(file, R_OK, "permission denied: ", 0);
		check_file_access(file, W_OK, "permission denied: ", 0);
		res = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if (res == -1)
		exit(EXIT_FAILURE);
	return (res);
}

//i_or_o for fd
void	check_file_access(char *file, int mode, char *error_msg, int i_or_o)
{
	if (i_or_o == 0 && access(file, mode) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(error_msg, 2);
		ft_putendl_fd(file, 2);
		exit(EXIT_FAILURE);
	}
	if (i_or_o == 1 && access(file, mode) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(error_msg, 2);
		ft_putendl_fd(file, 2);
		exit(1);
	}
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**cmd_parts;

	i = -1;
	allpath = ft_split(ft_getenv("PATH", env), ':');
	cmd_parts = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd_parts[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_tab(cmd_parts);
			return (exec);
		}
		free(exec);
	}
	free_tab(allpath);
	free_tab(cmd_parts);
	return (cmd);
}
