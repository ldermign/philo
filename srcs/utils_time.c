/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:15:36 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/03 09:20:18 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(long time_zero)
{
	struct timeval	tmps;

	gettimeofday(&tmps, NULL);
	return (((tmps.tv_sec * 1000) + (tmps.tv_usec / 1000)) - time_zero);
}

long	get_time_in_milli(void)
{
	struct timeval	tmps;

	gettimeofday(&tmps, NULL);
	return ((tmps.tv_sec * 1000) + (tmps.tv_usec / 1000));
}

long	get_time_in_micro(void)
{
	struct timeval	tmps;

	gettimeofday(&tmps, NULL);
	return ((tmps.tv_sec * 1000000) + tmps.tv_usec);
}

int	ft_usleep(long time, t_check *chck)
{
	long	first_time;
	long	time_passed;
	long	time_after;

	first_time = get_time_in_micro();
	time_passed = 0;
	while (time_passed < time)
	{
		if (mtx_check_one_dead_or_all_full(chck) == 1)
			return (1);
		usleep(10);
		time_after = get_time_in_micro();
		time_passed = time_after - first_time;
	}
	return (0);
}
