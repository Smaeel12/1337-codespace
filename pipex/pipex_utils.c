/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:15:21 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/09 20:23:27 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *join_path_to_cmd(char *path, char *cmd)
{
	char *line;
	int path_len;
	int cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	line = malloc(path_len + cmd_len + 2 * sizeof(char));
	ft_strlcpy(line, path, path_len + 1);
	line[path_len] = '/';
	ft_strlcpy(line + path_len + 1, cmd, cmd_len + 1);
	return (line);
}

t_cmd find_cmd(char **paths, char *cmd)
{
	t_cmd data;
	int i;

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

char **extract_paths(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

int child_execute(t_cmd cmd)
{
	int status;
	int pid;

	if (access(cmd.cmd, X_OK))
	{
		write(2, cmd.args[0], ft_strlen(cmd.args[0]));
		write(2, CMD_ERR, ft_strlen(CMD_ERR));
		return (clear_cmd(cmd), 1);
	}
	pid = fork();
	if (pid < -1)
		return (perror("Fork"), 1);
	if (pid == 0)
	{
		if (execve(cmd.cmd, cmd.args, NULL) == -1)
			exit(1);
	}
	wait(&status);
	clear_cmd(cmd);
	if (WEXITSTATUS(status))
		return (1);
	return (0);
}
