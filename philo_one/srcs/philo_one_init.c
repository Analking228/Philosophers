/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filo_one_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:47:29 by cjani             #+#    #+#             */
/*   Updated: 2021/04/05 15:47:31 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	ft_init_tab(t_tab *tab)
{
	tab->philos = 0;
	tab->is_dead = 0;
	tab->necrologue = 0;
	tab->starv = 0;
	tab->eat = 0;
	tab->sleep = 0;
	tab->cycles = 0;
	tab->bigb = 0;
	pthread_mutex_init(&tab->mutx_print, NULL);
}

void	ft_args(t_tab *tab, int	num, int count)
{
	if (count == 1)
	{
		tab->philos = num;
		tab->m_fork = (pthread_mutex_t *)malloc(num * sizeof(pthread_mutex_t));
		while (--num >= 0)
			pthread_mutex_init(&tab->m_fork[num], NULL);
	}
	else if (count == 2)
		tab->starv = num;
	else if (count == 3)
		tab->eat = num;
	else if (count == 4)
		tab->sleep = num;
	else if (count == 5)
		tab->cycles = num;
}

int		ft_parse_args(char **av, t_tab *tab, int argc)
{
	int	i;
	int	rez;

	i = 0;
	while (++i < argc)
	{
		if ((rez = ft_nznum(av[i])) > 0)
			ft_args(tab, rez, i);
		else
			return (0);
	}
	return (1);
}

int		ft_init_table(char **argv, t_tab *tab, int argc)
{
	ft_init_tab(tab);
	if (!ft_parse_args(argv, tab, argc))
		ft_exit("Bad argument");
	return (1);
}