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

int	new_norm_trolls(t_tab *tab, int	i, t_philo *philo, pid_t *pid)
{
	while (++i < tab->philos)
	{
		ft_make_school(&philo[i], tab, i);
		pid[i] = fork();
		if (pid[i] < 0)
			exit(1);
		else if (pid[i] == 0)
			ft_acient_greece(&philo[i]);
	}
	return (i);
}

int	ft_init_philos(t_tab *tab)
{
	t_philo		*philo;
	pid_t		*pid;
	int			i;

	i = -1;
	philo = (t_philo *)malloc(tab->philos * sizeof(t_philo));
	pid = (pid_t *)malloc((tab->philos + 1) * sizeof(pid_t));
	tab->bigb = ft_get_time();
	i = new_norm_trolls(tab, i, philo, pid);
	pid[i] = fork();
	if ((pid[i]) < 0)
		exit(1);
	else if (pid[i] == 0)
		ft_wait_cycle(tab);
	sem_wait(tab->exit);
	i = -1;
	while (++i < tab->philos)
		kill(pid[i], SIGKILL);
	free(pid);
	free(philo);
	return (1);
}

int	main(int argc, char **argv)
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
	sem_close(tab.polite);
	sem_close(tab.exit);
	sem_close(tab.wait_cycle);
	return (0);
}
