/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:52:57 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/12 08:13:02 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

/* MACROS */
#define READ 0
#define WRITE 1
#define COM_NOT_FOUND 127
#define USAGE_ERR "Usage: ./pipex file1 cmd1 cmd2 file2\n"
#define CMD_ERR ": command not found\n"
#define PIPE_ERR "Pipe error\n"
#define LIMITER_ERR "Missing here_doc Limiter\n"

/* STRUCTS*/
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

/* PROTOTYPES */
char		*join_path_to_cmd(char *path, char *cmd);
t_cmd		find_cmd(char **paths, char *cmd);
char		**extract_paths(char **envp);

t_file		init_files(char *infile, char *outfile);
int			child_execute(t_cmd cmd, int infile, int outfile);

int			clear_cmd(t_cmd cmd);
int			clear_paths(char **paths);
