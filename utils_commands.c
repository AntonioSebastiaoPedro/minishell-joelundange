/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 02:53:53 by llundage          #+#    #+#             */
/*   Updated: 2025/04/24 03:12:05 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_count_tkns(t_tkn *tokens)
{
	int			qtd_tkns;
	t_tkn	*aux;

	qtd_tkns = 0;
	aux = tokens;
	while (aux != NULL)
	{
		if (isctrlop(aux->str[0]) && aux->quoted == 0)
			break ;
		qtd_tkns++;
		aux = aux->nxt;
	}
	return (qtd_tkns);
}

int	ft_count_cmd(t_main *main, t_tkn *tokens)
{
	t_tkn	*aux;
	int			qtd_cmds;

	(void)main;
	aux = tokens;
	qtd_cmds = 0;
	while (aux != NULL)
	{
		if (aux->str && aux->str[0] == '|' && aux->quoted == 0)
			qtd_cmds++;
		aux = aux->nxt;
	}
	return (qtd_cmds);
}

int	isctrlop(char c)
{
	if (c == '<' || c == '|' || c == '>')
		return (1);
	return (0);
}

void	ft_create_pipe(t_cmd *cmds, int pipes, int *status)
{
	int	i;

	i = 0;
	while (i < pipes)
	{
		if (pipe(cmds[i].pipe_fd) == -1)
		{
			printf("Error: funcao pipe");
			*status = 1;
			exit(1);
		}
		//printf("cmd[%d]->read=%d|wite=%d\n", i,
		//	cmds[i].pipe_fd[0], cmds[i].pipe_fd[1]);
		i++;
	}
}

void	ft_set_cmds(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->qtd_cmds)
	{
		main->cmds[i].qtd_tkns = 0;
		main->cmds[i].tkns = NULL;
		main->cmds[i].read_from = -42;
		main->cmds[i].write_to = -42;
		main->cmds[i].pipe_fd[0] = -1;
		main->cmds[i].pipe_fd[1] = -1;
		main->cmds[i].exit_status = 0;
		i++;
	}
}
