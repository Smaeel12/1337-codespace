/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:44:29 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/04 18:05:38 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft/libft/libft.h"
# include "libft/printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

# define IN 0
# define OUT 1
# define READ 0
# define WRITE 1

# define FORK_FAILED "\033[31;1mError\033[0;   \nFailed to fork\n"
# define USAGE_ERROR "\033[31;1mError\033[0;   \nUsage: ./pipex ...\n"
# define EXECVE_FAILED "\033[31;1mError\033[0; \nUsage:Execve Failed\n"

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}			t_cmd;


char	**extract_paths(char **envp);
char	*join_path_to_cmd(char *path, char *cmd);
t_cmd	find_cmd(char **paths, char *cmd);
int		clear_ptrs(char *ptr, char **ptr2);
int		exit_prog(char **paths, t_cmd *cmd, char *message);

#endif