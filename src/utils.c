/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledias-d <ledias-d@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 23:12:48 by ledias-d          #+#    #+#             */
/*   Updated: 2025-02-18 23:12:48 by ledias-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Error: gettimeofday failed\n");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time_in_ms)
{
	long	start_time;
	long	target_time;
	long	remaining;

	start_time = get_time();
	target_time = start_time + time_in_ms;
	while (get_time() < target_time)
	{
		remaining = target_time - get_time();
		if (remaining > 1000)
			usleep((remaining / 2) * 1000);
		else
			usleep(remaining * 1000);
	}
}

void	ft_print_status(t_philo *philo, char *status)
{
	if (philo->table->end_table)
		return ;
	pthread_mutex_lock(&philo->table->print);
	printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->table->print);
}

void	free_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->end);
	free(table->forks);
	free(table->philos);
}
