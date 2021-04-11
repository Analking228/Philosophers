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

void			ft_make_school(t_philo *philo, t_tab *tab, int id)
{
	philo->id = id;
	philo->tab = tab;
	philo->meals = 0;
}

void*			ft_acient_greece(void *student)
{
	t_philo			*philo;
	long 			lifetime;

	philo = (t_philo *)student;
	while (philo->meals != philo->tab->cycles)
	{
		ft_print(philo, "is eating");
		usleep(philo->tab->eat);
		ft_print(philo, "is sleeping");
		usleep(philo->tab->sleep);
		ft_print(philo, "is thinking");
		//ft_greecelife();
		philo->meals++;
	}
	return (NULL);
}

void		*ft_init_philos(t_tab *tab)
{
	t_philo	philo[5];
	int		i;

	i = -1;
	while (++i < tab->philos)
	{
		ft_make_school(&philo[i], tab, i);
		pthread_create(&philo[i].philo, NULL, &ft_acient_greece, (void *)&philo[i]);
	}
	i = -1;
	while (++i < tab->philos)
		pthread_join(philo[i].philo, NULL);
	return (NULL);
}

int			main(int argc, char **argv)
{
	int		i;
	t_tab	tab;

	if (argc != 6)
		ft_exit("Wrong arguments' amount");
	ft_init_table(argv, &tab);
	ft_init_philos(&tab);
	pthread_mutex_destroy(&tab.mutx_print);
	return (1);
}
