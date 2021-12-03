/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:08:49 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/04 00:10:47 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	one_is_dead(t_check *chck)
{
	pthread_mutex_lock(&chck->mtx_all_dead);
	chck->all_dead++;
	pthread_mutex_unlock(&chck->mtx_all_dead);
}

void	*routine(void *data)
{
	t_philo	*thrd;

	thrd = (t_philo *)data;
	while (1)
	{
		if (is_thinking(thrd) == 1)
		{
			one_is_dead(thrd->more->death_full);
			return (NULL);
		}
		if (take_both_fork(thrd) == 1)
		{
			one_is_dead(thrd->more->death_full);
			return (NULL);
		}
		if (is_sleeping(thrd) == 1)
		{
			one_is_dead(thrd->more->death_full);
			return (NULL);
		}
	}
	return (NULL);
}
