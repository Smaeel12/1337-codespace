/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:15:21 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/06 21:06:06 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*join_path_to_cmd(char *path, char *cmd)
{
	char	*line;
	int		path_len;
	int		cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	line = malloc(path_len + cmd_len + 2 * sizeof(char));
	ft_strlcpy(line, path, path_len + 1);
	line[path_len] = '/';
	ft_strlcpy(line + path_len + 1, cmd, cmd_len + 1);
	return (line);
}

t_cmd	find_cmd(char **paths, char *cmd)
{
	t_cmd	data;
	int		i;

	i = 0;
	data.args = ft_split(cmd, ' ');
	data.cmd = ft_strdup(data.args[0]);
	if (data.cmd[0] == '/')
		return (data);
	while (paths && paths[i])
	{
		if (!access(data.cmd, X_OK))
			return (data);
		free(data.cmd);
		data.cmd = join_path_to_cmd(paths[i], data.args[0]);
		i++;
	}
	return (data);
}

char	**extract_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

t_fds	init_fds(char *infile, char *outfile)
{
	t_fds	fds;

	fds = (t_fds){0};
	fds.in_out[IN] = open(infile, O_RDONLY);
	fds.in_out[OUT] = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fds.in_out[IN] == -1 && fds.in_out[OUT] == -1)
		return (perror(infile), perror(outfile), exit(EXIT_FAILURE), fds);
	if (fds.in_out[IN] == -1)
		return (perror(infile), exit(EXIT_SUCCESS), fds);
	if (fds.in_out[OUT] == -1)
		return (perror(outfile), exit(EXIT_FAILURE), fds);
	if (pipe(fds.pipefds) == -1)
		return (perror("Pipe"), exit(EXIT_FAILURE), fds);
	return (fds);
}

int	child_execute(t_cmd cmd, int in_file, int out_file)
{
	int	pid;
	int	status;

	if (access(cmd.cmd, X_OK))
		return (error_message(ft_strjoin(cmd.args[0], CMD_ERR)), clear_child(cmd, in_file, out_file), 127);
	pid = fork();
	if (pid < 0)
		return (error_message(ft_strjoin("Fork", strerror(errno))), clear_child(cmd, in_file, out_file), 1);
	if (pid == 0)
	{
		dup2(in_file, 0);
		dup2(out_file, 1);
		close(in_file);
		close(out_file);
		if (execve(cmd.cmd, cmd.args, NULL) == -1)
			exit(1);
	}
	clear_child(cmd, in_file, out_file);
	wait(&status);
	if (WEXITSTATUS(status))
		return (1);
	return (0);
}
