/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lock_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 08:36:37 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/05 12:20:51 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mtx_all_dead(t_check *chck, int nbr_philo)
{
	pthread_mutex_lock(&chck->mtx_all_dead);
	if (chck->all_dead == nbr_philo)
	{
		pthread_mutex_unlock(&chck->mtx_all_dead);
		return (1);
	}
	pthread_mutex_unlock(&chck->mtx_all_dead);
	return (0);
}

int	mtx_all_full(t_check *chck, int nbr_philo)
{
	pthread_mutex_lock(&chck->mtx_how_many_have_eaten);
	if (chck->how_many_have_eaten == nbr_philo)
	{
		pthread_mutex_unlock(&chck->mtx_how_many_have_eaten);
		return (1);
	}
	pthread_mutex_unlock(&chck->mtx_how_many_have_eaten);
	return (0);
}

int	mtx_check_one_dead_or_all_full(t_check *chck)
{
	pthread_mutex_lock(&chck->mtx_wich_dead);
	if (chck->wich_dead != -1)
	{
		pthread_mutex_unlock(&chck->mtx_wich_dead);
		return (1);
	}
	pthread_mutex_unlock(&chck->mtx_wich_dead);
	pthread_mutex_lock(&chck->mtx_all_full);
	if (chck->all_full == 1)
	{
		pthread_mutex_unlock(&chck->mtx_all_full);
		return (1);
	}
	pthread_mutex_unlock(&chck->mtx_all_full);
	return (0);
}
