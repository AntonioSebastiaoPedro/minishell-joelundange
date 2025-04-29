/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:59:02 by llundage          #+#    #+#             */
/*   Updated: 2025/04/29 22:47:18 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_execute(t_main *main, t_cmd *cmd)
{
	if (ft_is_builtin((*cmd).tkns[0]))
		main->status = ft_execute_builtins(*cmd);
	else
		ft_execute_binary(main, cmd);
}
void	ft_exec_child(t_main *main, t_cmd *cmd)
{
	// pipe(main->pipefd);
	// cmd->read_from = main->pipefd[0];
	// cmd->write_to = main->pipefd[1];
	// if (cmd->read_from != -42)
	// {
	// 	dup2(cmd->read_from, STDIN_FILENO);
	// 	close(cmd->read_from);
	// }
	// if (cmd->write_to != -42)
	// {
	// 	dup2(cmd->write_to, STDOUT_FILENO);
	// 	close(cmd->write_to);
	// }
	ft_execute(main, cmd);
	exit(main->status);
}

void	start_execution(t_main *main)
{
	int	i;

	if (main->qtd_cmds == 0)
		return ;
	if (main->qtd_cmds == 1)
	{
		if (main->cmds[0].tkns != NULL && main->cmds[0].exit_status == 0)
			ft_execute(main, &main->cmds[0]);
		else
			main->status = main->cmds[0].exit_status;
		return ;
	}
	i = 0;
	while (main->cmds && i < main->qtd_cmds)
	{
		if (main->cmds[i].tkns != NULL && main->cmds[i].exit_status == 0)
		{
			// if (main->cmds[i].nxt != NULL)
			// {
			// 	pipe(main->pipefd);
			// 	main->cmds[i].write_to = main->pipefd[1];//verif antes fd de redir
			// 	//close(main->pipefd[1]);
			// 	main->cmds[i].nxt->read_from = main->pipefd[0];//verif antes fd de redir
			// 	//close(main->pipefd[0]);
			// }
			
				if (i != 0)
				{
					main->cmds[i].read_from = main->pipefd[0];//verif antes fd de redir
					//close(main->pipefd[0]);
				}
				if (i != main->qtd_cmds - 1)
				{
					pipe(main->pipefd);
					main->cmds[i].write_to = main->pipefd[1];//verif antes fd de redir
						//close(main->pipefd[1]);
				}
					
			main->cmds[i].pid = fork();
			if (main->cmds[i].pid == 0)
				ft_exec_child(main, &main->cmds[i]);
		}
		else
			main->status = main->cmds[i].exit_status;
		i++;
	}
	while (i)
	{
		i--;
		waitpid(main->cmds[i].pid, &main->status, 0);
		if (WIFEXITED(main->status))
			main->status = WEXITSTATUS(main->status);
		else if (WIFSIGNALED(main->status))
			main->status = WTERMSIG(main->status) + 128;
	}
}
