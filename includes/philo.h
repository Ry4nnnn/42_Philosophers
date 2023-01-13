/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:02:36 by welim             #+#    #+#             */
/*   Updated: 2023/01/13 19:45:54 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_VALIDARGS "Error: Please provide valid arguments\n"
# define ERR_INPUT "./philo [philos] [die_ms] [eat_ms] [sleep_ms] opt:[eat_no]\n"

//status
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIED "died"
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

typedef enum e_state {
	FORK = 0,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	EATEN,
	END
}			t_state;

typedef struct s_init
{
	int		fork;
	int		philos;
}				t_init;

typedef struct s_lock
{
	pthread_mutex_t	msg;
	pthread_mutex_t	dead;
	pthread_mutex_t	eat;
	pthread_mutex_t	*forks;
}			t_lock;

typedef struct	s_table
{
	int				philo_num;
	int				die_ms;
	int				eat_ms;
	int				sleep_ms;
	uintmax_t		start_ms;
	int				eat_count;
	int				philos_eaten;
	int				is_dead;
	t_init			init;
	t_lock			lock;
}				t_table;

typedef struct s_philo
{
	pthread_t		id;
	int				seat;
	int				times_eaten;
	uintmax_t		eaten_ms;
	uintmax_t		deadline;
	t_table			*table;
	pthread_mutex_t	*hands[2];
}					t_philo;

//libft.c
int			ft_atoi(char *str);
long long	get_time(void);
void		ft_msleep(int time, long long start);  

//philo_status.c
void		philo_think(t_table *table, int philo);
void		philo_live(t_table *table, int philo);
void		philo_sleep(t_table *table, int philo);
void		philo_eat(t_table *table, int philo);

//philo.c
void		philo(t_table *table);

int 	init_table(t_table *table, char **argv);
#endif