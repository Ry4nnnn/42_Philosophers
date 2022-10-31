#include "philo.h"

void	init_table(t_table *table, int argc, char **argv)
{
	int i;
	table->philo = ft_atoi(argv[1]);
	table->eat_ms = ft_atoi(argv[3]);
	table->die_ms = ft_atoi(argv[2]);
	table->sleep_ms = ft_atoi(argv[4]);
	if (argc == 6)
		table->philo_eat_count = ft_atoi(argv[5]);
	else
		table->philo_eat_count = 2147483647;
	table->curr_philo = 0;
	table->start_routine = 0;
	table->group = malloc(sizeof(t_philo) * table->philo);
	i = 0;
	while (i < table->philo)
		table->group[i++].eat_count = 0;
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!check_error(argc, argv))
	{
		printf ("Error!\n");
		return (0);
	}
	init_table(&table, argc, argv);
	philo(&table);
	return (0);
}