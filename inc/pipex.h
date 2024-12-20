/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:09:37 by sabdulba          #+#    #+#             */
/*   Updated: 2024/12/08 17:16:57 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include <fcntl.h>
# include <sys/types.h>

# include "../lib/libft/inc/libft.h"

void	exec(char *cmd, char **env);
int		open_file(char *file, int in_or_out);
void	free_tab(char **tab);
char	*ft_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	check_file_access(char *file, int mode, char *error_msg, int i_or_o);

char	**ft_splitplus(char const *s, char c);

#endif