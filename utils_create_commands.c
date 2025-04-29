/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_create_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:48:15 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 10:48:42 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_cmd_args(t_main *main, int i)
{
	while (i >= 0)
		free(main->cmds[i--].tkns);
	free(main->cmds);
}

t_tkn	*skip_pipe_tkns(t_tkn *tmp)
{
	if (tmp && tmp->str[0] == '|' && tmp->quoted == 0)
		tmp = tmp->nxt;
	return (tmp);
}

int	set_cmd_tkns(t_tkn *tmp, t_main *main, int i)
{
	main->cmds[i].qtd_tkns = ft_count_tkns(tmp);
	main->cmds[i].tkns = set_tkns(tmp, &main->cmds[i], main, 0);
	/*if (main->cmds[i].tkns == NULL)
	{
		free_cmd_args(main, i);
		return (0);
	}*/
	main->cmds[i].nxt = NULL;
	if (i > 0)
		main->cmds[i - 1].nxt = &main->cmds[i];
	return (1);
}
