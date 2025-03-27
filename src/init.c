/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledias-d <ledias-d@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-21 18:01:22 by ledias-d          #+#    #+#             */
/*   Updated: 2025-02-21 18:01:22 by ledias-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_table(t_table *table)
{
	int	i;

	table->start_time = get_time();
	table->end_table = false;
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->num_philos);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->end, NULL);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		i++;
	}
	init_philosophers(table);
}

void	init_philosophers(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philos);
	table->full_philos = 0;
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].full = false;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->num_philos];
		table->philos[i].last_meal_time = get_time();
		table->philos[i].start_time = table->start_time;
		table->philos[i].table = table;
		pthread_mutex_init(&table->philos[i].philo_mutex, NULL);
		i++;
	}
}
