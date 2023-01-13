#include "philo.h"

// int	ft_atoi(char *str)
// {
// 	long	integer;
// 	long	sign;

// 	integer = 0;
// 	sign = 1;
// 	if (!str)
// 		return (-1);
// 	while (*str && (*str == 32 || (*str > 8 && *str < 14)))
// 		str++;
// 	if (*str == '-')
// 		sign *= -1;
// 	if (*str == '-' || *str == '+')
// 		str++;
// 	while (*str)
// 	{
// 		if (*str < '0' || *str > '9')
// 			return (-1);
// 		integer = integer * 10 + (*str - '0');
// 		if ((sign * integer > INT_MAX) || (sign * integer < INT_MIN))
// 			return (-1);
// 		str++;
// 	}
// 	return (sign * integer);
// }

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