#include "philo.h"

static void	init_table(t_table *table, int argc, char **argv)
{
	int i;
	table->philo_num = ft_atoi(argv[1]);
	table->eat_ms = ft_atoi(argv[3]);
	table->die_ms = ft_atoi(argv[2]);
	table->sleep_ms = ft_atoi(argv[4]);
	table->philo_eat_count = INT_MAX;
	if (argc == 6)
		table->philo_eat_count = ft_atoi(argv[5]);
	table->curr_philo = 0;
	table->start_routine = 0;
	table->start_death = 0;
	table->finish_eating = 0;
	table->group = malloc(sizeof(t_philo) * table->philo_num);
	i = 0;
	while (i < table->philo_num)
		table->group[i++].eat_count = 0;
	while (i < table->philo_num)
		table->group[i++].death_time = get_time() + 100000;
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
	free(table.group);
	return (0);
}