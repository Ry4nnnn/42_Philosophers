/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:53:39 by welim             #+#    #+#             */
/*   Updated: 2023/01/13 21:55:14 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table, t_philo *philos)
{
	int		i;

	i = -1;
	while (philos && ++i < table->philo_num)
	{
		if (pthread_create(&philos[i].id, NULL, &philo_start, &philos[i]))
			return (1);
	}
	i = -1;
	while (++i < table->philo_num)
		pthread_join(philos[i].id, NULL);
	return (0);
}

int	init_mutex(t_table *table)
{
	int		i;

	if (pthread_mutex_init(&table->lock.msg, NULL))
		return (1);
	if (pthread_mutex_init(&table->lock.dead, NULL))
		return (1);
	if (pthread_mutex_init(&table->lock.eat, NULL))
		return (1);
	table->lock.forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (table->lock.forks == NULL)
		return (1);
	i = -1;
	while (++i < table->philo_num)
	{
		if (pthread_mutex_init(&(table->lock.forks[i]), NULL))
			return (1);
	}
	table->init.fork = 1;
	return (0);
}

int	init_philos(t_table *table, t_philo **philos)
{
	int		i;

	*philos = NULL;
	*philos = malloc(sizeof(t_philo) * table->philo_num);
	if (*philos == NULL)
		return (1);
	i = -1;
	while (++i < table->philo_num)
	{
		(*philos)[i].id = 0;
		(*philos)[i].seat = i + 1;
		(*philos)[i].times_eaten = 0;
		(*philos)[i].eaten_ms = get_time_ms();
		(*philos)[i].deadline = (*philos)[i].eaten_ms + table->die_ms;
		(*philos)[i].table = table;
		(*philos)[i].hands[0] = &(table->lock.forks[i]);
		if (i == (*philos)[i].table->philo_num - 1)
			(*philos)[i].hands[1] = &(table->lock.forks[0]);
		else
			(*philos)[i].hands[1] = &(table->lock.forks[i + 1]);
	}
	table->init.philos = 1;
	return (0);
}
