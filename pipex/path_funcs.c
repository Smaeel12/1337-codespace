/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 15:54:09 by iboubkri          #+#    #+#             */
/*   Updated: 2025-02-17 15:54:09 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char *find_cmd_path(char **paths, char *cmd)
{
    char *cmd_line;
    int i;
    
    i = 0;
    while (paths[i])
    {
        cmd_line = ft_strjoin(paths[i], "/");
        if (access(cmd_line, F_OK))
            return cmd_line;
        free(cmd_line);
        i++;
    }
}

char **extract_paths(char **envp)
{
    char *path;
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
        {
            path = envp[i];
            break;
        }
        i++;
    }
    return ft_split(ft_strchr(path, '=') + 1, ':');
}