/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledias-d <ledias-d@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-24 22:53:00 by ledias-d          #+#    #+#             */
/*   Updated: 2025-02-24 22:53:00 by ledias-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(&philo->left_fork->mutex);
        printf("%ld %d has taken a fork\n", get_time() - philo->table->start_time, philo->id);
        pthread_mutex_lock(&philo->right_fork->mutex);
        printf("%ld %d has taken a fork\n", get_time() - philo->table->start_time, philo->id);
        printf("%ld %d is eating\n", get_time() - philo->table->start_time, philo->id);
        usleep(philo->table->time_to_eat * 1000);
        philo->last_meal_time = get_time();
        philo->meals_counter++;
        pthread_mutex_unlock(&philo->left_fork->mutex);
        pthread_mutex_unlock(&philo->right_fork->mutex);
        printf("%ld %d is sleeping\n", get_time() - philo->table->start_time, philo->id);
        usleep(philo->table->time_to_sleep * 1000);
        printf("%ld %d is thinking\n", get_time() - philo->table->start_time, philo->id);
    }
    return (NULL);
}