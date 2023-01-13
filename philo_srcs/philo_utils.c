#include "philo.h"

int	ft_atoi(char *str)
{
	long	integer;
	long	sign;

	integer = 0;
	sign = 1;
	if (!str)
		return (-1);
	while (*str && (*str == 32 || (*str > 8 && *str < 14)))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		integer = integer * 10 + (*str - '0');
		if ((sign * integer > INT_MAX) || (sign * integer < INT_MIN))
			return (-1);
		str++;
	}
	return (sign * integer);
}

int free_exit(t_table *table, t_philo	**philos)
{
	int i;

	if (table->init.fork)
	{
		pthread_mutex_destroy(&table->lock.msg);
		pthread_mutex_destroy(&table->lock.dead);
		pthread_mutex_destroy(&table->lock.eat);
		free(table->lock.forks);
	}
	if (philos != NULL && table->init.philos)
	{
		i = -1;
		while (++i < table->philo_num)
			pthread_mutex_destroy(((*philos)[i].hands[0]));
		free(*philos);
	}
	// system("leaks philo");
	exit(0);
}

void	update_state(t_philo *philo, char *message, t_state state)
{
	uintmax_t	time;
	static char	*color[] = {RED, GRN, CYN, BLU, MAG, YEL, WHT};

	if (state == EAT)
	{
		pthread_mutex_lock(&philo->table->lock.eat);
		philo->eaten_ms = get_time_ms();
		philo->deadline = philo->eaten_ms + philo->table->die_ms;
		pthread_mutex_unlock(&philo->table->lock.eat);
	}
	pthread_mutex_lock(&philo->table->lock.msg);
	if (!philo_status(philo, DEAD))
	{
		time = get_time_ms() - philo->table->start_ms;
		printf("%s", color[philo->seat % 7]);
		printf("%ju Philosophers [%d] %s", time, philo->seat, message);
		if (philo->table->eat_count && state == EAT)
		{
			pthread_mutex_lock(&philo->table->lock.eat);
			printf(" (%d/%d)", ++philo->times_eaten, philo->table->eat_count);
			pthread_mutex_unlock(&philo->table->lock.eat);
		}
		printf("\n%s", WHT);
	}
	pthread_mutex_unlock(&philo->table->lock.msg);
}

void	usleep_chunks(uintmax_t ms)
{
	uintmax_t		start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
		usleep(50);
}

uintmax_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}