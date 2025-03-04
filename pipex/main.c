/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:19:35 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/04 18:05:54 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print(t_cmd *cmd)
{
	printf("%s\n", cmd->cmd);
	for (int i = 0; cmd->args[i]; i++)
		printf("%s\n", cmd->args[i]);
}

int	child_execute(char **paths, char *cline, int in_file, int out_file)
{
	t_cmd cmd;
	int	pid;

	cmd = find_cmd(paths, cline);
	pid = fork();
	if (pid < 0)
		return (exit_prog(paths, &cmd, FORK_FAILED));

	if (pid == 0)
	{
		dup2(in_file, 0);
		dup2(out_file, 1);
		close(in_file);
		close(out_file);
		execve(cmd.cmd, cmd.args, NULL);
		exit_prog(paths, &cmd, EXECVE_FAILED);
	}
	else
	{
		close(in_file);
		close(out_file);
		wait(NULL);
	}
	clear_ptrs(cmd.cmd, cmd.args);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	**paths;
	int		pipefds[2];
	int		in_out[2];

	if (ac >= 5)
	{
		in_out[IN] = open(av[1], O_RDONLY);
		in_out[OUT] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipe(pipefds) == -1 || in_out[IN] == -1 || in_out[OUT] == -1)
			return (close(in_out[IN]), close(in_out[OUT]), 1);
		paths = extract_paths(envp);
		child_execute(paths, av[2], in_out[IN], pipefds[WRITE]);
		child_execute(paths, av[3], pipefds[READ], in_out[OUT]);
		close(pipefds[WRITE]);
		close(pipefds[READ]);
		close(in_out[IN]);
		close(in_out[OUT]);
		exit_prog(paths, NULL, NULL);
	}
	return (exit_prog(NULL, NULL, USAGE_ERROR));
}
