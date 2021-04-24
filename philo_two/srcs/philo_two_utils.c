/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filo_one_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:47:29 by cjani             #+#    #+#             */
/*   Updated: 2021/04/05 15:47:31 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void		ft_wait(long time)
{
	long				start;
	long				stop;

	start = ft_get_time();
	stop = start;
	while (stop - start < time)
	{
		stop = ft_get_time();
		usleep(10);
	}
}

void				ft_print(t_philo *philo, char *str)
{
	long			time;

	sem_wait(philo->tab->sem_print);
	if (philo->tab->is_dead)
	{
		sem_post(philo->tab->sem_print);
		return ;
	}
	time = 0;
	time = (ft_get_time() - philo->tab->bigb);
	printf("[%ld] %d %s\n", time, philo->id + 1, str);
	sem_post(philo->tab->sem_print);
}

long		ft_get_time()
{
	struct timeval	tv;
	long			utime;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_exit(char *str)
{
	printf("%s\n", str);
}

int		ft_nznum(const char *str)
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
