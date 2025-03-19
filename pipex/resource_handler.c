/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:46:06 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/16 02:12:43 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	print_error(char *cmd, char *error)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, error, ft_strlen(error));
	return (1);
}

int	clear_cmd(t_cmd cmd)
{
	int	i;

	i = 0;
	free(cmd.cmd);
	while (cmd.args && cmd.args[i])
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
