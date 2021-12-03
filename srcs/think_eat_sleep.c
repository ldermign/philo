/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_eat_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:10:12 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/04 00:32:48 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_eating(t_philo *t)
{
	if (mtx_check_one_dead_or_all_full(t->more->death_full) == 1)
		return (1);
	pthread_mutex_lock(&t->mtx_date_of_last_meal);
	t->date_of_last_meal = get_time(t->more->time_zero);
	pthread_mutex_unlock(&t->mtx_date_of_last_meal);
	printf("%ld [%d] is eating.\n", get_time(t->more->time_zero), t->id + 1);
	if (ft_usleep(t->more->args->time_eat * 1000, t->more->death_full) == 1)
		return (1);
	pthread_mutex_lock(&t->mtx_time_eaten);
	t->time_eaten++;
	if (t->time_eaten == t->more->args->must_eat_at_least)
	{
		pthread_mutex_lock(&t->more->death_full->mtx_how_many_have_eaten);
		t->more->death_full->how_many_have_eaten++;
		pthread_mutex_unlock(&t->more->death_full->mtx_how_many_have_eaten);
	}
	pthread_mutex_unlock(&t->mtx_time_eaten);
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
	int	fork1;
	int	fork2;

	fork1 = t->id;
	if (mtx_check_one_dead_or_all_full(t->more->death_full) == 1)
		return (1);
	if (t->id == t->more->args->nbr_philo - 1)
		fork2 = 0;
	else
		fork2 = t->id + 1;
	pthread_mutex_lock(&t[fork1].fourchette);
	if (mtx_check_one_dead_or_all_full(t->more->death_full) == 1
		|| fork1 == fork2)
	{
		pthread_mutex_unlock(&t[fork1].fourchette);
		return (1);
	}
	pthread_mutex_lock(&t[fork2].fourchette);
	printf("%ld [%d] has taken a fork.\n%ld [%d] has taken a fork.\n",
		get_time(t->more->time_zero), t->id + 1, get_time(t->more->time_zero),
		t->id + 1);
	if (is_eating(t) == 1)
		return (unlock_both_fork(t, fork1, fork2, 1));
	return (unlock_both_fork(t, fork1, fork2, 0));
}

int	is_sleeping(t_philo *thrd)
{
	if (mtx_check_one_dead_or_all_full(thrd->more->death_full) == 1)
		return (1);
	printf("%ld [%d] is sleeping.\n", get_time(thrd->more->time_zero),
		thrd->id + 1);
	if (ft_usleep(thrd->more->args->time_sleep * 1000,
			thrd->more->death_full) == 1)
		return (1);
	return (0);
}

int	is_thinking(t_philo *thrd)
{
	if (mtx_check_one_dead_or_all_full(thrd->more->death_full) == 1)
		return (1);
	printf("%ld [%d] is thinking.\n", get_time(thrd->more->time_zero),
		thrd->id + 1);
	return (0);
}
