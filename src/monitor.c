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
		printf("%ld %d died\n", get_time() - table->start_time, table->philos[0].id);
		table->end_table = true;
        table->philos[0].end_table = true;
        pthread_mutex_unlock(&table->philos[0].right_fork->mutex);
		return;
    }
	while (!table->end_table)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (check_philo_status(table, &table->philos[i]))
				return ;
			i++;
		}
	}
}
int	check_philo_status(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->meals_counter == table->nbr_limits_meals)
		table->full_philos++;
	if (table->full_philos == table->num_philos)
	{
		table->end_table = true;
		return (1);
	}
	if (get_time() - philo->last_meal_time > table->time_to_die)
	{
		printf("%ld %d died\n", get_time() - table->start_time, philo->id);
		table->end_table = true;
		while (i < table->num_philos)
		{
			table->philos[i].end_table = true;
			i++;
		}
		return (1);
	}
	return (0);
}