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


typedef struct l_philo
{
	int		n;
	bool 	is_eating;
	struct l_info	*info;
	long long last_eat;
    pthread_t thread;
	pthread_mutex_t	fork_r;
	pthread_mutex_t fork_l;
} 	  t_philo;

typedef struct l_info
{
	int n_philo;
	int t_die;
	int	t_eat;
	int t_sleep;
	int n_eat;
	int stop;
	t_philo *philo;
	pthread_mutex_t	print;
}       t_info;

void philo_init(t_info *data);
void    *philo_life(void *philo);
long long timestamp();
void var_init(t_info *data, char **av);
void    *philo_life(void *phi);
void print(t_philo *philo, char *str);



#endif