/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:40:38 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/06 21:06:36 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int error_message(char *message)
{
	if (!message)
		return 0;
	write(2, message, ft_strlen(message));
	free(message);
	return 1;
}
int	clear_child(t_cmd cmd, int fd1, int fd2)
{
	int	i;

	i = 0;
	close(fd1);
	close(fd2);
	free(cmd.cmd);
	while (cmd.args[i])
		free(cmd.args[i++]);
	free(cmd.args);
	return (0);
}

int	clear_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
		free(paths[i++]);
	free(paths);
	return (0);
}
