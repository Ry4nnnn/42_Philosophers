/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:53:28 by welim             #+#    #+#             */
/*   Updated: 2023/04/06 12:06:04 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, char **argv)
{
	table->philo_num = ft_atoi(argv[1]);
	table->eat_ms = ft_atoi(argv[3]);
	table->die_ms = ft_atoi(argv[2]);
	table->sleep_ms = ft_atoi(argv[4]);
	table->eat_count = ft_atoi(argv[5]);
	if (table->eat_count == 0)
	{
		printf (ERR_VALIDARGS);
		free_exit(table, NULL);
	}
	else if (!(argv[5]))
		table->eat_count = 0;
	if (table->philo_num < 1 || table->philo_num > 200 || table->die_ms < 60
		|| table->eat_ms < 60 || table->sleep_ms < 60 || table->eat_count < 0)
	{
		printf (ERR_VALIDARGS);
		free_exit(table, NULL);
	}
	return (0);
}

int	create_table(t_table *table, char **argv)
{
	table->philo_num = 0;
	table->die_ms = 0;
	table->eat_ms = 0;
	table->sleep_ms = 0;
	table->start_ms = get_time_ms();
	table->eat_count = 0;
	table->philos_eaten = 0;
	table->is_dead = 0;
	table->init.fork = 0;
	table->init.philos = 0;
	init_table(table, argv);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
		return (printf (ERR_VALIDARGS ERR_INPUT));
	create_table(&table, argv);
	if (init_mutex(&table) || init_philos(&table, &philos))
	{
		printf ("Error initializing mutexes\n");
		free_exit(&table, &philos);
		return (1);
	}
	if (create_threads(&table, philos))
	{
		printf ("Error creating threads\n");
		free_exit(&table, &philos);
		return (1);
	}
	free_exit(&table, &philos);
	return (0);
}
