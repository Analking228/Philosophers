/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:47:14 by cjani             #+#    #+#             */
/*   Updated: 2021/04/05 15:47:17 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_tab
{
	int				philos;
	int				is_dead;
	long			starv;
	long			eat;
	long			sleep;
	long			cycles;
	long			bigb;
	sem_t			*polite;
	sem_t			*sem_print;
	sem_t			*sem_control;
	sem_t			*sem_forks;
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
void				ft_exit(char *str);
void				ft_wait(long time);
void				ft_print(t_philo *philo, char *str);
void				ft_make_school(t_philo *philo, t_tab *tab, int id);
void				*ft_acient_greece(void *student);

#endif