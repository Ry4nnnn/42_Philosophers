#include "philo.h"

static int	double_check(char *args)
{
	int i;
	char *c;
	int test;

	i = ft_atoi(args);
	c = ft_itoa(i);
	test = ft_strcmp(args, c);
	free (c);
	if (test == 0)
		return (1);
	return (0);
}

int	check_error(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		if (!(double_check(argv[i])))
			return (0);
		if (argv[i][0] == '-')
			return (0);
		if (ft_atoi(argv[i]) >= INT_MAX)
			return (0);
		i++;
	}
	return (1);
}