/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filo_one.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:47:14 by cjani             #+#    #+#             */
/*   Updated: 2021/04/05 15:47:17 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILO_ONE_H
# define FILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>

typedef struct	s_tab
{
	int			philos;
	int			die;
	int			eat;
	int			sleep;
	int			cycle;
}				t_tab;

typedef struct	s_philo
{
	int			id;
	int			lastmeal;
	t_tab		*tab;
	pthread_t	philo;
}				t_philo;

int		ft_init_table(char **argv, t_tab *tab);
int		ft_nznum(const char *str);
void	ft_exit(char *str);


#endif