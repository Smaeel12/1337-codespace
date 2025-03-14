/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:41:20 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/13 00:46:03 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_file	init_heredoc_files(char *limiter, char *outfile)
{
	int		pipefds[2];
	char	*line;
	t_file	file;

	file = (t_file){0};
	if (pipe(pipefds) == -1)
		return (write(2, PIPE_ERR, ft_strlen(PIPE_ERR)), file);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			write(2, LIMITER_ERR, ft_strlen(LIMITER_ERR));
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter)))
			break ;
		write(pipefds[WRITE], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipefds[WRITE]);
	file.in = pipefds[READ];
	file.out = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file.out == -1)
		return (perror(outfile), file.out = open("/dev/null",
				O_CREAT | O_TRUNC | O_WRONLY, 0644), file.err = 1, file);
	return (file);
}

int	run_cmds(char **paths, char **cmds, t_file file)
{
	int	pipefds[2];
	int	i;

	i = 0;
	if (pipe(pipefds) == -1)
		return (write(2, PIPE_ERR, ft_strlen(PIPE_ERR)), 1);
	child_execute(find_cmd(paths, cmds[i++]), file.in, pipefds[WRITE]);
	while (dup2(pipefds[READ], file.in) && cmds[i + 1])
	{
		close(pipefds[READ]);
		if (pipe(pipefds) == -1)
			return (write(2, PIPE_ERR, ft_strlen(PIPE_ERR)), 1);
		child_execute(find_cmd(paths, cmds[i++]), file.in, pipefds[WRITE]);
	}
	return (child_execute(find_cmd(paths, cmds[i]), pipefds[READ], file.out));
}

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	t_file	file;
	int		status;

	if ((av[1] && !ft_strncmp("here_doc", av[1], ft_strlen(av[1])) && ac != 6)
		|| (ac < 5))
		return (write(2, BONUS_USAGE_ERR, ft_strlen(BONUS_USAGE_ERR)), 1);
	paths = extract_paths(envp);
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		file = init_heredoc_files(av[2], av[ac - 1]);
		if (!file.in)
			return (clear_paths(paths), 0);
		av[ac - 1] = NULL;
		status = run_cmds(paths, &av[3], file);
	}
	else
	{
		file = init_files(av[1], av[ac - 1]);
		av[ac - 1] = NULL;
		status = run_cmds(paths, &av[2], file);
	}
	close(file.in);
	close(file.out);
	return (clear_paths(paths), status | file.err);
}
