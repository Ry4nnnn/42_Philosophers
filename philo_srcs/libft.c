#include "philo.h"

long	ft_atoi(const char *str)
{
	long	result;
	long	sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ((*str >= 48 && *str <= 57) && *str != '\0')
	{
		result = (*str - 48) + (result * 10);
		str++;
	}
	return (result * sign);
}

static int	intlen(long nb)
{
	int	res;

	if (nb == 0)
		return (1);
	res = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		res++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	long	nb;

	len = intlen(n);
	nb = n;
	if (nb == 0 && len == 1)
		return (ft_strdup("0"));
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len--] = 0;
	if (!nb)
		res[len] = '\0';
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	while (nb != 0)
	{
		res[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (res);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		c1 = s1[i];
		c2 = s2[i++];
		if ((c1 - c2) != 0)
			return (c1 - c2);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	slen;
	char	*dst;

	slen = ft_strlen(s);
	dst = (char *)malloc(slen + 1);
	if (!dst)
		return (0);
	i = 0;
	while (i < slen)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
