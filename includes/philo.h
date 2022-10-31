/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:02:36 by welim             #+#    #+#             */
/*   Updated: 2022/10/31 12:29:02 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_VALIDARGS "Error: Please provide valid arguments\n"
# define ERR_INPUT "./philo [philos] [die_ms] [eat_ms] [sleep_ms] opt:[eat_no]\n"

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIED "is died"
# define MSG_EATEN "is done eating"

typedef struct	s_philo
{
	pthread_t		philo;
	pthread_mutex_t	fork;
	int				eat_count;
	long long		death_time;
}	t_philo;

typedef struct	s_table
{
	t_philo			*group;
	pthread_t		death;
	pthread_mutex_t mutex;
	int				philo;
	int				die_ms;
	int				eat_ms;
	int				sleep_ms;
	int				philo_eat_count;
	int				curr_philo;
	int				start_routine;
}				t_table;

long	ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

int	check_error(int argc, char **argv);

#endif