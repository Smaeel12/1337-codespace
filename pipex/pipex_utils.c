/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:15:21 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/14 00:23:32 by iboubkri         ###   ########.fr       */
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
	cmd = ft_strtrim(cmd, " \t");
	if (cmd[0] == '\0')
		return (write(2, CMD_ERR, ft_strlen(CMD_ERR)), free(cmd),
			(t_cmd){NULL});
	data.args = ft_split(cmd, ' ');
	data.cmd = ft_strdup(data.args[0]);
	if ((cmd[0] == '/' || cmd[1] == '/') && (access(data.cmd, X_OK) == -1))
		return (write(2, data.args[0], ft_strlen(data.args[0])), write(2,
				FILE_ERR, ft_strlen(FILE_ERR)), free(cmd), data);
	if (cmd[0] == '/' || cmd[1] == '/')
		return (free(cmd), data);
	while (data.args[0] && paths && paths[i])
	{
		if (!access(data.cmd, X_OK))
			return (free(cmd), data);
		free(data.cmd);
		data.cmd = join_path_to_cmd(paths[i], data.args[0]);
		i++;
	}
	return (write(2, cmd, ft_strlen(cmd)), write(2, CMD_ERR, ft_strlen(CMD_ERR))
		, clear_cmd(data), free(cmd), (t_cmd){NULL});
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

	if (!cmd.cmd || access(cmd.cmd, X_OK) == -1)
		return (close(infile), close(outfile), clear_cmd(cmd), 127);
	pid = fork();
	if (pid < -1)
		return (perror("Fork"), 1);
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(infile);
		close(outfile);
		if (execve(cmd.cmd, cmd.args, NULL) == -1)
			return (perror(cmd.args[0]), clear_cmd(cmd), exit(EXIT_FAILURE), 1);
	}
	close(infile);
	close(outfile);
	wait(&status);
	clear_cmd(cmd);
	return (WEXITSTATUS(status));
}
