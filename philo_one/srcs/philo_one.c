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

int			ft_init_philos(t_tab *tab)
{
	t_philo	philo[tab->philos];
	int		i;

	i = 0;
	tab->bigb = ft_get_time();
	while (i < tab->philos)
	{
		ft_make_school(&philo[i], tab, i);
		pthread_create(&philo[i].philo, NULL, &ft_acient_greece, &philo[i]);
		++i;
	}
	i = -1;
	while (++i < tab->philos)
		pthread_join(philo[i].philo, NULL);
	return (1);
}

int			main(int argc, char **argv)
{
	int		i;
	t_tab	tab;

	if (argc < 5)
		ft_exit("Wrong arguments' amount");
	ft_init_table(argv, &tab, argc);
	ft_init_philos(&tab);
	pthread_mutex_destroy(&tab.mutx_print);
	pthread_mutex_destroy(&tab.mutx_death);
	pthread_mutex_destroy(&tab.mutx_ctrl);
	while (--tab.philos >= 0)
		pthread_mutex_destroy(&tab.m_fork[tab.philos]);
	return (1);
}
