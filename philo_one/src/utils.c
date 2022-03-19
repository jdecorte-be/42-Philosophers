#include "philo.h"

void print(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->info->print);
    printf("%lld %d %s", timestamp(), philo->n, str);
    pthread_mutex_unlock(&philo->info->print);
}