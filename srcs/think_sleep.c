/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:01:18 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/04 17:45:47 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_sleeping(t_philo *thrd)
{
	if (mtx_check_one_dead_or_all_full(thrd->death_full) == 1)
		return (1);
	printf("%ld [%d] is sleeping.\n", get_time(thrd->time_zero),
		thrd->id);
	if (ft_usleep(thrd->args->time_sleep * 1000,
			thrd->death_full) == 1)
		return (1);
	return (0);
}

int	is_thinking(t_philo *thrd)
{
	if (mtx_check_one_dead_or_all_full(thrd->death_full) == 1)
		return (1);
	printf("%ld [%d] is thinking.\n", get_time(thrd->time_zero),
		thrd->id);
	return (0);
}
