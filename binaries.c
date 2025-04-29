/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:39:02 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 16:39:19 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	apply_redirections(t_cmd *cmd)
{
	if (cmd->read_from != -42)
		dup2(cmd->read_from, STDIN_FILENO);
	if (cmd->write_to != -42)
		dup2(cmd->write_to, STDOUT_FILENO);
}

void	handle_signals_in_child(void)
{
	signal(SIGINT, ft_sigint_on_child);
	signal(SIGQUIT, ft_sigquit_handle);
}

void	execute_cmd(t_main *main, t_cmd *cmd)
{
	if (cmd->tkns != NULL && cmd->tkns[0][0] == '.')
		ft_relative_path(cmd);
	else if (cmd->tkns != NULL && cmd->tkns[0][0] == '/')
		ft_absolute_path(cmd);
	else if (cmd->tkns != NULL)
		ft_path(main, cmd, -1);
	free_all(main);
	exit(127);
}

void	wait_for_child(t_main *main, pid_t pid)
{
	waitpid(pid, &main->status, 0);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (WIFEXITED(main->status))
		main->status = WEXITSTATUS(main->status);
	else if (WIFSIGNALED(main->status))
		main->status = WTERMSIG(main->status) + 128;
	dup2(main->stdout_dup, STDOUT_FILENO);
	dup2(main->stdin_dup, STDIN_FILENO);
}

void	ft_execute_binary(t_main *main, t_cmd *cmd)
{
	pid_t	pid;

	if (is_invalid_redir(cmd))
		return ;
	//apply_redirections(cmd);
	pid = fork();
	if (pid == -1)
		handle_fork_error(cmd);
	handle_signals_in_child();
	if (pid == 0)
		execute_cmd(main, cmd);
	else
		wait_for_child(main, pid);
}
