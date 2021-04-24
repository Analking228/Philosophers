#include "../includes/philo_two.h"

void	ft_init_tab(t_tab *tab)
{
	tab->philos = 0;
	tab->is_dead = 0;
	tab->starv = 0;
	tab->eat = 0;
	tab->sleep = 0;
	tab->cycles = 0;
	tab->bigb = 0;
	sem_unlink("sem_control");
	sem_unlink("sem_print");
	sem_unlink("waiter");
	tab->waiter = sem_open("waiter", O_CREAT, 0770, 1);
	tab->sem_control = sem_open("sem_control", O_CREAT, 0770, 1);
	tab->sem_print = sem_open("sem_print", O_CREAT, 0770, 1);
}

void	ft_args(t_tab *tab, int	num, int count)
{
	if (count == 1)
	{
		tab->philos = num;
		sem_unlink("sem_forks");
		tab->sem_forks = sem_open("sem_forks", O_CREAT, 0770, tab->philos);
	}
	else if (count == 2)
		tab->starv = num;
	else if (count == 3)
		tab->eat = num;
	else if (count == 4)
		tab->sleep = num;
	else if (count == 5)
		tab->cycles = num;
}

int		ft_parse_args(char **av, t_tab *tab, int argc)
{
	int	i;
	int	rez;

	i = 0;
	while (++i < argc)
	{
		if ((rez = ft_nznum(av[i])) > 0)
			ft_args(tab, rez, i);
		else
			return (1);
	}
	return (0);
}

int		ft_init_table(char **argv, t_tab *tab, int argc)
{
	ft_init_tab(tab);
	if (ft_parse_args(argv, tab, argc))
	{
		ft_exit("Bad argument");
		return (1);
	}
	return (0);
}