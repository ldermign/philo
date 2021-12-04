/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:15:56 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/04 14:59:16 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_right_left_fork(t_philo *thrd, int id_philo, int nbr_philo)
{
	if (id_philo == nbr_philo)
	{
		thrd->fork1 = -(nbr_philo - 1);
		thrd->fork2 = 0;
		return ;
	}
	if (id_philo % 2 == 0)
	{
		thrd->fork1 = 0;
		thrd->fork2 = 1;
	}
	else
	{
		thrd->fork1 = 1;
		thrd->fork2 = 0;
	}
}

int	init_s_threads(t_s *s, void *addr_more, int nbr_philo)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		s->thrd[i].more = addr_more;
		s->thrd[i].id = i;
		s->thrd[i].time_eaten = 0;
		s->thrd[i].date_of_last_meal = 0;
		get_right_left_fork(&s->thrd[i], i, nbr_philo);
		if (pthread_mutex_init(&(s->thrd[i].mtx_time_eaten), NULL) != 0)
			return (EXIT_FAILURE);
		if (pthread_mutex_init(&(s->thrd[i].mtx_date_of_last_meal), NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_s_checkers(t_check *chck)
{
	chck->first_death = 0;
	chck->wich_dead = -1;
	chck->all_dead = 0;
	chck->how_many_have_eaten = 0;
	chck->all_full = 0;
	if (pthread_mutex_init(&(chck->mtx_first_death), NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(chck->mtx_wich_dead), NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(chck->mtx_all_dead), NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(chck->mtx_how_many_have_eaten), NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(chck->mtx_all_full), NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_s_more(t_s *s, int nbr_philo)
{
	int				i;

	i = 0;
	while (i < nbr_philo)
	{
		if (pthread_mutex_init(&s->thrd[i].fourchette, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	s->thrd->more->args = &s->data;
	s->thrd->more->death_full = &s->chck;
	s->thrd->more->time_zero = get_time_in_milli();
	return (EXIT_SUCCESS);
}
