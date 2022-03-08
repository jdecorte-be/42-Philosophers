#include "philo.h"

long long timestamp()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void check_death(t_info *data,  t_philo *philo)
{
    int  i = 0;

    while(1)
    {
        pthread_mutex_lock(&data->eat);
        // printf("------> %lld\n", timestamp() - philo[i].last_eat);
        if (timestamp() - philo[i].last_eat > data->t_die)
        {
            printf("%lld %d died\n", timestamp(), i + 1);
            exit(-1);
        }
        pthread_mutex_unlock(&data->eat);
        usleep(1000);
        if(i == data->n_philo - 1)
            i = 0;
        i++;
    }
}

// chaque philo == thread
void    *philo_life(t_philo *philo)
{
    while(1)
    {
        pthread_mutex_init(&philo->fork.right, NULL); 
        pthread_mutex_init(&philo->fork.left, NULL); 
        pthread_mutex_lock(&philo->fork.right);
        printf("%lld %d has taken a fork\n", timestamp() ,philo->n + 1);
        pthread_mutex_lock(&philo->fork.left);
        printf("%lld %d has taken a fork\n", timestamp(), philo->n + 1);

        // time for eat
        pthread_mutex_lock(&philo->info->eat);
        printf("%lld %d is eating\n", timestamp(), philo->n + 1);
        philo->last_eat = timestamp();
        // printf("%d\n", philo->t_sleep);
        usleep(philo->t_eat);
        pthread_mutex_unlock(&philo->info->eat);



        // time to sleep
        printf("%lld %d is sleeping\n", timestamp(), philo->n + 1);
        usleep(philo->t_sleep);
    
        // drop fork
        printf("%lld %d is thinking\n", timestamp(), philo->n + 1);
        pthread_mutex_unlock(&philo->fork.right);
        pthread_mutex_unlock(&philo->fork.left);
    }
}

int main(int ac, char **av)
{
    t_info *data = malloc(sizeof(t_info));
    if (!data)
        return -1;
    var_init(data, av);
    philo_init(data);
}
