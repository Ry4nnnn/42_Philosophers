#include "philo.h"

static	int	ft_isdigit(char c)
{
	int	chr;

	chr = '0';
	while (chr <= '9')
	{
		if (c == chr)
			return (1);
		chr++;
	}
	return (-1);
}

static	int	check_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) < 0)
			return (-1);
		i++;
	}
	return (1);
}

int	check_error(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_digit(argv[i]) < 0)
			return (-1);
		i++;
	}
	return (1);
}