
#include <stdlib.h>
#include <limits.h>

// stack structure
typedef struct s_stack
{
    int len;
    int *content;
} t_stack;

typedef struct s_stks
{
    t_stack a;
    t_stack b;
} t_stks;


// args processing
long	ft_atol(const char *str);
int ft_isdigit(char *str);
int count_args(char **args);
int process_args(t_stack *stack, char **args);