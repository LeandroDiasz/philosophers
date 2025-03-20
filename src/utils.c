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

#include "philo.h"

void    error_exit(char *str)
{
    printf("%s\n", str);
    exit(EXIT_FAILURE);
}

long   get_time(void)
{
    struct timeval  tv;

    if (gettimeofday(&tv, NULL))
        error_exit("Error: gettimeofday failed\n");
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}