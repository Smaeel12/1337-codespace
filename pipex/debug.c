

// void	print(t_cmd *cmd)
// {
// 	printf("%s\n", cmd->cmd);
// 	for (int i = 0; cmd->args[i]; i++)
// 		printf("%s\n", cmd->args[i]);
// }

// void	run(t_cmd *cmd)
// {
// 	int	pid;

// 	if (access(cmd->cmd, X_OK))
// 		return (perror(cmd->cmd));
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve(cmd->cmd, cmd->args, NULL);
// 		exit(0);
// 	}
// 	else if (pid > 0)
// 		wait(NULL);
// 	else
// 		exit(0);
// }
