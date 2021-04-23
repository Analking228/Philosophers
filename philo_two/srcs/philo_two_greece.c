#include "../includes/philo_two.h"

void			ft_make_school(t_philo *philo, t_tab *tab, int id)
{
	philo->id = id;
	philo->tab = tab;
	philo->lastmeal = ft_get_time();
	philo->meals = 0;
	return ;
}