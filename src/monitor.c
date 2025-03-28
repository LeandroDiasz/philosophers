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
		ft_print_status(&table->philos[0], "died");
		table->end_table = true;
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
		//usleep(1);
	}
}
int	check_philo_status(t_table *table, t_philo *philo)
{
	int	i;
	long long	time;

	i = 0;
	pthread_mutex_lock(&philo->eating);
	if (philo->full)
		table->full_philos++;
	pthread_mutex_unlock(&philo->eating);
	if (table->full_philos == table->num_philos)
	{
		table->end_table = true;
		return (1);
	}
	time = get_time() - philo->last_meal_time;
	if (time > table->time_to_die)
	{
		ft_print_status(philo, "died");
		table->end_table = true;
		return (1);
	}
	return (0);
}