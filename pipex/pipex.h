/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:52:57 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 15:27:35 by iboubkri         ###   ########.fr       */
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
#define COMMAND_NOT_FOUND 127
#define BASIC_USAGE_ERR "Usage:\n\t./pipex file1 cmd1 cmd2 file2\n"
#define BONUS_USAGE_ERR \
	"Usage:\n\t./pipex file1 cmd1 cmd2 file2\n\t./pipex here_doc \
LIMITER cmd cmd1 file\n"
#define CMD_ERR ": Command not found\n"
#define FILE_ERR ": No such file or directory\n"
#define PIPE_ERR "Error: Unable to create pipe\n"
#define LIMITER_ERR "Error: Missing here_doc limiter\n"

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
