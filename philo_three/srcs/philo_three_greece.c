/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_greece.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:14:58 by cjani             #+#    #+#             */
/*   Updated: 2021/04/25 18:15:00 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	ft_cycles(int meals, int cycles)
{
	if ((cycles == 0) || (meals < cycles))
		return (1);
	return (0);
}

void	ft_make_school(t_philo *philo, t_tab *tab, int id)
{
	philo->id = id;
	philo->tab = tab;
	philo->lastmeal = 0;
	philo->meals = 0;
}

void	*ft_death_patrol(void *philos)
{
	t_philo		*philo;

	philo = (t_philo *)philos;
	sem_wait(philo->tab->sem_control);
	while ((ft_get_time() - philo->lastmeal) < philo->tab->starv \
	&& ft_cycles(philo->meals, philo->tab->cycles))
	{
		sem_post(philo->tab->sem_control);
		usleep(10);
		sem_wait(philo->tab->sem_control);
	}
	sem_post(philo->tab->sem_control);
	if (ft_cycles(philo->meals, philo->tab->cycles))
	{
		sem_wait(philo->tab->sem_die);
		ft_print(philo, "is dead");
		sem_post(philo->tab->exit);
	}
	else
		sem_post(philo->tab->wait_cycle);
	exit(0);
}

void	ft_greece_life(t_philo *philo)
{
	sem_wait(philo->tab->polite);
	sem_wait(philo->tab->sem_forks);
	ft_print(philo, "has taken a fork");
	sem_wait(philo->tab->sem_forks);
	ft_print(philo, "has taken a fork");
	sem_post(philo->tab->polite);
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

void	*ft_acient_greece(void *student)
{
	t_philo		*philo;
	pthread_t	death_patrol;

	philo = (t_philo *)student;
	philo->lastmeal = ft_get_time();
	pthread_create(&death_patrol, NULL, ft_death_patrol, philo);
	while (ft_cycles(philo->meals, philo->tab->cycles))
		ft_greece_life(philo);
	pthread_join(death_patrol, NULL);
	return (NULL);
}
