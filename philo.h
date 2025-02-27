/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledias-d <ledias-d@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 21:07:29 by ledias-d          #+#    #+#             */
/*   Updated: 2025-02-18 21:07:29 by ledias-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdint.h>

typedef struct s_table t_table;

typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
    t_mutex mutex;
    int     fork_id;
}	t_fork;


typedef struct s_philo
{
    int         id;
    long        meals_counter;
    bool        full;
    long        last_meal_time;
    t_fork      *left_fork;
    t_fork      *right_fork;
    pthread_t   thread;
    t_table     *table;
}	t_philo;

struct s_table
{
    long    num_philos;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    nbr_limits_meals;
    long    start_time;
    bool    end_time;
    t_fork  *forks;
    t_philo *philos;
} ;

/*--- utils.c ---*/

void    error_exit(char *str);
long   get_time(void);

/*--- parsing.c ---*/

long    ft_atol(const char *str);
void    parse_input(char **av, t_table *table);

/*--- init.c ---*/

void    init_table(t_table *table);

/*--- main .c ---*/
#endif