#ifndef	PHILO_H
#define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <sys/time.h>

typedef struct l_info
{
	int n_philo;
	int t_die;
	int	t_eat;
	int t_sleep;
	int n_eat;
	pthread_mutex_t	eat;
}       t_info;

typedef struct l_fork
{
	pthread_mutex_t	right;
	pthread_mutex_t left;
} 	  t_fork;

typedef struct l_philo
{
	int	n;
	int	t_eat;
	int t_sleep;
	int	last_eat;
	t_info	*info;
	t_fork	fork;
} 	  t_philo;

void philo_init(t_info *data);
void    *philo_life(t_philo *philo);
long long timestamp();
void check_death(t_info *data,  t_philo *philo);
void var_init(t_info *data, char **av);




#endif