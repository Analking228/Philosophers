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

int	ft_init_philos(t_tab *tab)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(tab->philos * sizeof(t_philo));
	tab->bigb = ft_get_time();
	while (++i < tab->philos)
	{
		ft_make_school(&philo[i], tab, i);
		pthread_create(&philo[i].philo, NULL, &ft_acient_greece, &philo[i]);
	}
	i = -1;
	while (++i < tab->philos)
		pthread_join(philo[i].philo, NULL);
	free(philo);
	return (1);
}

int	main(int argc, char **argv)
{
	t_tab	tab;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong arguments' amount");
		return (1);
	}
	if (ft_init_table(argv, &tab, argc))
		return (1);
	ft_init_philos(&tab);
	pthread_mutex_destroy(&tab.mutx_print);
	pthread_mutex_destroy(&tab.mutx_patrol);
	pthread_mutex_destroy(&tab.mutx_polite);
	while (--tab.philos >= 0)
		pthread_mutex_destroy(&tab.m_fork[tab.philos]);
	free(tab.m_fork);
	return (0);
}
