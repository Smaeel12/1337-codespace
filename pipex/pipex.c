/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:52:33 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/15 20:36:49 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	t_file	file;
	int		pipefds[2];
	int		status;

	if (ac != 5)
		return (write(2, BASIC_USAGE_ERR, ft_strlen(BASIC_USAGE_ERR)), 1);
	if (pipe(pipefds) == -1)
		return (write(2, PIPE_ERR, ft_strlen(PIPE_ERR)), 1);
	file = init_files(av[1], av[ac - 1]);
	paths = extract_paths(envp);
	status = child_execute(find_cmd(paths, av[2]), file.in, pipefds[WRITE]);
	status = child_execute(find_cmd(paths, av[3]), pipefds[READ], file.out);
	wait(&status);
	clear_paths(paths);
	return (status | file.err);
}
