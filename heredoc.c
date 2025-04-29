/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:38:25 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 09:38:46 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	heredoc_child(int write_fd, char *delimiter)
{
	char	*input;

	signal(SIGINT, ft_sigint_on_heredoc_child);
	while (1)
	{
		input = readline(">");
		if (!input)
			break ;	
		if (ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		write(write_fd, input, ft_strlen(input));
		write(write_fd, "\n", 1);
		free(input);
	}
	exit(EXIT_SUCCESS);
}

void	handle_heredoc(int pipefd[2], t_cmd *cmd,
	char *delimiter, int *status)
{
	pid_t	pid;

	check_error(pipe(pipefd));
	cmd->read_from = dup(pipefd[0]);
	pid = fork();
	check_error(pid);
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_child(pipefd[1], delimiter);
		close(pipefd[1]);
	}
	close(pipefd[1]);
	waitpid(pid, status, 0);
	close(pipefd[0]);
}
