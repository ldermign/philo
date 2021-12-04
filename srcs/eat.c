/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:10:12 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/04 19:02:10 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_eating(t_philo *t)
{
	if (mtx_check_one_dead_or_all_full(t->death_full) == 1)
		return (1);
	pthread_mutex_lock(&t->mtx_date_of_last_meal);
	t->date_of_last_meal = get_time(t->time_zero);
	printf("%ld [%d] is eating.\n", get_time(t->time_zero), t->id);
	if (ft_usleep(t->args->time_eat * 1000, t->death_full) == 1)
	{
		pthread_mutex_unlock(&t->mtx_date_of_last_meal);
		return (1);
	}
	pthread_mutex_unlock(&t->mtx_date_of_last_meal);
	t->time_eaten++;
	if (t->time_eaten == t->args->must_eat_at_least)
	{
		pthread_mutex_lock(&t->death_full->mtx_how_many_have_eaten);
		t->death_full->how_many_have_eaten++;
		pthread_mutex_unlock(&t->death_full->mtx_how_many_have_eaten);
	}
	return (0);
}

int	unlock_both_fork(t_philo *t, int fork1, int fork2, int code_err)
{
	pthread_mutex_unlock(&t[fork1].fourchette);
	pthread_mutex_unlock(&t[fork2].fourchette);
	if (code_err == 1)
		return (1);
	return (0);
}

int	take_both_fork(t_philo *t)
{
	if (mtx_check_one_dead_or_all_full(t->death_full) == 1)
		return (1);
	pthread_mutex_lock(&t[t->fork1].fourchette);
	if (mtx_check_one_dead_or_all_full(t->death_full) == 1
		|| t->args->nbr_philo == 1)
	{
		pthread_mutex_unlock(&t[t->fork1].fourchette);
		return (1);
	}
	pthread_mutex_lock(&t[t->fork2].fourchette);
	if (mtx_check_one_dead_or_all_full(t->death_full) == 1)
		return (unlock_both_fork(t, t->fork1, t->fork2, 1));
	printf("%ld [%d] has taken a fork.\n", get_time(t->time_zero), t->id);
	printf("%ld [%d] has taken a fork.\n", get_time(t->time_zero), t->id);
	if (is_eating(t) == 1)
		return (unlock_both_fork(t, t->fork1, t->fork2, 1));
	return (unlock_both_fork(t, t->fork1, t->fork2, 0));
}
