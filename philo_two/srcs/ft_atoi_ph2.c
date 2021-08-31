

#include "philo_two.h"

int				ft_atoi(const char *nbr)
{
	int				i;
	int				sign;
	unsigned long	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((nbr[i] >= '\t' && nbr[i] <= '\r') || nbr[i] == ' ')
		i++;
	if (nbr[i] == '+' || nbr[i] == '-')
	{
		sign = (nbr[i] == '-') ? -1 : 1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		if ((res * 10 + (nbr[i] - '0')) < res)
			return ((sign > 0) ? -1 : 0);
		res = res * 10 + (nbr[i] - '0');
		i++;
	}
	return (res * sign);
}

void			*philo_is_full(t_philo *ph, int philo_num)
{
	int	kludge_for_not_dying_in_death_checking;

	kludge_for_not_dying_in_death_checking = ph->params.time_to_die;
	sem_wait(ph->s_for_getting_philo_number);
	ph->fed_philo_amount++;
	sem_post(ph->s_for_getting_philo_number);
	ph->time_of_last_meal[philo_num - 1] +=
	kludge_for_not_dying_in_death_checking;
	return (NULL);
}
