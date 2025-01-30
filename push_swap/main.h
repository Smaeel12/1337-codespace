/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:22:26 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/30 10:38:19 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft/get_next_line/get_next_line.h"
# include "libft/libft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int		len;
	int		*content;
}			t_stack;

typedef struct s_stks
{
	t_stack	a;
	t_stack	b;
	t_stack	meta;
}			t_stks;

// args processing
int			ft_init_stacks(t_stks *stks, char **av);

// helper functions
void		ft_exit_error(t_stks *stks);
int			ft_is_sorted(t_stack stack);
int			ft_get_max_pos(t_stack stack);
void		ft_get_to_top(t_stack stack, int pos, char *r, char *rr);
int			ft_check_double(t_stack stack);

// instructions
void		push_stack(t_stack *to, t_stack *from, char *action);
void		reverse_rotate_stack(t_stack stack, char *action);
void		rotate_stack(t_stack stack, char *action);
void		swap_stack(t_stack stack, char *action);

// bonus instructions
int			swapper(t_stks *stks, int move);
int			pusher(t_stks *stks, int move, int slen);
int			rotater(t_stks *stks, int move);
int			reverse_rotater(t_stks *stks, int move);

#endif