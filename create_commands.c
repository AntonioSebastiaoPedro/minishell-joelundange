/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:24:32 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 09:46:05 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_to_redir(t_tkn *tkns, t_cmd *cmd, int *status)
{
	int		pipehere[2];
	char	*delimiter;

	if (!tkns || !tkns->str || tkns->quoted != 0)
		return (0);
	if (is_out_redir(tkns))
		cmd->write_to = open(tkns->nxt->str,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (is_append_redir(tkns))
		cmd->write_to = open(tkns->nxt->str,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (is_in_redir(tkns))
		cmd->read_from = open(tkns->nxt->str, O_RDONLY, 0644);
	else if (is_heredoc(tkns))
	{
		delimiter = tkns->nxt->str;
		handle_heredoc(pipehere, cmd, delimiter, status);
	}
	return (check_redir_errors(cmd, status));
}

char	**set_tkns(t_tkn *tkns, t_cmd *cmd, t_main *main, int i)
{
	//char		**tkns;
	t_tkn	*aux;

	/*if (cmd->qtd_tkns == 0)
		cmd->tkns = NULL;
	else*/
	cmd->tkns = (char **)malloc(sizeof(char *) * (cmd->qtd_tkns + 1));
	//if (!cmd->tkns)
	//	return (NULL);
	aux = tkns;
	while (aux != NULL && aux->str != NULL
		&& !(aux->str[0] == '|' && aux->quoted == 0))
	{
		if (!aux->quoted && isctrlop(aux->str[0]) && aux->str[0] != '|')
		{
			if (set_to_redir(aux, cmd, &main->status))
				return (free(cmd->tkns), NULL);
			aux = aux->nxt;
		}
		else
			cmd->tkns[i++] = aux->str;
		aux = aux->nxt;
	}
	cmd->tkns[i] = NULL;
	return (cmd->tkns);
}

t_cmd	*ft_create_cmds(t_main *main, int i)
{
	t_tkn	*tmp;

	tmp = main->tkns;
	main->cmds = (t_cmd *)malloc(sizeof(t_cmd) * main->qtd_cmds);
	if (!main->cmds)
		return (NULL);
	ft_set_cmds(main);
	//if (main->qtd_cmds > 1)
	//	ft_create_pipe(main->cmds, (main->qtd_cmds - 1), &main->status);
	while (++i < main->qtd_cmds)
	{
		set_cmd_tkns(tmp, main, i);
		tmp = skip_pipe_tkns(tmp);
	}
	return (main->cmds);
}
