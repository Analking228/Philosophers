/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_greece.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:04:27 by cjani             #+#    #+#             */
/*   Updated: 2021/04/14 14:04:30 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void			ft_make_school(t_philo *philo, t_tab *tab, int id)
{
	philo->id = id;
	philo->tab = tab;
	philo->lastmeal = 0;
	philo->meals = 0;
}

void			ft_greecelife(t_philo *philo)
{
	sem_wait(philo->tab->waiter);
	sem_wait(philo->tab->sem_forks);
	ft_print(philo, "has taken a fork");
	sem_wait(philo->tab->sem_forks);
	ft_print(philo, "has taken a fork");
	sem_post(philo->tab->waiter);
	ft_print(philo, "is eating");
	philo->lastmeal = ft_get_time();
	ft_wait(philo->tab->eat);
	sem_post(philo->tab->sem_forks);
	sem_post(philo->tab->sem_forks);
	ft_print(philo, "is sleeping");
	ft_wait(philo->tab->sleep);
	ft_print(philo, "is thinking");
	philo->meals++;
}

int				ft_cycles(int meals, int cycles)
{
	if ((cycles == 0) || (meals < cycles))
		return (1);
	return (0);
}

void*			ft_death_patrol(void *student)
{
	t_philo		*philo;

	philo = (t_philo *)student;
	sem_wait(philo->tab->sem_control);
	while (ft_cycles(philo->meals,philo->tab->cycles) && !philo->tab->is_dead \
	&& ((ft_get_time() - philo->lastmeal) < philo->tab->starv))
	{
		sem_post(philo->tab->sem_control);
		usleep(10);
		sem_wait(philo->tab->sem_control);
	}
	sem_post(philo->tab->sem_control);
	if (((ft_get_time() - philo->lastmeal) >= philo->tab->starv) && !philo->tab->is_dead)
	{
		sem_wait(philo->tab->sem_print);
		philo->tab->is_dead = 1;
		printf("[%ld] %d %s\n", (ft_get_time() - philo->tab->bigb), philo->id + 1, "is dead");
		sem_post(philo->tab->sem_print);
	}	
	else
		return (NULL);
	return (NULL);
}

void			*ft_acient_greece(void *student)
{
	t_philo			*philo;
	pthread_t		death_patrol;

	philo = (t_philo *)student;
	philo->lastmeal = ft_get_time();
	pthread_create(&death_patrol, NULL, &ft_death_patrol, philo);
	while (ft_cycles(philo->meals,philo->tab->cycles) && !philo->tab->is_dead)
		ft_greecelife(philo);
	pthread_join(death_patrol, NULL);
	return (NULL);
}
