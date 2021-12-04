/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:06:48 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/04 17:06:41 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <inttypes.h>
# include "philo_struct.h"
# define NORMAL "\e[0m"
# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define BBLACK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGREEN "\e[1;32m"
# define BYELLOW "\e[1;33m"
# define BBLUE "\e[1;34m"
# define BMAGENTA "\e[1;35m"
# define BCYAN "\e[1;36m"
# define BWHITE "\e[1;37m"

/*
**	PARSING
*/

int		parsing(int ac, char **av, t_s *s);

/*
**	INIT
*/

int		init_s_threads(t_s *s, int nbr_philo);
int		init_s_checkers(t_check *chck);

/*
**	START
*/

int		start_threads_philo_and_checkers(t_s *s);

/*
**	ROUTINE
*/

void	*routine(void *data);
void	*check_for_a_death_or_a_full_tummy(void *data);

/*
**	VITAL FUNCTIONS
*/

int		take_both_fork(t_philo *t);
int		is_sleeping(t_philo *thrd);
int		is_thinking(t_philo *thrd);

/*
**	TIME
*/

long	get_time_in_milli(void);
long	get_time_in_micro(void);
long	get_time(long time_zero);
int		ft_usleep(long time, t_check *chck);

/*
**	MEMORY
*/

int		mtx_all_full(t_check *chck, int nbr_philo);
int		mtx_all_dead(t_check *chck, int nbr_philo);
int		mtx_check_one_dead_or_all_full(t_check *chck);

/*
**	UTILS PARSING
*/

int		ft_atoi(const char *str);
int		ft_int_strchr(const char *str, int c);
int		ft_isdigit(int c);

/*
**	FREE
*/

void	free_everything(t_s *s);

#endif
