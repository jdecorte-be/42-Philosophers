#include "philo.h"

int	free_all(t_info *data)
{
	int	i;

	i = 0;
	if (data->philo)
		free(data->philo);
    while (i < data->n_philo)
    {
        if (pthread_mutex_destroy(&(data->philo[i].fork_r)) != 0)
            return (free_all(data));
        if (pthread_mutex_destroy(&(data->philo[i].fork_l)) != 0)
            return (free_all(data));
        i++;
    }
		// free(data->forks);
	i = pthread_mutex_unlock(&(data->print));
	if (i == 0)
	{
		if (pthread_mutex_destroy(&(data->print)) != 0)
			return (free_all(data));
	}
	return (1);
}

long long timestamp()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int main(int ac, char **av)
{
    t_info data;
    var_init(&data, av);
    philo_init(&data);
    // free_all(&data);

}
