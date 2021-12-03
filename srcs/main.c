/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 00:15:00 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/04 00:15:33 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_store	tmp_more;
	t_s		s;

	if (parsing(ac, av, &s) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	s.thrd = malloc(sizeof(t_philo) * s.data.nbr_philo);
	if (s.thrd == NULL)
		return (EXIT_FAILURE);
	if (init_s_checkers(&s.chck) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_s_threads(&s, &tmp_more, s.data.nbr_philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_s_more(&s, s.data.nbr_philo) == EXIT_FAILURE)
	{
		free(s.thrd);
		return (EXIT_FAILURE);
	}
	start_threads_philo_and_checkers(&s);
	free_everything(&s);
	return (EXIT_SUCCESS);
}
