/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:52:57 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/16 20:59:39 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

/* MACROS */
# define READ 0
# define WRITE 1
# define ERR 2

# define COMMAND_NOT_FOUND 127
# define BASIC_USAGE_ERR "Usage:\n\t./pipex file1 cmd1 cmd2 file2\n"
# define BONUS_USAGE_ERR \
	"Usage:\n\t./pipex file1 cmd1 cmd2 file2\n\t./pipex here_doc \
LIMITER cmd cmd1 file\n"
# define C_ERR ": Command not found\n"
# define P_ERR ": Permission denied\n"
# define F_ERR ": No such file or directory\n"
# define PIPE_ERR "Error: Unable to create pipe\n"
# define LIMITER_ERR "Error: Missing here_doc limiter\n"

/* STRUCTS*/
typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	int		status;
}			t_cmd;

/* PROTOTYPES */
char		*join_path_to_cmd(char *path, char *cmd);
t_cmd		find_cmd(char **paths, char *cmd);
char		**extract_paths(char **envp);

int			open_file(int *fd, char *file, int flags);
int			child_execute(t_cmd cmd, int infile, int outfile, int pipeend);
// int			child_execute(t_cmd cmd, int infile, int outfile, int pipeend);

int			clear_cmd(t_cmd cmd);
int			clear_paths(char **paths);
int			print_error(char *cmd, char *error);

#endif