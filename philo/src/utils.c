#include "philo.h"

// ? OK
int is_dead(t_philo *philo, int nb)
{
    pthread_mutex_lock(&philo->info->dead);
    if(nb)
        philo->info->stop = 1;
    if(philo->info->stop)
    {
        pthread_mutex_unlock(&philo->info->dead);
        return 1;
    }
    pthread_mutex_unlock(&philo->info->dead);
    return 0;
}

// ? OK
long long timestamp()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// ? OK
void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}

// ? OK
void print(t_philo *philo, char *str)
{
    long int time = -1;
    time = timestamp() - philo->info->t_start;
    if(!philo->info->stop && time >= 0 && time <= INT_MAX && !is_dead(philo, 0))
        printf("%lld %d%s", timestamp() - philo->info->t_start, philo->n, str);
}