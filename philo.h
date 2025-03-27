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

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex				mutex;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	long				start_time;
	bool				full;
	long				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_mutex				philo_mutex;
	t_table				*table;
	pthread_t			thread;
}						t_philo;

struct					s_table
{
	long				num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limits_meals;
	long				start_time;
	bool				end_table;
	long				full_philos;
	t_mutex				print;
	t_mutex				end;
	t_fork				*forks;
	t_philo				*philos;
};

/*--- utils.c ---*/

void					error_exit(char *str);
long					get_time(void);
void					ft_print_status(t_philo *philo, char *status);
void					ft_usleep(long time_in_ms);
void					free_table(t_table *table);

/*--- parsing.c ---*/

long					ft_atol(const char *str);
void					parse_input(char **av, t_table *table);

/*--- init.c ---*/

void					init_table(t_table *table);
void					init_philosophers(t_table *table);

/*--- philo.c ---*/
void					start_simulation(t_table *table);
void					*routine(void *arg);
void					take_forks(t_philo *philo);
void					eat(t_philo *philo);
void					unlock_forks(t_philo *philo);

/*--- monitor.c ---*/
void					monitor(t_table *table);
int						check_philo_status(t_table *table, t_philo *philo);
int						verify_end(t_philo *philo);
int						count_full(t_table *table);

#endif