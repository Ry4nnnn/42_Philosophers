/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:02:36 by welim             #+#    #+#             */
/*   Updated: 2022/11/14 17:56:49 by welim            ###   ########.fr       */
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

//color
#define RED		"\x1B[31m"
#define GRN		"\x1B[32m"
#define YEL		"\x1B[33m"
#define BLU		"\x1B[34m"
#define MAG		"\x1B[35m"
#define CYN		"\x1B[36m"
#define WHT		"\x1B[37m"
#define RESET	"\x1B[0m"

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
	int				start_death;
	int				finish_eating;
	int				philo_death;
}				t_table;

//libft.c
long	ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

//check_error.c
int	check_error(int argc, char **argv);

//philo_status.c
void	philo_think(t_table *table, int philo);
void	philo_live(t_table *table, int philo);
void	philo_sleep(t_table *table, int philo);
void	philo_eat(t_table *table, int philo);
void	ft_msleep(int time, long long start);

//philo.c
void	philo(t_table *table);

//philo_utils.c
long long	get_time(void);

#endif