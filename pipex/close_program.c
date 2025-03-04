/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:53:31 by iboubkri          #+#    #+#             */
/*   Updated: 2025/03/03 15:33:42 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	free_lst(t_cmd *cmd)
{
	int	i;

	i = 0;
	free(cmd->cmd);
	while (cmd->args && cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
	free(cmd);
}

int	exit_program(char **paths, t_list *cmds, t_error status)
{
	int	i;

	i = 0;
	while (paths && paths[i])
		free(paths[i++]);
	free(paths);
	ft_lstclear(&cmds, (void (*)(void *))free_lst);
	exit(status);
}
