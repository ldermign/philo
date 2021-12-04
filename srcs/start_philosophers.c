/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:46:07 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/04 14:03:30 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_threads(t_s *s)
{
	int	i;

	i = 0;
	while (i < s->data.nbr_philo)
	{
		if (pthread_join(s->thrd[i].philo, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_join(s->chck.checker, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	start_threads_philo_and_checkers(t_s *s)
{
	int	i;

	i = 0;
	while (i < s->data.nbr_philo)
	{
		if (pthread_create(&s->thrd[i].philo, NULL,
				&routine, &s->thrd[i]) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_create(&s->chck.checker, NULL,
			&check_for_a_death_or_a_full_tummy, s) != 0)
		return (EXIT_FAILURE);
	if (join_threads(s) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
