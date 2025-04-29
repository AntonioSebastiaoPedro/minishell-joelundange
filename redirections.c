/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:42:00 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 09:43:04 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_out_redir(t_tkn *token)
{
	return (ft_strcmp(token->str, ">") == 0);
}

int	is_append_redir(t_tkn *token)
{
	return (ft_strcmp(token->str, ">>") == 0);
}

int	is_in_redir(t_tkn *token)
{
	return (ft_strcmp(token->str, "<") == 0);
}

int	is_heredoc(t_tkn *token)
{
	return (ft_strcmp(token->str, "<<") == 0);
}

int	check_redir_errors(t_cmd *cmd, int *status)
{
	if (cmd->write_to == -1 || cmd->read_from == -1)
	{
		printf("minishell: %s: %s\n", cmd->tkns[1], strerror(errno));
		*status = 1;
		cmd->exit_status = 1;
		return (-1);
	}
	return (0);
}
