/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:15:21 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/12 08:54:41 by iboubkri         ###   ########.fr       */
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
	if (!data.args[0])
		return (data.cmd = ft_strdup(""), data);
	if (data.args[0][0] == '/' || data.args[0][1] == '/')
		return (data.cmd = ft_strdup(data.args[0]), data);
	data.cmd = ft_strdup(data.args[0]);
	while (data.args[0] && paths && paths[i])
	{
		if (!access(data.cmd, X_OK))
			return (data);
		free(data.cmd);
		data.cmd = join_path_to_cmd(paths[i], data.args[0]);
		i++;
	}
	free(data.cmd);
	data.cmd = ft_strdup(data.args[0]);
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

t_file	init_files(char *infile, char *outfile)
{
	t_file	file;

	file.err = 0;
	file.in = open(infile, O_RDONLY);
	file.out = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file.in == -1)
	{
		perror(infile);
		file.in = open("/dev/null", O_RDONLY);
	}
	if (file.out == -1)
	{
		perror(outfile);
		file.out = open("/dev/null", O_CREAT | O_TRUNC | O_WRONLY, 0644);
		file.err = 1;
	}
	return (file);
}

int	child_execute(t_cmd cmd, int infile, int outfile)
{
	int	status;
	int	pid;

	if (!cmd.cmd || access(cmd.cmd, X_OK))
	{
		write(2, cmd.cmd, ft_strlen(cmd.cmd));
		write(2, CMD_ERR, ft_strlen(CMD_ERR));
		return (clear_cmd(cmd), close(infile), close(outfile), COM_NOT_FOUND);
	}
	pid = fork();
	if (pid < -1)
		return (perror("Fork"), 1);
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		if (execve(cmd.cmd, cmd.args, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	close(infile);
	close(outfile);
	wait(&status);
	clear_cmd(cmd);
	return (WEXITSTATUS(status));
}
