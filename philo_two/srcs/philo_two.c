#include "../includes/philo_two.h"

int			ft_init_philos(t_tab *tab)
{
	t_philo	philo[tab->philos];
	int		i;

	i = 0;
	tab->bigb = ft_get_time();
	while (i < tab->philos)
	{
		ft_make_school(&philo[i], tab, i);
		pthread_create(&philo[i].philo, NULL, &ft_acient_greece, &philo[i]);
		++i;
	}
	i = -1;
	while (++i < tab->philos)
		pthread_join(philo[i].philo, NULL);
	return (1);
}

int		main(int argc, char **argv)
{
	int		i;
	t_tab	tab;

	if (argc < 5 || argc > 6)
	{
		ft_exit("Wrong arguments' amount");
		return (1);
	}
	if (ft_init_table(argv, &tab, argc))
		return (1);
	ft_init_philos(&tab);
	sem_close(tab.sem_control);
	sem_close(tab.sem_print);
	sem_close(tab.sem_forks);
	sem_close(tab.waiter);
	return (0);
}