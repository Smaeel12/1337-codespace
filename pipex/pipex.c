/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:52:33 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/06 20:00:29 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	t_fds	fds;
	int		status;

	status = 0;
	if (ac > 4)
	{
		fds = init_fds(av[1], av[ac - 1]);
		paths = extract_paths(envp);
		status = child_execute(find_cmd(paths, av[2]), fds.in_out[IN],
				fds.pipefds[WRITE]);
		status = child_execute(find_cmd(paths, av[3]), fds.pipefds[READ],
				fds.in_out[OUT]);
		return (clear_paths(paths), status);
	}
	return (write(2, USAGE_ERR, ft_strlen(USAGE_ERR)), 1);
}
