/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:24:57 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 09:41:51 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	g_signal = 0;

void	ft_sigint_handle(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sigint_on_child(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
}

void	ft_sigint_on_heredoc_child(int sig)
{
	g_signal = 42;
	(void)sig;
	write(1, "\n", 1);
	exit(EXIT_SUCCESS);
}

void	ft_sigquit_handle(int sig)
{
	g_signal = sig;
	write(1, "Quit (core dumped)\n", 20);
}
