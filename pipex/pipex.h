/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:52:57 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/06 21:16:18 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define IN 0
#define OUT 1
#define READ 0
#define WRITE 1

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}			t_cmd;

typedef struct s_fds
{
	int		in_out[2];
	int		pipefds[2];
}			t_fds;

#define USAGE_ERR "Usage: ./pipex file1 cmd1 cmd2 file2\ncle"
#define CMD_ERR ": command not found\n"

char		*join_path_to_cmd(char *path, char *cmd);
t_cmd		find_cmd(char **paths, char *cmd);
char		**extract_paths(char **envp);
t_fds		init_fds(char *infile, char *outfile);
int			child_execute(t_cmd cmd, int in_file, int out_file);

int error_message(char *message);
int	clear_child(t_cmd cmd, int fd1, int fd2);
int	clear_paths(char **paths);
