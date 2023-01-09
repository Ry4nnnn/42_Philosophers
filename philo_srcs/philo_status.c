 #include "philo.h"

void	philo_think(t_table *table, int philo)
{
	printf(MAG "%lld %d is thinking\n", get_time(), philo);
	table->group[philo].death_time = get_time()
		+ (long long)table->die_ms;
}

void	philo_live(t_table *table, int philo)
{
	pthread_mutex_lock(&table->group[philo].fork);
	pthread_mutex_lock(&table->group[(philo + 1) % table->philo_num].fork);
	philo_eat(table, philo);
	pthread_mutex_unlock(&table->group[philo].fork);
	pthread_mutex_unlock(&table->group[(philo + 1) % table->philo_num].fork);
	philo_sleep(table, philo);
}

void	philo_sleep(t_table *table, int philo)
{
	if (table->philo_death == 0)
		printf(YEL "%lld %d is sleeping\n", get_time(), philo);
	if (table->group[philo].eat_count == table->philo_eat_count)
		table->finish_eating++;
	ft_msleep(table->sleep_ms, get_time());
}

void	philo_eat(t_table *table, int philo)
{
	if (table->philo_death == 0)
	{
		printf(CYN "%lld %d has taken a fork\n", get_time(), philo);
		printf(CYN "%lld %d has taken a fork\n", get_time(), philo);
		printf(GRN "%lld %d is eating\n", get_time(), philo);
	}
	table->group[philo].eat_count++;
	table->group[philo].death_time = get_time() + (long long)table->die_ms;
	ft_msleep(table->eat_ms, get_time());
}
