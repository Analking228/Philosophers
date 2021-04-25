#include "../includes/philo_three.h"

int				ft_cycles(int meals, int cycles)
{
	if ((cycles == 0) || (meals < cycles))
		return (1);
	return (0);
}

void			ft_make_school(t_philo *philo, t_tab *tab, int id)
{
	philo->id = id;
	philo->tab = tab;
	philo->lastmeal = 0;
	philo->meals = 0;
}

void		sem_death(t_philo *philo)
{
	sem_wait(philo->tab->sem_die);
	ft_print(philo, "is dead");
	sem_post(philo->tab->exit);
}

void		*ft_death_patrol(void *philos)
{
	t_philo		*philo;

	philo = (t_philo *)philos;
	sem_wait(philo->tab->sem_control);
	while ((ft_get_time() - philo->lastmeal) < philo->tab->starv &&
			ft_cycles(philo->meals,philo->tab->cycles))
	{
		sem_post(philo->tab->sem_control);
		usleep(10);
		sem_wait(philo->tab->sem_control);
	}
	sem_post(philo->tab->sem_control);
	if (!(ft_cycles(philo->meals, philo->tab->cycles)))
	{
		sem_post(philo->tab->end_of_eat);
		exit(0);
	}
	else
		sem_death(philo);
	return (NULL);
}

void		ft_greece_life(t_philo *philo)
{
	sem_wait(philo->tab->waiter);
	sem_wait(philo->tab->sem_forks);
	ft_print(philo, "has taken a fork");
	sem_wait(philo->tab->sem_forks);
	ft_print(philo, "has taken a fork");
	sem_post(philo->tab->waiter);
	ft_print(philo, "is eating");
	philo->lastmeal = ft_get_time();
	ft_wait(philo->tab->eat);
	sem_post(philo->tab->sem_forks);
	sem_post(philo->tab->sem_forks);
	ft_print(philo, "is sleeping");
	ft_wait(philo->tab->sleep);
	ft_print(philo, "is thinking");
	philo->meals++;
}

void		*ft_acient_greece(void *student)
{
	t_philo		*philo;
	pthread_t	death_patrol;

	philo = (t_philo *)student;
	philo->lastmeal = ft_get_time();
	pthread_create(&death_patrol, NULL, ft_death_patrol, philo);
	while (ft_cycles(philo->meals,philo->tab->cycles) && !philo->tab->is_dead)
		ft_greece_life(philo);
	pthread_join(death_patrol, NULL);
	return (NULL);
}