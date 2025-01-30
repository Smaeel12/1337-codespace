

// DEBUGGGGGGGGGGGGGGGGGG
void print_stack(t_stack *stack, char c)
{
    int i = stack->len - 1;
    
    printf("%c || ", c);
    while (i >= 0)
    {
        printf("%i ", stack->content[i]);
        i--;
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

// void quick_sort(t_stks *stks, int pivot) {
//     int i;

//     i = 0;
//     if (ft_is_sorted(stks->a) || stks->a.len <= 5)
//         return ;
//     while (stks->a.len > 5 && i < stks->meta.len && !ft_is_sorted(stks->a))
//     {
//         if (TOPA > stks->meta.content[pivot])
//             rotate_stack(stks->a, "ra\n");
//         else
//         {
//             push_stack(&stks->b, &stks->a, "pb\n");
//             if (pivot < stks->meta.len - 1)
//                 pivot++;
//             if ((stks->b.len > 1 && stks->b.content[stks->b.len - 1] < stks->meta.content[pivot / 2]))
//                 rotate_stack(stks->b, "rb\n");
//         }
//         i++;
//     }
//     // 
//     quick_sort(stks, pivot);
// }


// void easy_sort(t_stks *stks)
// {
//     while (!ft_is_sorted(stks->a))
//     {
//         if (TOPA > stks->a.content[stks->a.len - 2])
//         {
//             if (TOPA > BOTTOM1)
//                 rotate_stack(stks->a, "ra\n");
//             else
//                 swap_stack(stks->a, "sa\n");
//         }
//         else if (BOTTOM2 > BOTTOM1)
//             reverse_rotate_stack(stks->a, "rra\n");
//         else
//             push_stack(&stks->b, &stks->a, "pb\n");
//     }
//     // exit(1);

//     int bpos;
//     int expec = stks->meta.len;
//     while (stks->b.len)
//     {
//         // print_stack(&stks->a, 'a');
//         // print_stack(&stks->b, 'b');
//         bpos = get_max_pos(stks->b);
//         while (get_to_top(stks->b, bpos) && stks->b.content[stks->b.len - 1] > BOTTOM1)
//         {
//             if (expec != stks->meta.len && TOPA != expec + 1)
//                 break;
//             push_stack(&stks->a, &stks->b, "pa\n");
//             bpos = get_max_pos(stks->b);
//             expec--;
//         }
//         while (BOTTOM1 != stks->meta.len && BOTTOM1 > stks->b.content[stks->b.len - 1])
//         {
//             reverse_rotate_stack(stks->a, "rra\n");
//             expec--;
//         }
//         while (stks->b.content[stks->b.len - 1] > TOPA)
//         {
//             rotate_stack(stks->a, "ra\n");
//             expec++;
//         }
//         if (TOPA == expec)
//             expec--;
//         push_stack(&stks->a, &stks->b, "pa\n");
//     }
//     while (BOTTOM1 != stks->meta.len)
//         reverse_rotate_stack(stks->a, "rra\n");
// }

// void ft_pre_sort_a(t_stks *stks)
// {
//     if (stks->.len % 2 == 0)
//         meta->median = (a.len - 2) / 2;
//     else
//         meta->median = (a.len - 1) / 2;
// }