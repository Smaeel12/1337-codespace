/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:52:33 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/10 23:51:27 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int here_doc(char **cmds, char **paths, t_file file, char *limiter)
{
	int pipefds[2];
	char *line;
	int status;

	if (pipe(pipefds) == -1)
		return 1;
	line = get_next_line(0);
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter)))
	{
		ft_putstr_fd(line, pipefds[WRITE]);
		free(line);
	}
	free(line);
	close(pipefds[WRITE]);
	dup2(pipefds[READ], STDIN_FILENO);
	if (pipe(pipefds) == -1)
		return 1;
	dup2(pipefds[WRITE], STDOUT_FILENO);
	status = child_execute(find_cmd(paths, cmds[0]));
	dup2(pipefds[READ], STDIN_FILENO);
	dup2(file.out, STDOUT_FILENO);
	status = child_execute(find_cmd(paths, cmds[0]));
	return status;
}

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

	if (ac == 6 && !ft_strncmp(av[1], "here_doc", 9))
	{
		file = init_files(av[1], av[ac - 1]);
		av[ac - 1] = NULL;
		paths = extract_paths(envp);
		status = here_doc(&av[3], paths, file, av[2]);
		close(file.in);
		close(file.out);
		return (clear_paths(paths), status | file.err);
	}
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
