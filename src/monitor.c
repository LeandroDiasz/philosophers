/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledias-d <ledias-d@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-21 20:38:02 by ledias-d          #+#    #+#             */
/*   Updated: 2025-03-21 20:38:02 by ledias-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	monitor(t_table *table)
{
	int	i;

    if (table->num_philos == 1)
    {
        ft_usleep(table->time_to_die);
		ft_print_status(table->philos, "died");
		table->end_table = true;
		return;
    }	
	while (1)
	{
		if (verify_end(&table->philos[0]))
			return ;
		i = 0;
		while (i < table->num_philos)
		{
			if (check_philo_status(table, &table->philos[i]))
				return ;
			i++;
		}
	}
}
int	count_full(t_table *table)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philos[i].philo_mutex);
		if (table->philos[i].meals_counter == table->nbr_limits_meals)
			full++;
		pthread_mutex_unlock(&table->philos[i].philo_mutex);
		i++;
	}
	return (full);
}

int	check_philo_status(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->end);
	if (count_full(table) == table->num_philos)
	{
		table->end_table = true;
		pthread_mutex_unlock(&table->end);
		return (1);
	}
	pthread_mutex_unlock(&table->end);
	pthread_mutex_lock(&philo->philo_mutex);
	if (get_time() - philo->last_meal_time > table->time_to_die)
	{
		ft_print_status(philo, "died");
		pthread_mutex_lock(&table->end);
		table->end_table = true;
		pthread_mutex_unlock(&table->end);
		pthread_mutex_unlock(&philo->philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	return (0);
}

int		verify_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->end);
	if (philo->table->end_table)
	{
		pthread_mutex_unlock(&philo->table->end);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->end);
	return (0);
}
