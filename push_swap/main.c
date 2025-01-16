/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:14:38 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/16 11:40:39 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


void error(t_stks *stks) {
    free_all(stks);
    write(1, "Error\n", 6);
}

int main(int ac, char **av) {
    t_stks *stks;
    int len;

    stks = (t_stks *) malloc(sizeof(t_stks));
    if (ac > 2)
    {
        if (!process_args(&stks->a, &av[1]))
        {
            error(stks);
            return 0;
        }
        if (len < 20)
            easy_sort(stks, &len);
        else
            fast_sort(stks);
    }
    free_all(stks);
}