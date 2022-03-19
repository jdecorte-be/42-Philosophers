#include "philo.h"

long long timestamp()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int main(int ac, char **av)
{
    t_info *data = malloc(sizeof(t_info));
    if (!data)
        return -1;
    var_init(data, av);
    philo_init(data);
}
