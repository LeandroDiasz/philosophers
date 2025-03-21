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

#include "../philo.h"

void    start_simulation(t_table *table)
{
    int i;
    pthread_t monitor_thread;

    i = 0;
    while (i < table->num_philos)
    {
        pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]);
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

void    monitor(t_table *table)
{
    int i;

    while (1)
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
int check_philo_status(t_table *table, t_philo *philo)
{
    if (philo->meals_counter == table->nbr_limits_meals)
    {
        philo->full = true;
        table->full_philos++;
    }
    if (table->full_philos == table->num_philos)
    {
        table->end_table = true;
        return (1);
    }
    if (get_time() - philo->last_meal_time > table->time_to_die)
    {
        printf("%ld %d died\n", get_time() - table->start_time, philo->id);
        table->end_table = true;
        return (1);
    }
    return (0);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        ft_usleep(100);
    while (!philo->table->end_table)
    {
        pthread_mutex_lock(&philo->left_fork->mutex);
        ft_print_status(philo, "has taken a fork");
        pthread_mutex_lock(&philo->right_fork->mutex);
        ft_print_status(philo, "has taken a fork");
        ft_print_status(philo, "is eating");
        ft_usleep(philo->table->time_to_eat);
        philo->last_meal_time = get_time();
        philo->meals_counter++;
        pthread_mutex_unlock(&philo->left_fork->mutex);
        pthread_mutex_unlock(&philo->right_fork->mutex);
        ft_print_status(philo, "is sleeping");
        ft_usleep(philo->table->time_to_sleep);
        ft_print_status(philo, "is thinking");
    }
    return (NULL);
}