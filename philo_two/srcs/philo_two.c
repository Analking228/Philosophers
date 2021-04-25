/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:52:54 by cjani             #+#    #+#             */
/*   Updated: 2021/04/25 17:52:58 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

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
	int		i;
	t_tab	tab;

	if (argc < 5 || argc > 6)
	{
		ft_exit("Wrong arguments' amount");
		return (1);
	}
	if (ft_init_table(argv, &tab, argc))
		return (1);
	ft_init_philos(&tab);
	sem_close(tab.sem_control);
	sem_close(tab.sem_print);
	sem_close(tab.sem_forks);
	sem_close(tab.polite);
	return (0);
}
