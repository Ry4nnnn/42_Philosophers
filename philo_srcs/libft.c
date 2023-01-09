#include "philo.h"

int	ft_atoi(const char *str)
{
	long	result;
	long	negative;

	result = 0;
	negative = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negative = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
		if (result * negative > 2147483647)
			return (-1);
		if (result * negative < -2147483648)
			return (0);
	}
	return (result * negative);
}

long long	get_time(void)
{
	struct timeval	timer;
	long long		result;

	gettimeofday(&timer, NULL);
	result = (long long)timer.tv_sec * 1000000;
	result = result + (long long)timer.tv_usec;
	result = result / 1000;
	return (result);
}

void	ft_msleep(int time, long long start)
{
	long long	cur;

	cur = 0;
	while (cur < (long long)time)
	{
		cur = get_time() - start;
		usleep(100);
	}
}