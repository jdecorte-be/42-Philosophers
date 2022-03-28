#include "philo.h"

int main(int ac, char **av)
{
    if(ac != 5 && ac != 6)
        return 0;
    t_info data;
    var_init(&data, av);
    philo_init(&data);

}
