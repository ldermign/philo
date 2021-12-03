/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:37:14 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/04 00:12:39 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

typedef struct s_arg
{
	int		nbr_philo;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		must_eat_at_least;
}	t_ag;

typedef struct s_checkers
{
	pthread_t		checker;
	pthread_mutex_t	mtx_first_death;
	bool			first_death;
	pthread_mutex_t	mtx_wich_dead;
	int				wich_dead;
	pthread_mutex_t	mtx_all_dead;
	int				all_dead;
	pthread_mutex_t	mtx_how_many_have_eaten;
	int				how_many_have_eaten;
	pthread_mutex_t	mtx_all_full;
	int				all_full;
}	t_check;

typedef struct s_storage
{
	t_ag			*args;
	t_check			*death_full;
	long			time_zero;
}	t_store;

typedef struct s_philo
{
	pthread_mutex_t	fourchette;
	int				id;
	pthread_t		philo;
	pthread_mutex_t	mtx_time_eaten;
	int				time_eaten;
	pthread_mutex_t	mtx_date_of_last_meal;
	long			date_of_last_meal;
	t_store			*more;
}	t_philo;

typedef struct s_struct
{
	t_ag	data;
	t_philo	*thrd;
	t_check	chck;
}	t_s;

#endif
