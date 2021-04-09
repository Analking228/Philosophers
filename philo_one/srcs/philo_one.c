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

void		*ft_eat(void *arr)
{
	return (NULL);
}

void		*ft_sleep(void *arr)
{
	return (NULL);
}

void		*ft_think(void *arr)
{
	return (NULL);
}

void			ft_make_school(t_philo *philo, t_tab *tab, int id)
{
	philo->id = id;
	philo->tab = tab;
}

void*			ft_acient_greece(void *student)
{
	t_philo		*philo;

	philo = (t_philo *)student;
	printf("Welcome to the club, buddy! I'm the %d\n", philo->id);
	usleep(50);
	printf("Ending\n");
	return (NULL);
}

void		*ft_init_philos(t_tab *tab)
{
	t_philo	philo[5];
	int		i;

	i = -1;
	// philo[0].id = 0;
	// pthread_create(&philo[++i].philo, NULL, &ft_acient_greece, (void *)&philo[i]);
	// philo[1].id = 1;
	// pthread_create(&philo[++i].philo, NULL, &ft_acient_greece, (void *)&philo[i]);
	// pthread_join(philo[0].philo, NULL);
	// pthread_join(philo[1].philo, NULL);
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
	return (1);
}
