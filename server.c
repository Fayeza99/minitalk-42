/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:50:42 by fnikzad           #+#    #+#             */
/*   Updated: 2024/01/23 17:43:34 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	hndler(int signum, siginfo_t *info, void *context)
{
	static int	bits;
	static int	i;

	(void)context;
	if (signum == SIGUSR1)
	{
		i |= (0x01 << bits);
	}
	bits++;
	if (bits == 8)
	{
		if (i == 0)
		{
			kill(info->si_pid, SIGUSR1);
		}
		write(1, &i, sizeof(char));
		bits = 0;
		i = 0;
	}
}

void	ft_putchar(int c)
{
	write (1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write (1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar('0' + (n % 10));
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr(getpid());
	write (1, "\n", 1);
	sa.sa_sigaction = hndler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
