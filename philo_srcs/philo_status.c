/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:53:34 by welim             #+#    #+#             */
/*   Updated: 2023/01/13 21:56:25 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_start(void *args)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)args;
	if (pthread_create(&tid, NULL, &philo_check, args))
		return ((void *)1);
	if (philo->seat % 2 == 0)
		usleep(1000);
	while (!philo_status(philo, END))
	{
		philo_action(philo);
		usleep(1000);
	}
	pthread_join(tid, NULL);
	return (NULL);
}

void	*philo_check(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&philo->table->lock.eat);
		if (get_time_ms() > philo->deadline)
			return (philos_eaten_dead(philo, DEAD));
		pthread_mutex_unlock(&philo->table->lock.eat);
		if (philo_status(philo, EATEN))
			return (philos_eaten_dead(philo, EATEN));
		usleep(1000);
	}
	return (NULL);
}

void	*philos_eaten_dead(t_philo *philo, t_state state)
{
	if (state == EATEN)
	{
		update_state(philo, MSG_EATEN, EATEN);
		pthread_mutex_lock(&philo->table->lock.dead);
		philo->table->philos_eaten++;
		pthread_mutex_unlock(&philo->table->lock.dead);
	}
	if (state == DEAD)
	{
		update_state(philo, MSG_DIED, DEAD);
		pthread_mutex_lock(&philo->table->lock.dead);
		philo->table->is_dead = 1;
		pthread_mutex_unlock(&philo->table->lock.dead);
		pthread_mutex_unlock(&philo->table->lock.eat);
		pthread_mutex_unlock(philo->hands[0]);
		pthread_mutex_unlock(philo->hands[1]);
	}
	return (NULL);
}

int	philo_status(t_philo *philo, t_state state)
{
	int		done;

	if (state == EATEN || state == END)
	{
		pthread_mutex_lock(&philo->table->lock.eat);
		done = 0;
		if (philo->table->eat_count
			&& philo->times_eaten == philo->table->eat_count)
			done = 1;
		pthread_mutex_unlock(&philo->table->lock.eat);
	}
	if (state == DEAD || (state == END && done == 0))
	{
		pthread_mutex_lock(&philo->table->lock.dead);
		done = 0;
		if (philo->table->is_dead
			|| philo->table->philos_eaten == philo->table->philo_num)
			done = 1;
		pthread_mutex_unlock(&philo->table->lock.dead);
	}
	return (done);
}

void	philo_action(t_philo *philo)
{
	int		side;

	if (philo->seat % 2 == 0)
		side = 0;
	else
		side = 1;
	pthread_mutex_lock(philo->hands[side]);
	update_state(philo, MSG_FORK, FORK);
	pthread_mutex_lock(philo->hands[!side]);
	update_state(philo, MSG_FORK, FORK);
	update_state(philo, MSG_EAT, EAT);
	usleep_chunks(philo->table->eat_ms);
	pthread_mutex_unlock(philo->hands[0]);
	pthread_mutex_unlock(philo->hands[1]);
	update_state(philo, MSG_SLEEP, SLEEP);
	usleep_chunks(philo->table->sleep_ms);
	update_state(philo, MSG_THINK, THINK);
}
