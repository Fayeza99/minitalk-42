/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:50:31 by fnikzad           #+#    #+#             */
/*   Updated: 2024/01/23 17:43:51 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	client_hndler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR1)
	{
		write (1, "received", 8);
	}
}

void	send_chars(int p, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)) != 0)
			kill(p, SIGUSR1);
		else
		{
			kill(p, SIGUSR2);
		}
		usleep(100);
		bit++;
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	sa;

	if (argc == 3)
	{
		i = 0;
		sa.sa_sigaction = client_hndler;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sa, NULL);
		pid = ft_atoi(argv[1]);
		while (argv[2][i])
		{
			send_chars(pid, argv[2][i]);
			i++;
		}
		send_chars(pid, '\n');
		send_chars(pid, '\0');
	}
	else
	{
		return (1);
	}
	return (0);
}
