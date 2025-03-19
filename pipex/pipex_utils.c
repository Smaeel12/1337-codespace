/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:15:21 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/16 11:33:08 by iboubkri         ###   ########.fr       */
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
	data.status = 0;
	if (cmd[0] == '\0' || (!access(cmd, F_OK) && !ft_strchr(cmd, '/')))
		return (print_error(cmd, C_ERR), (t_cmd){NULL, NULL, 127});
	data.args = ft_split(cmd, ' ');
	if (!data.args[0])
		return (free(data.args), print_error(cmd, C_ERR), (t_cmd){NULL, NULL,
			127});
	data.cmd = ft_strdup(data.args[0]);
	if (ft_strchr(data.cmd, '/') && access(data.cmd, F_OK) == -1)
		return (print_error(data.cmd, F_ERR), data.status = 127, data);
	if (ft_strchr(data.cmd, '/') && access(data.cmd, X_OK) == -1)
		return (print_error(data.cmd, P_ERR), data.status = 126, data);
	while (paths && paths[i])
	{
		if (!access(data.cmd, X_OK))
			return (data);
		free(data.cmd);
		data.cmd = join_path_to_cmd(paths[i], data.args[0]);
		i++;
	}
	return (print_error(cmd, C_ERR), data.status = 127, data);
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

int	open_file(int *fd, char *file, int flags)
{
	*fd = open(file, flags, 0644);
	if (*fd == -1)
	{
		perror(file);
		*fd = open("/dev/null", flags, 0644);
		return (1);
	}
	return (0);
}

int	child_execute(t_cmd cmd, int infile, int outfile, int pipeend)
{
	int	pid;

	if (!cmd.cmd || access(cmd.cmd, X_OK) == -1)
		return (close(infile), close(outfile), clear_cmd(cmd), cmd.status);
	pid = fork();
	if (pid < -1)
		return (perror("Fork"), 1);
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(infile);
		close(outfile);
		close(pipeend);
		if (execve(cmd.cmd, cmd.args, NULL) == -1)
			return (perror(cmd.args[0]), clear_cmd(cmd), exit(EXIT_FAILURE), 1);
	}
	close(infile);
	close(outfile);
	clear_cmd(cmd);
	return (0);
}
