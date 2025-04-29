/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_binaries.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:11:52 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 17:12:09 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_invalid_redir(t_cmd *cmd)
{
	return (cmd->read_from == -1 || cmd->write_to == -1);
}

void	handle_fork_error(t_cmd *cmd)
{
	printf("Erro no fork\n");
	free(cmd->tkns);
}

void	ft_free_split(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
}
