/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:15:21 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/04 18:07:42 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	t_cmd data;
	int i;

	i = 0;
	data.args = ft_split(cmd, ' ');
	data.cmd = ft_strdup(data.args[0]);
	if (data.cmd[0] == '/')
		return (data);
	while (paths[i])
	{
		if (!access(data.cmd, X_OK))
			return (data);
		free(data.cmd);
		data.cmd = join_path_to_cmd(paths[i], data.args[0]);
		i++;
	}
	return (data);
}

int clear_ptrs(char *ptr, char **ptr2)
{
	int i;

	i = 0;
	free(ptr);
	while (ptr2 && ptr2[i])
		free(ptr2[i++]);
	free(ptr2);
	return 0;
}
int exit_prog(char **paths, t_cmd *cmd, char *message)
{
	if (message)
		write(2, message, ft_strlen(message));
	if (cmd)
		clear_ptrs(cmd->cmd, cmd->args);
	if (paths)
		clear_ptrs(NULL, paths);
	exit(message != NULL);
}
