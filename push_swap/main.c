/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:14:38 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/20 15:38:01 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


// DEBUGGGGGGGGGGGGGGGGGG
void print_stack(t_stack *stack, char c)
{
    int i = 0;
    
    printf("%c || ", c);
    while (i < stack->len)
    {
        printf("%i ", stack->content[i]);
        i++;
    }
    printf("|| \n");
}


int mid_num(int n1, int n2, int n3) {
    if ((n1 > n2 && n1 < n3) || (n1 < n2 && n1 > n3))
        return n1;
    else if ((n2 > n1 && n2 < n3) || (n2 < n1 && n2 > n3))
        return n2;
    else
        return n3;
}

void quick_sort(t_stks *stks, int pivot) {
    int i;

    i = 0;
    if (ft_is_sorted(stks->a) || stks->a.len <= 5)
        return ;
    while (stks->a.len > 5 && i < stks->meta.len && !ft_is_sorted(stks->a))
    {
        if (TOP1 > stks->meta.content[pivot])
            rotate_stack(stks->a, "ra\n");
        else
        {
            push_stack(&stks->b, &stks->a, "pb\n");
            if (pivot < stks->meta.len - 1)
                pivot++;
            if ((stks->b.len > 1 && stks->b.content[stks->b.len - 1] < stks->meta.content[pivot / 2]))
                rotate_stack(stks->b, "rb\n");
        }
        i++;
    }
    // 
    quick_sort(stks, pivot);
}

int get_max_pos(t_stack stack)
{
    int i;
    int pos;
    int max;

    i = 0;
    pos = 0;
    max = stack.content[i];
    while (i < stack.len)
    {
        if (max < stack.content[i])
        {
            max = stack.content[i];
            pos = i;
        }
        i++;
    }
    return pos;
}

int get_to_top(t_stack stack, int pos)
{
    if (pos >= stack.len - 3)
    {
        while (pos++ < stack.len - 1)
            rotate_stack(stack, "rb\n");
        return 1;
    }
    else if (pos < 3)
    {
        while (pos-- >= 0)
            reverse_rotate_stack(stack, "rrb\n");
        return 1;
    }
    return 0;
}


void easy_sort(t_stks *stks)
{
    while (!ft_is_sorted(stks->a))
    {
        if (TOP1 > TOP2)
        {
            if (TOP1 > BOTTOM1)
                rotate_stack(stks->a, "ra\n");
            else
                swap_stack(stks->a, "sa\n");
        }
        else if (BOTTOM2 > BOTTOM1)
            reverse_rotate_stack(stks->a, "rra\n");
        else
            push_stack(&stks->b, &stks->a, "pb\n");
    }
    // exit(1);

    int bpos;
    int expec = stks->meta.len;
    while (stks->b.len)
    {
        print_stack(&stks->a, 'a');
        print_stack(&stks->b, 'b');
        bpos = get_max_pos(stks->b);
        while (get_to_top(stks->b, bpos) && stks->b.content[stks->b.len - 1] > BOTTOM1)
        {
            if (expec != stks->meta.len && TOP1 != expec + 1)
                break;
            push_stack(&stks->a, &stks->b, "pa\n");
            bpos = get_max_pos(stks->b);
            expec--;
        }
        while (BOTTOM1 != stks->meta.len && BOTTOM1 > stks->b.content[stks->b.len - 1])
        {
            reverse_rotate_stack(stks->a, "rra\n");
            expec--;
        }
        while (stks->b.content[stks->b.len - 1] > TOP1)
        {
            rotate_stack(stks->a, "ra\n");
            expec++;
        }
        if (TOP1 == expec)
            expec--;
        push_stack(&stks->a, &stks->b, "pa\n");
    }
    while (BOTTOM1 != stks->meta.len)
        reverse_rotate_stack(stks->a, "rra\n");
}

void sort(t_stks *stks) {
    if (stks->a.len >= 3)
        quick_sort(stks, (stks->meta.len  - 2) / 2);
    easy_sort(stks);
}

void sort_arr(t_stack *stack)
{
    int i = 0;
    int j = 0;
    int tmp;

    while (i < stack->len)
    {
        j = i + 1;
        while (j < stack->len)
        {
            if (stack->content[i] > stack->content[j])
            {
                tmp = stack->content[i];
                stack->content[i] = stack->content[j];
                stack->content[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

// void ft_pre_sort_a(t_stks *stks)
// {
//     if (stks->.len % 2 == 0)
//         meta->median = (a.len - 2) / 2;
//     else
//         meta->median = (a.len - 1) / 2;
// }

int main(int ac, char **av) {
    t_stks *stks;

    stks = (t_stks *) malloc(sizeof(t_stks));
    if (ac >= 2)
    {
        ft_init_stacks(stks, &av[1]);
        sort_arr(&stks->meta);
        sort(stks);
    }
    free(stks->a.content);
    free(stks->b.content);
    free(stks);
}