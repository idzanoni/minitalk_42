/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:35:03 by izanoni           #+#    #+#             */
/*   Updated: 2023/11/17 19:58:35 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_bits(int pid, char octeto);
void	client_sigaction(int sig, siginfo_t *info, void *ucontext);
int	g_recebido;

int	main(int argc, char **argv)
{
	int					pid_s;
	int					pid_c;
	struct sigaction	client_config;

	client_config.sa_handler = NULL;
	client_config.sa_flags = SA_SIGINFO;
	client_config.sa_sigaction = client_sigaction;
	sigaction(SIGUSR1, &client_config, NULL);
	pid_s = atoi(argv[1]);
	pid_c = getpid();
	print_bits(pid_s, 4);
	return (0);
}

void	print_bits(int pid, char octeto)
{
	int	i;
	int	bit;

	i = 7;
	while (i >= 0)
	{
		g_recebido = 0;
		bit = (octeto >> i) & 1;
		if (bit == 1)
			kill (pid, SIGUSR1);
		else
			kill (pid, SIGUSR2);
		i--;
		while (!g_recebido)
			;
	}
	printf ("\n");
}

void	client_sigaction(int sig, siginfo_t *info, void *ucontext)
{
	if (sig == SIGUSR1)
		printf("ok\n");
	g_recebido = 1;
}
