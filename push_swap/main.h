

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#define TOP1 stks->a.content[stks->a.len - 1]
#define TOP2 stks->a.content[stks->a.len - 2]

#define BOTTOM1 stks->a.content[0]
#define BOTTOM2 stks->a.content[1]

#define MID stks->a.content[stks->a.len / 2]


typedef struct s_stack
{
    int len;
    int *content;
} t_stack;

typedef struct s_stks
{
    t_stack a;
    t_stack b;
    t_stack meta;
} t_stks;


// args processing
void	ft_init_stacks(t_stks *stks, char **av);


// common functions
void ft_exit_error(t_stks *stks);
int ft_is_sorted(t_stack stack);


// instructions
void push_stack(t_stack *to, t_stack *from, char *action);
void reverse_rotate_stack(t_stack stack, char *action);
void rotate_stack(t_stack stack, char *action);
void swap_stack(t_stack stack, char *action);

// minilibft
int ft_strlen(char *str);
char *ft_strdup(char *str);
char *ft_strcat(char *dest, char *src);
char    *ft_strnstr(const char *haystack, const char *needle, size_t len);
long	ft_atol(const char *str);

