/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:41:20 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/16 21:50:59 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_heredoc_file(int *fd, char *limiter)
{
	int		pipefds[2];
	char	*line;

	if (pipe(pipefds) == -1)
		return (write(2, PIPE_ERR, ft_strlen(PIPE_ERR)), 1);
	while (1)
	{
		ft_printf("pipe heredoc> ");
		line = get_next_line(0);
		if (!line)
			write(2, LIMITER_ERR, ft_strlen(LIMITER_ERR));
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
			break ;
		write(pipefds[WRITE], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipefds[WRITE]);
	*fd = pipefds[READ];
	free(limiter);
	return (0);
}

int	run_cmds(char **paths, char **cmds, int *file)
{
	int	pipefds[2];
	int	*status;
	int	i;

	i = 0;
	status = (int [2]){0, 0};
	if (pipe(pipefds) == -1)
		return (write(2, PIPE_ERR, ft_strlen(PIPE_ERR)), 1);
	child_execute(find_cmd(paths, cmds[i++]), file[READ], pipefds[WRITE],
		pipefds[READ]);
	while (dup2(pipefds[READ], file[READ]) && cmds[i + 1])
	{
		close(pipefds[READ]);
		if (pipe(pipefds) == -1)
			return (write(2, PIPE_ERR, ft_strlen(PIPE_ERR)), 1);
		child_execute(find_cmd(paths, cmds[i++]), file[READ], pipefds[WRITE],
			pipefds[READ]);
	}
	close(file[READ]);
	status[0] = child_execute(find_cmd(paths, cmds[i]), pipefds[READ],
			file[WRITE], pipefds[WRITE]);
	i = 0;
	while (wait(&status[1]) > 0)
		;
	return (WEXITSTATUS(status[1]) | status[0]);
}

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	int		file[3];
	int		status;

	status = 0;
	if (ac < 5 || (av[1] && !ft_strncmp("here_doc", av[1], 9) && ac != 6))
		return (write(2, BONUS_USAGE_ERR, ft_strlen(BONUS_USAGE_ERR)), 1);
	paths = extract_paths(envp);
	if (!ft_strncmp("here_doc", av[1], 9))
	{
		init_heredoc_file(&file[READ], ft_strjoin(av[2], "\n"));
		file[ERR] = open_file(&file[WRITE], av[ac - 1],
				O_CREAT | O_TRUNC | O_WRONLY);
		av[ac - 1] = NULL;
		status = run_cmds(paths, &av[3], file) | status;
	}
	else
	{
		open_file(&file[READ], av[1], O_RDONLY);
		status = open_file(&file[WRITE], av[ac - 1],
				O_CREAT | O_TRUNC | O_WRONLY);
		av[ac - 1] = NULL;
		status = run_cmds(paths, &av[2], file) | status;
	}
	return (clear_paths(paths), status * !file[ERR] | file[ERR]);
}
