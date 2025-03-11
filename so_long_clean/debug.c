#include "includes/so_long.h"

void print(t_point *point)
{
	printf("%li || %li\n", point->x, point->y);
}

void print_map(t_map *map)
{
	if (!map->grid)
		return;
	printf("%li || %li\n", map->size.x, map->size.y);
	for (int i = 0; map->grid[i]; i++)
		printf("%s\n", map->grid[i]);
}

void print_stats(t_stats *stats)
{
	if (!stats->clc_poss)
		return;
	printf("clc ::\n");
	ft_lstiter(stats->clc_poss, (void (*)(void *))print);
	printf("enm ::\n");
	ft_lstiter(stats->enm_poss, (void (*)(void *))print);
	printf("player ::\n");
	ft_lstiter(stats->player_pos, (void (*)(void *))print);
	printf("exit ::\n");
	ft_lstiter(stats->exit_pos, (void (*)(void *))print);
	return;
}
