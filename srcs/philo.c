#include "philo.h"

t_data	d_data;

void	init_data(char **argv)
{
	d_data.total_philo = ft_atoi(argv[1]);
	d_data.time_to_die = ft_atoi(argv[2]);
	d_data.time_to_eat = ft_atoi(argv[3]);
	d_data.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		d_data.times_philo_eat = ft_atoi(argv[5]);
	else
		d_data.times_philo_eat = 2147483647;
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf ("Error!\n");
		return (1);
	}
	init_data(argv);
}