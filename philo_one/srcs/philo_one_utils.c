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

#include "../includes/philo_one.h"

void		ft_print(t_philo *ph, char *str)
{
	pthread_mutex_lock(&ph->tab->mutx_print);
	printf("%ld : %d %s\n", ft_get_time() - ph->tab->bigbang, ph->id, str);
	pthread_mutex_unlock(&ph->tab->mutx_print);
}

long		ft_get_time()
{
	struct timeval	*tv;
	long			utime;

	tv = (struct timeval *)malloc(sizeof(struct timeval));
	gettimeofday(tv, NULL);
	utime = tv->tv_usec;
	free(tv);
	return (utime);
}

int		ft_isspace(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\n')
		|| (c == '\v') || (c == '\f') || (c == '\r'))
		return (1);
	return (0);
}

void	ft_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}

int		ft_nznum(const char *str)
{
	int		res;

	res = 0;
	while (ft_isspace(*str))
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
