#include "philo.h"

void print(t_philo *philo, char *str)
{
    pthread_mutex_lock(&(philo->info->print));
    usleep(1000);
    if(!philo->info->stop)
        printf("%lld %d%s", timestamp() - philo->info->t_start, philo->n, str);
    pthread_mutex_unlock(&(philo->info->print));
}