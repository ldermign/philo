/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:08:33 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/03 13:43:46 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long int	ft_atol(const char *str)
{
	int				i;
	int				neg;
	long long int	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			neg = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	nbr *= neg;
	return (nbr);
}

static void	recup_args(char **av, t_ag *data)
{
	data->nbr_philo = ft_atol(av[1]);
	data->time_die = ft_atol(av[2]);
	data->time_eat = ft_atol(av[3]);
	data->time_sleep = ft_atol(av[4]);
	if (av[5])
		data->must_eat_at_least = ft_atol(av[5]);
	else
		data->must_eat_at_least = -1;
}

static int	check_if_int(char *arg)
{
	int				i;
	int				len_arg;
	long long int	nbr;

	i = 0;
	len_arg = 0;
	nbr = 0;
	while (arg[i])
	{
		i++;
		len_arg++;
	}
	nbr = ft_atol(arg);
	if (len_arg > 10 || nbr > 2147483647 || nbr < -2147483648)
	{
		printf("Not above int.");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_args_letter(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (i < ac - 1)
	{
		j = 0;
		if (check_if_int(av[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("No letters, only numbers.\n");
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parsing(int ac, char **av, t_s *s)
{
	if (ac > 6 || ac < 5)
	{
		printf("Wrong number of arguments.\n");
		return (EXIT_FAILURE);
	}
	if (check_args_letter(ac, &av[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	recup_args(av, &s->data);
	if (s->data.nbr_philo == 0)
	{
		printf("Not enough philosohers.\n");
		return (EXIT_FAILURE);
	}
	if (s->data.time_die < 60 || s->data.time_eat < 60
		|| s->data.time_sleep < 60)
	{
		printf("Not enough time for philosohers to do anything...\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
