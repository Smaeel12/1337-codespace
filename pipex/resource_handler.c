/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:46:06 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/10 22:34:14 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_file init_files(char *infile, char *outfile)
{
	t_file file;
	int devnull;

	file = (t_file){0};
	file.in = open(infile, O_RDONLY);
	file.out = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 644);
	devnull = open("/dev/null", O_RDONLY);
	if (file.in == -1)
	{
		perror(infile);
		file.in = devnull;
	}
	if (file.out == -1)
	{
		perror(outfile);
		file.out = devnull;
	}
	return (file);
}

int clear_cmd(t_cmd cmd)
{
	int i;

	i = 0;
	free(cmd.cmd);
	while (cmd.args[i])
		free(cmd.args[i++]);
	free(cmd.args);
	return (0);
}

int clear_paths(char **paths)
{
	int i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (0);
}
