/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 18:19:35 by iboubkri          #+#    #+#             */
/*   Updated: 2025-02-16 18:19:35 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void run_command(char **paths, char *cmd)
{
    char **cmd_line;

    cmd_line = ft_split(cmd, ' ');
    find_cmd_path(cmd_line);
    free_2d_array(cmd_line);
}


int main(int ac, char **av, char **envp)
{
    char **paths;

    paths = extract_paths(envp);
    run_command(paths, av[1]);
}