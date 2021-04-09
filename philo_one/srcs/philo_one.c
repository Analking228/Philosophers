/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filo_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:47:05 by cjani             #+#    #+#             */
/*   Updated: 2021/04/05 15:47:10 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void		*eat(void *arr)
{

}

void		*sleep(void *arr)
{

}

void		*think(void *arr)
{

}

void			*ft_philo_singularity(void *tab)
{

}

int			main(int argc, char **argv)
{
	int		i;
	t_tab	tab;

	if (argc != 6)
		ft_exit("Wrong arguments' amount");
	ft_init_table(argv, &tab);
	i = -1;
	while (++i < tab.philos)
	{
		
	}
	
	ft_philo_singularity();
	return (1);
}
