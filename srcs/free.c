/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:36:24 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/03 14:13:25 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_all_mutex(t_s *s)
{
	int	i;

	i = 0;
	while (i < s->data.nbr_philo)
	{
		pthread_mutex_destroy(&s->thrd[i].fourchette);
		pthread_mutex_destroy(&s->thrd[i].mtx_time_eaten);
		pthread_mutex_destroy(&s->thrd[i].mtx_date_of_last_meal);
		i++;
	}
	pthread_mutex_destroy(&s->chck.mtx_first_death);
	pthread_mutex_destroy(&s->chck.mtx_wich_dead);
	pthread_mutex_destroy(&s->chck.mtx_all_dead);
	pthread_mutex_destroy(&s->chck.mtx_how_many_have_eaten);
	pthread_mutex_destroy(&s->chck.mtx_all_full);
}

void	free_everything(t_s *s)
{
	destroy_all_mutex(s);
	free(s->thrd);
}
