#include "philo.h"

static void	*routine(void *extable)
{
	int i;
	int philo;
	t_table *table;

	table = extable;
	pthread_mutex_lock(&table->mutex);
	philo = table->curr_philo;
	pthread_mutex_unlock(&table->mutex);
	while 
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
		pthread_join(&table->group[i++].philo, NULL);
	return ;
}