#include "philo.h"

static void	*check_death(void *oldtable)
{
	t_table		*table;
	int			philo;
	long long 	time_stamp;
	
	philo = 0;
	table = oldtable;
	while (table->start_death == 0)
		usleep(table->philo);
	while (philo < table->philo && table->philo_death == 0)
	{
		time_stamp = get_time();
		if (table->finish_eating == table->philo)
			table->philo_death = 1;
		if (time_stamp > table->group[philo].death_time && table->death == 0)
		{
			printf(RED "%lld %d died\n", time_stamp, philo);
			table->philo_death = 1;
		}
		if (philo == table->philo - 1)
			philo = 0;
		else
			philo++;
	}
	return (0);
}

static void	*routine(void *extable)
{
	int i;
	int philo;
	t_table *table;

	table = extable;
	pthread_mutex_lock(&table->mutex);
	philo = table->curr_philo;
	pthread_mutex_unlock(&table->mutex);
	while (table->start_routine == 0)
		usleep(table->philo);
	philo_think(table, philo);
	if (philo % 2 == 0)
		usleep(table->eat_ms * 500);
	table->start_death = 1;
	i = 0;
	while (i < table->philo_eat_count && table->philo_death == 0)
	{
		if (table->philo == 1)
			return (0);
		philo_live(table, philo);
		i++;
	}
	return (0);
}

void	philo(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->mutex, NULL);
	while (i < table->philo)
		pthread_mutex_init(&table->group[i++].fork, NULL);
	i = 0;
	while (i < table->philo)
		pthread_create(&table->group[i++].philo, NULL, *routine, table);
	table->start_routine = 1;
	pthread_create(&table->death, NULL, *check_death, table);
	pthread_join(table->death, NULL);
	i = 0;
	while (i < table->philo)
		pthread_join(table->group[i++].philo, NULL);
	return ;
}