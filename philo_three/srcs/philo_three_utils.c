/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:15:19 by cjani             #+#    #+#             */
/*   Updated: 2021/04/25 18:15:21 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	ft_wait_cycle(t_tab *tab)
{
	int		i;

	i = -1;
	while (++i < tab->philos)
		sem_wait(tab->wait_cycle);
	sem_post(tab->exit);
}

void	ft_wait(long time)
{
	long			start;
	long			stop;

	start = ft_get_time();
	stop = start;
	while (stop - start < time)
	{
		stop = ft_get_time();
		usleep(10);
	}
}

void	ft_print(t_philo *philo, char *str)
{
	long			time;

	sem_wait(philo->tab->sem_print);
	time = 0;
	time = (ft_get_time() - philo->tab->bigb);
	printf("[%ld] %d %s\n", time, philo->id + 1, str);
	sem_post(philo->tab->sem_print);
}

long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_nznum(const char *str)
{
	int		res;

	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		return (res);
	if (*str == '+')
		str++;
	while ((*str >= '0' && *str <= '9') && res > -1)
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str)
		return (-1);
	return (res);
}
