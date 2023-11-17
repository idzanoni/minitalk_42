/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:35:07 by izanoni           #+#    #+#             */
/*   Updated: 2023/11/17 20:10:49 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	write_bit(int sinal);
void	server_sigaction(int sig, siginfo_t *info, void *ucontext);

int	main(void)
{
	int					pid;
	struct sigaction	server_config;

	pid = getpid();
	server_config.sa_handler = NULL;
	server_config.sa_sigaction = server_sigaction;
	server_config.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &server_config, NULL);
	sigaction(SIGUSR2, &server_config, NULL);
	printf("%i\n", pid);
	while (1)
	{
		pause();
	}
	return (0);
}

void	server_sigaction(int sig, siginfo_t *info, void *ucontext)
{
	static int	bit_count;

	if (sig == SIGUSR1)
	{
		write (1, "1", 1);
		bit_count++;
	}
	if (sig == SIGUSR2)
	{
		write (1, "0", 1);
		bit_count++;
	}
	if (bit_count == 8)
	{
		printf("\n");
		bit_count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}
