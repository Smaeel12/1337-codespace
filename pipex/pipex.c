/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:52:33 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/16 21:08:32 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	int		file[3];
	int		pipefds[2];
	int		status;

	if (ac != 5)
		return (write(2, BASIC_USAGE_ERR, ft_strlen(BASIC_USAGE_ERR)), 1);
	if (pipe(pipefds) == -1)
		return (write(2, PIPE_ERR, ft_strlen(PIPE_ERR)), 1);
	paths = extract_paths(envp);
	open_file(&file[READ], av[1], O_RDONLY);
	child_execute(find_cmd(paths, av[2]), file[READ], pipefds[WRITE],
		pipefds[READ]);
	file[ERR] = open_file(&file[WRITE], av[ac - 1],
			O_CREAT | O_WRONLY | O_TRUNC);
	status = child_execute(find_cmd(paths, av[3]), pipefds[READ], file[WRITE],
			pipefds[WRITE]);
	clear_paths(paths);
	wait(&status);
	wait(&status);
	return (status * !file[ERR] | file[ERR]);
}
