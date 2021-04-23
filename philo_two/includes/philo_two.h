#ifndef FILO_TWO_H
# define FILO_TWO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/time.h>

typedef struct		s_tab
{
	int				philos;
	int				is_dead;
	int				necrologue;
	long			starv;
	long			eat;
	long			sleep;
	long			cycles;
	long			bigb;
	pthread_mutex_t	mutx_print;
}					t_tab;

typedef struct		s_philo
{
	int				id;
	long			lastmeal;
	int				meals;
	t_tab			*tab;
	pthread_t		philo;
}					t_philo;

int					ft_init_table(char **argv, t_tab *tab, int argc);
int					ft_nznum(const char *str);
long				ft_get_time();
void				ft_exit(char *str);
void				ft_wait(long time);
void				ft_print(t_philo *philo, char *str);
void				ft_make_school(t_philo *philo, t_tab *tab, int id);

#endif