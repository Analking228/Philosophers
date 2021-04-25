/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 17:47:07 by skarry            #+#    #+#             */
/*   Updated: 2020/11/17 14:02:57 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int			ft_init_philos(t_tab *tab)
{
	t_philo		philo[tab->philos];
	pid_t		pid[tab->philos + 1];
	int			i;

	i = -1;
	tab->bigb = ft_get_time();
	while (++i < tab->philos)
	{
		ft_make_school(&philo[i], tab, i);
		pid[i] = fork();
		if (pid[i] < 0)
			exit(1);
		else if (pid[i] == 0)
			ft_acient_greece(&philo[i]);
	}
	if ((pid[i] = fork()) < 0)
		exit(1);
	else if (pid[i] == 0)
		ft_wait_cycle(tab);
	sem_wait(tab->exit);
	i = -1;
	while (++i < tab->philos)
		kill(pid[i], SIGKILL);
	return (1);
}

int		main(int argc, char **argv)
{
	t_tab	tab;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong arguments' amount");
		return (1);
	}
	if (ft_init_table(argv, &tab, argc))
		return (1);
	ft_init_philos(&tab);
	sem_close(tab.sem_control);
	sem_close(tab.sem_die);
	sem_close(tab.sem_print);
	sem_close(tab.sem_forks);
	sem_close(tab.waiter);
	sem_close(tab.exit);
	sem_close(tab.end_of_eat);
	return (0);
}
