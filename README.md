# philosophers


<h3>This project contain multiple implementation of the dining philosophers problem.</h3>

**philo_one** - philosopher with threads and mutex

**philo_two** - philosopher with threads and semaphore

**philo_three** - philosopher with processes and semaphore

Program arguments: number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat].
The last one is optional, time in ms.

e.g.: ./philo_one 4 410 200 200
