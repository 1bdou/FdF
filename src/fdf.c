/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo1 <abdo1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:50:41 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/12 06:31:46 by abdo1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_Point3D	*points_placer(int number_of_lines, int array_lenght,
		int **map)
{
	int			i;
	int			j;
	t_Point3D	*point;
	t_Point3D	*head;

	i = 0;
	head = setup_first_node(&head, &point, map);
	j = 4;
	while (i < number_of_lines - 1)
	{
		while (j < array_lenght * 4 - 4)
		{
			point->next = store_in_node(map, i + 1, j);
			j += 4;
			point->next->next = store_in_node(map, i, j);
			point = point->next->next;
		}
		j = 0;
		i++;
		point->next = store_in_node(map, i, j);
		point = point->next;
	}
	return (head);
}

static void	fdf(int fd, void *mlx_ptr)
{
	int			**map;
	int			map_data[2];
	t_Point3D	*head;

	map = map_parser(fd, &map_data[0], &map_data[1]);
	if (!map)
		return ;
	head = points_placer(map_data[1], map_data[0], map);
	rendering_engine(head, map_data, mlx_ptr, map);
	free_array(map, map_data[1]);
	clear_list(head);
}

int	error_handler(int argc, char **argv, char *path, int fd)
{
	if (argc < 2)
	{
		perror("please provide FDF file.");
		return (1);
	}
	else if (fd < 0)
	{
		perror("cannot open file or wrong extention");
		free(path);
		return (1);
	}
	else if (!ft_strchr(argv[1], '.'))
		return (1);
	else if ((*(ft_strchr(argv[1], '.') + 4)))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	int		fd;
	char	*path;

	path = ft_strjoin("../tests/", argv[1]);
	fd = open(path, O_RDONLY);
	if (error_handler(argc, argv, path, fd))
		return (1);
	mlx_ptr = mlx_init();
	fdf(fd, mlx_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	free(path);
	close(fd);
	return (0);
}
