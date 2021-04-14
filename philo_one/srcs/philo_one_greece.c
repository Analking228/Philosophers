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

#include "../includes/philo_one.h"

void			ft_make_school(t_philo *philo, t_tab *tab, int id)
{
	philo->id = id;
	philo->tab = tab;
	philo->lastmeal = ft_get_time();
	philo->birthday = 0;
	philo->meals = 0;
	return ;
}

void			ft_greecelife(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&philo->tab->m_fork[philo->id]);
	else
		pthread_mutex_lock(&philo->tab->m_fork[(philo->id + 1)
											% philo->tab->philos]);
	ft_print(philo,"has taken a fork");
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&philo->tab->m_fork[(philo->id + 1)
											% philo->tab->philos]);
	else
		pthread_mutex_lock(&philo->tab->m_fork[philo->id]);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	philo->lastmeal = ft_get_time();
	ft_wait(philo->tab->eat);
	pthread_mutex_unlock(&philo->tab->m_fork[(philo->id + 1)
											% philo->tab->philos]);
	pthread_mutex_unlock(&philo->tab->m_fork[philo->id]);
	ft_print(philo, "is sleeping");
	ft_wait(philo->tab->sleep);
	ft_print(philo, "is thinking");
	philo->meals++;
	return ;
}

void*			ft_death_patrol(void *student)
{
	t_philo		*philo;

	philo = (t_philo *)student;
	while ((philo->meals < philo->tab->cycles) && !philo->tab->is_dead \
	&& ((ft_get_time() - philo->lastmeal) < philo->tab->starv))
		usleep(10);
	if (((ft_get_time() - philo->lastmeal) >= philo->tab->starv) && !philo->tab->is_dead)
	{
		philo->tab->is_dead = 1;
		ft_print(philo, "is dead");
		philo->tab->necrologue = 1;
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
	philo->birthday = ft_get_time();
	pthread_create(&death_patrol, NULL, &ft_death_patrol, philo);
	while (philo->meals < philo->tab->cycles && !philo->tab->is_dead \
	&& ((ft_get_time() - philo->lastmeal) < philo->tab->starv))
		ft_greecelife(philo);
	pthread_join(death_patrol, NULL);
	return (NULL);
}
