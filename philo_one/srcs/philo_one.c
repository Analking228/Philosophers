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
	philo->birthday = ft_get_time();
	philo->lastmeal = philo->birthday;
}

void			ft_greecelife(t_philo *philo)
{
	ft_print(philo, "is eating");
	ft_wait(philo->tab->eat);
	philo->lastmeal = ft_get_time();
	ft_print(philo, "is sleeping");
	ft_wait(philo->tab->sleep);
	ft_print(philo, "is thinking");
	philo->meals++;
}

void*			ft_death_patrol(void *student)
{
	t_philo		*philo;

	pthread_mutex_lock(&philo->tab->mutx_ctrl);
	philo = (t_philo *)student;
	while ((philo->meals < philo->tab->cycles) && !philo->tab->is_dead &&\
			(ft_get_time() - philo->lastmeal > philo->tab->starv))
	{
		pthread_mutex_unlock(&philo->tab->mutx_ctrl);
		usleep(100);
		pthread_mutex_lock(&philo->tab->mutx_ctrl);
	}
	pthread_mutex_lock(&philo->tab->mutx_ctrl);
	if (philo->meals < philo->tab->cycles)
		return (NULL);
	else
	{
		pthread_mutex_lock(&philo->tab->mutx_death);
		philo->tab->is_dead = 1;
		ft_print(philo, "is dead");
		philo->tab->necrologue = 1;
		pthread_mutex_unlock(&philo->tab->mutx_death);
		return (NULL);
	}
}

void*			ft_acient_greece(void *student)
{
	t_philo			*philo;
	pthread_t		death_patrol;

	philo = (t_philo *)student;
	printf("philo %d is ready for duty\n", philo->id);
	pthread_create(&death_patrol, NULL, &ft_death_patrol, philo);
	while ((philo->meals < philo->tab->cycles) && !philo->tab->is_dead)
		ft_greecelife(philo);
	pthread_join(death_patrol, NULL);
	return (NULL);
}

int			ft_init_philos(t_tab *tab)
{
	t_philo	philo[tab->philos];
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
	return (1);
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
	pthread_mutex_destroy(&tab.mutx_death);
	pthread_mutex_destroy(&tab.mutx_ctrl);
	while (--tab.philos != -1)
		pthread_mutex_destroy(&tab.m_fork[tab.philos]);
	return (1);
}
