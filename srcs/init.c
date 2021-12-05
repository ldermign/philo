/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:15:56 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/05 12:09:53 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_s_threads(t_s *s, int nbr_philo)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		s->thrd[i].id = i;
		s->thrd[i].time_eaten = 0;
		s->thrd[i].date_of_last_meal = 0;
		s->thrd[i].fork1 = 0;
		s->thrd[i].fork2 = 1;
		if (s->thrd[i].id == nbr_philo - 1)
			s->thrd[i].fork2 = -(nbr_philo - 1);
		if (pthread_mutex_init(&s->thrd[i].fourchette, NULL) != 0)
			return (EXIT_FAILURE);
		if (pthread_mutex_init(&(s->thrd[i].mtx_date_of_last_meal), NULL) != 0)
			return (EXIT_FAILURE);
		s->thrd[i].args = &s->data;
		s->thrd[i].death_full = &s->chck;
		s->thrd[i].time_zero = get_time_in_milli();
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_s_checkers(t_check *chck)
{
	chck->wich_dead = -1;
	chck->all_dead = 0;
	chck->how_many_have_eaten = 0;
	chck->all_full = 0;
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
