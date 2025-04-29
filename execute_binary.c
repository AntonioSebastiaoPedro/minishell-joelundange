/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:26:21 by llundage          #+#    #+#             */
/*   Updated: 2025/04/24 21:37:48 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_relative_path(t_cmd *cmd)
{
	extern char	**environ;

	if (execve(cmd->tkns[0], cmd->tkns, environ) == -1)
	{
		printf("minishell: %s: %s\n", cmd->tkns[0], strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	ft_absolute_path(t_cmd *cmd)
{
	extern char	**environ;

	if (execve(cmd->tkns[0], cmd->tkns, environ) == -1)
	{
		printf("minishell: %s: %s\n", cmd->tkns[0], strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int	report_error(t_main *main_st, t_cmd *cmd, char **paths)
{
	if (!paths)
	{
		fprintf(stderr, "minishell$: %s: No such file or directory\n",
			cmd->tkns[0]);
		main_st->status = 127;
		return (1);
	}
	return (0);
}
