/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2024/11/05 11:27:19 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_coin(t_map *map)
{
	map->map[map->y][map->x] = '0';
	map->coin -= 1;
	map->player += 1;
}

static void	get_coin_enermy(t_map *map)
{
	map->map[map->xy[1]][map->xy[0]] = '0';
	map->coin -= 1;
	map->hole += 1;
}

static int	move(int keycode, t_map *map)
{
	int	x;
	int	y;
	
	ft_printf("keycode = %d\n", keycode);
	x = map->x;
	y = map->y;
	if (keycode == 2 && map->map[y][x + 1] != '1')
	{
		(map->x) += 1;
		map->flag = 0;
	}
	else if (keycode == 0 && map->map[y][x - 1] != '1')
	{
		(map->x) -= 1;
		map->flag = 1;
	}
	else if (keycode == 1 && map->map[y + 1][x] != '1')
		(map->y) += 1;
	else if (keycode == 13 && map->map[y - 1][x] != '1')
		(map->y) -= 1;
	x = map->xy[0];
	y = map->xy[1];
	if (keycode == 124 && map->map[y][x + 1] != '1')
	{
		map->xy[0] += 1;
		map->flag1 = 0;
	}
	else if (keycode == 123 && map->map[y][x - 1] != '1')
	{
		map->xy[0] -= 1;
		map->flag1 = 1;
	}
	else if (keycode == 125 && map->map[y + 1][x] != '1')
		map->xy[1] += 1;
	else if (keycode == 126 && map->map[y - 1][x] != '1')
		map->xy[1] -= 1;
	if (map->coin == 0)
		map->enermy = 0;
	return (0);
}

static int	game(int keycode, t_map *map)
{
	put_cover(map, map->x, map->y);
	put_cover(map, map->xy[0], map->xy[1]);
	put_map(map);
	map->player += move(keycode, map);
	if (keycode == 53)
		end(map);
	if (map->map[map->y][map->x] == 'E' && map->coin == 0 && map->player >= map->hole)
		finish(map);
	if (map->map[map->xy[1]][map->xy[0]] == 'E' && map->coin == 0 && map->player <= map->hole)
		finishe(map);
	if (map->x == map->xy[0] && map->y == map->xy[1] && map->enermy == 0 && map->player > map->hole)
		die(map);
	if (map->x == map->xy[0] && map->y == map->xy[1] && map->enermy == 0 && map->player < map->hole)
		die1(map);
	//move_enermy(map);
	put_hole(map);
	if (map->flag == 1)
		mlx_loop_hook(map->mlx, put_chicken_mirror, map);
	else
		mlx_loop_hook(map->mlx, put_chicken, map);
	if (map->map[map->y][map->x] == 'C')
		get_coin(map);
	if (map->map[map->xy[1]][map->xy[0]] == 'C')
		get_coin_enermy(map);
	put_info(map);
	return (0);
}

void	start(t_map *map, int argc, char *input)
{
	ft_file(map, argc, input);
	parse(map, map->path);
	map->map = calloc((map->height + 1), sizeof(void *));
	if (!map->map)
		error(12, -1, NULL);
	map->coin = 0;
	map->hole = 0;
	map->player = 0;
	parse1(map, map->path);
	init(map);
	put_map(map);
	put_hole(map);
	init_enermy(map);
	put_info(map);
	mlx_loop_hook(map->mlx, put_chicken, map);
	mlx_hook(map->win, 2, 1L << 0, game, map);
	mlx_hook(map->win, 17, 0, end, map);
	mlx_loop(map->mlx);
}

// delete first if condition to take maps automatically
int	main(int argc, char **argv)
{
	t_map	map;

	if (argc > 2)
		error(7, -1, NULL);
	map.hole = 0;
	map.player = 0;
	map.retry = 0;
	if (argc == 2)
		start(&map, argc, argv[1]);
	else
		start(&map, argc, NULL);
	return (0);
}

/* void printmap(char **map, int height)
{
	int y;

	y = 0;
	while (y < height)
	{
		printf("%s", map[y]);
		y++;
	}
	printf("--------------------------\n");
} */
