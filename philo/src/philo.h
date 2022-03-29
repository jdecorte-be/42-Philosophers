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
# include <limits.h>

typedef struct l_philo
{
	
	int		n;
	int		m_count;
	bool 	is_eating;
    pthread_t thread;
	long int last_eat;
	struct l_info	*info;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t fork_l;
} 	  t_philo;

typedef struct l_info
{
	int		philo_eat;
	int n_philo;
	int t_die;
	int	t_eat;
	int t_sleep;
	int n_eat;
	int stop;
	long int t_start;
	t_philo *philo;
	pthread_mutex_t	print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	dead;
}       t_info;

void	ft_usleep(int ms);
int philo_init(t_info *data);
void    *philo_life(void *philo);
long long timestamp();
int var_init(t_info *data, char **av);
void    *philo_life(void *phi);
void print(t_philo *philo, char *str);
int is_dead(t_philo *philo, int nb);


#endif