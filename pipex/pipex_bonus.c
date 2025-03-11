/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:41:20 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/10 22:40:53 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int run_cmd(char **cmds, char **paths, t_file file)
{
	int pipefds[2];
	int status;
	int i;

	i = 0;
	dup2(file.in, STDIN_FILENO);
	while (cmds[i])
	{
		if (!cmds[i + 1])
			dup2(file.out, STDOUT_FILENO);
		else
		{
			if (pipe(pipefds) == -1)
				return (1);
			dup2(pipefds[WRITE], STDOUT_FILENO);
		}
		status = child_execute(find_cmd(paths, cmds[i]));
		close(pipefds[WRITE]);
		dup2(pipefds[READ], STDIN_FILENO);
		i++;
	}
	return (status);
}

int main(int ac, char **av, char **envp)
{
	char **paths;
	t_file file;
	int status;

	if (ac > 4)
	{
		file = init_files(av[1], av[ac - 1]);
		av[ac - 1] = NULL;
		paths = extract_paths(envp);
		status = run_cmd(&av[2], paths, file);
		close(file.in);
		close(file.out);
		return (clear_paths(paths), status | file.err);
	}
	return (write(2, USAGE_ERR, ft_strlen(USAGE_ERR)), 1);
}
