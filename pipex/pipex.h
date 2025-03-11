/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:52:57 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/09 19:25:32 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define IN 0
#define OUT 1
#define READ 0
#define WRITE 1

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}			t_cmd;

typedef struct s_file
{
	int		in;
	int		out;
	int		err;
}			t_file;

#define USAGE_ERR "Usage: ./pipex file1 cmd1 cmd2 file2\ncle"
#define CMD_ERR ": command not found\n"

char		*join_path_to_cmd(char *path, char *cmd);
t_cmd		find_cmd(char **paths, char *cmd);
char		**extract_paths(char **envp);
// int			run_cmd(char **cmds, char **paths, t_file file);
int			child_execute(t_cmd cmd);

t_file		init_files(char *infile, char *outfile);
int			clear_cmd(t_cmd cmd);
int			clear_paths(char **paths);
