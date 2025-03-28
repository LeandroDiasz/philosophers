/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledias-d <ledias-d@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-21 20:39:31 by ledias-d          #+#    #+#             */
/*   Updated: 2025-03-21 20:39:31 by ledias-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	start_simulation(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_create(&table->philos[i].thread, NULL, routine,
			&table->philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, (void *)monitor, table);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

void    take_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork->mutex);
    ft_print_status(philo, "has taken a fork");
    pthread_mutex_lock(&philo->right_fork->mutex);
    ft_print_status(philo, "has taken a fork");
}

void    eat(t_philo *philo)
{	
    ft_print_status(philo, "is eating");
    ft_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->eating);
    philo->last_meal_time = get_time();
    philo->meals_counter++;
	pthread_mutex_unlock(&philo->eating);
}

void    unlock_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->left_fork->mutex);
    pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		ft_usleep(100);
	while ((philo->table->nbr_limits_meals == -1
			|| philo->meals_counter < philo->table->nbr_limits_meals)
		&& (!philo->table->end_table))
	{
		if (philo->table->num_philos == 1)
		{
			ft_print_status(philo, "has taken a fork");
			return (NULL);
		}
		take_forks(philo);
        eat(philo);
        unlock_forks(philo);
		ft_print_status(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		ft_print_status(philo, "is thinking");
		usleep(1);
	}
	philo->full = true;
	return (NULL);
}
