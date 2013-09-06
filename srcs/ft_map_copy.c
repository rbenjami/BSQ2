/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mp_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: espiroux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/09/02 13:01:33 by espiroux          #+#    #+#             */
/*   Updated: 2013/09/02 13:01:34 by espiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFSIZE 1
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "struct.h"
#include "function.h"
#include "ft_map.h"
#include "pushpullchar.h"

/*
**copie file to struct map in the variable mem.
*/

void	ft_count_clone_file(map *mp, int *fd, char *buf, int ret)
{
	int	count;
	int	i;
	int	countfind;
	char	find_char[13];

	i = 0;
	count = 0;
	countfind = 0;
	map_init(mp);
	while (read(*fd, buf, BUFFSIZE))
	{
		if (count != 0)
		{
			map_count(mp, buf);
			mp->mem[i] = buf[0];
			i++;
		}
		ft_take_char_first_line(buf, &count, find_char, &countfind);
		buf[ret] = '\0';
	}
	if ((close(*fd)) || (mp->x <= 0) || (mp->y <= 0))
		mp->error = 1;
	mp->mem[i] = '\0';
	ft_pull_char_first_line(countfind, mp, find_char);
	ft_map_max(mp);
}

/*
**Open a file and write an error in map's struct.    
*/

void	ft_open(int *fd, char *av, map *mp)
{
	*fd = open(av, O_RDONLY);
	if (*fd < 0)
	{
		mp->error = 1;
	}
}

/*
**Copy the map information in a map's structure    
*/

map	ft_map_copy(char *av, int ac)
{
	int	fd;
	char	buf[BUFFSIZE + 1];
	map	mp;
	int	ret;
	int	j;

	fd = 0;
	j = 0;
	mp.mem = (char*) malloc(BUFFSIZE);
	if (ac > 1)
	{
		ft_open(&fd, av, &mp);
		while ((ret = read(fd, buf, BUFFSIZE)))
			j++;
		close(fd);
		mp.mem = malloc(sizeof(char*) * j);
		ft_open(&fd, av, &mp);
	}
	ft_count_clone_file(&mp, &fd, buf, ret);
	return (mp);
}
