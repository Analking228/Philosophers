#include "../includes/philo_three.h"

void		end_of_eat(t_tab *tab)
{
	int		i;

	i = -1;
	while (++i < tab->philos)
		sem_wait(tab->end_of_eat);
	sem_post(tab->exit);
}

void				ft_print(t_philo *philo, char *str, int flag)
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