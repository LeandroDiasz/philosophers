/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledias-d <ledias-d@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 23:11:40 by ledias-d          #+#    #+#             */
/*   Updated: 2025-02-18 23:11:40 by ledias-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_table table;
	if (ac == 5 || ac == 6)
	{
		parse_input(av, &table);
		init_table(&table);
		start_simulation(&table);
		free_table(&table);
	}
	else
	{
		error_exit("Error: Wrong number of arguments\n");
		return (0);
	}
}