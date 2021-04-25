#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_tab
{
	int				philos;
	long			starv;
	long			eat;
	long			sleep;
	long			cycles;
	long			bigb;
	sem_t			*polite;
	sem_t			*sem_die;
	sem_t			*sem_print;
	sem_t			*sem_control;
	sem_t			*sem_forks;
	sem_t			*wait_cycle;
	sem_t			*exit;
}t_tab;

typedef struct s_philo
{
	int				id;
	long			lastmeal;
	int				meals;
	t_tab			*tab;
	pthread_t		philo;
}t_philo;

int					ft_init_table(char **argv, t_tab *tab, int argc);
int					ft_nznum(const char *str);
long				ft_get_time(void);
void				ft_wait(long time);
void				ft_print(t_philo *philo, char *str);
void				ft_make_school(t_philo *philo, t_tab *tab, int id);
void				*ft_acient_greece(void *student);
void				ft_wait_cycle(t_tab *tab);

#endif
