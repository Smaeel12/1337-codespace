/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:46:06 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/12 23:57:05 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
