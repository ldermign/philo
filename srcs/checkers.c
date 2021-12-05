/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 08:21:16 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/05 10:32:32 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	someone_is_dead_abort(t_check *chck, int id)
{
	pthread_mutex_lock(&chck->mtx_wich_dead);
	chck->wich_dead = id;
	pthread_mutex_unlock(&chck->mtx_wich_dead);
}

static int	always_checking_if_someone_s_dead(t_s *s)
{
	int		i;
	long	time_till_last_meal;

	i = 0;
	while (i < s->data.nbr_philo)
	{
		if (mtx_all_full(&s->chck, s->data.nbr_philo) == 1)
			return (0);
		pthread_mutex_lock(&s->thrd[i].mtx_date_of_last_meal);
		time_till_last_meal = get_time(s->thrd->time_zero)
			- s->thrd[i].date_of_last_meal;
		pthread_mutex_unlock(&s->thrd[i].mtx_date_of_last_meal);
		if (time_till_last_meal > s->data.time_die)
		{
			someone_is_dead_abort(&s->chck, i);
			return (1);
		}
		i++;
		if (i == s->data.nbr_philo)
			i = 0;
	}
	return (0);
}

void	mtx_all_are_full(t_s *s)
{
	pthread_mutex_lock(&s->chck.mtx_all_full);
	s->chck.all_full = 1;
	pthread_mutex_unlock(&s->chck.mtx_all_full);
}

void	*check_for_a_death_or_a_full_tummy(void *data)
{
	t_s	*s;

	s = (t_s *)data;
	if (always_checking_if_someone_s_dead(s) == 1)
	{
		while (1)
		{
			if (mtx_all_dead(&s->chck, s->data.nbr_philo) == 1)
			{
				printf("%ld [%d] died.\n",
					get_time(s->thrd->time_zero),
					s->chck.wich_dead);
				return (NULL);
			}
		}
	}
	else
		mtx_all_are_full(s);
	return (NULL);
}
