/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledias-d <ledias-d@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-19 17:43:36 by ledias-d          #+#    #+#             */
/*   Updated: 2025-02-19 17:43:36 by ledias-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atol(const char *str)
{
	long	res;

	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			error_exit("Error: Negative number of philosophers");
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	if (res > INT_MAX)
		error_exit("Error: Number of philosophers too big");
	else if (res == 0)
		error_exit("Error: Number of philosophers is 0");
	return (res);
}

void	parse_input(char **av, t_table *table)
{
	table->num_philos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		table->nbr_limits_meals = ft_atol(av[5]);
	else
		table->nbr_limits_meals = -1;
}
