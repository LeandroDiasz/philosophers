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

void	ft_usleep(int time_in_ms)
{
	long	finish_time;
	long	current_time;

	current_time = get_time();
	finish_time = current_time + time_in_ms;
	while (current_time < finish_time)
	{
		usleep(((finish_time - current_time) * 1000) / 2);
		current_time = get_time();
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
	pthread_mutex_destroy(&table->print);
	free(table->forks);
	free(table->philos);
}