/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filo_one_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:47:29 by cjani             #+#    #+#             */
/*   Updated: 2021/04/05 15:47:31 by cjani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	ft_init_tab(t_tab *tab)
{
	tab->philos = 0;
	tab->die = 0;
	tab->eat = 0;
	tab->sleep = 0;
	tab->cycles = 0;
}

void	ft_args(t_tab *tab, int	num, int count)
{
	if (count == 1)
		tab->philos = num;
	else if (count == 2)
		tab->die = num;
	else if (count == 3)
		tab->eat = num;
	else if (count == 4)
		tab->sleep = num;
	else if (count == 5)
		tab->cycles = num;
}

int		ft_parse_args(char **av, t_tab *tab)
{
	int	i;
	int	rez;

	i = 0;
	while (++i < 6)
	{
		if ((rez = ft_nznum(av[i])) > 0)
			ft_args(tab, rez, i);
		else
			return (0);
	}
	return (1);
}

int		ft_init_table(char **argv, t_tab *tab)
{
	ft_init_tab(tab);
	if (!ft_parse_args(argv, tab))
		ft_exit("Bad argument");
	return (1);
}