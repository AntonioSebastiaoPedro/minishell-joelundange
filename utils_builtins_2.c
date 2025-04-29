/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:53:35 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 09:47:07 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_is_builtin(char *cmd)
{
	int		i;
	char	*builtins[7];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd, builtins[i++]) == 0)
			return (true);
	}
	return (false);
}

int	ft_execute_builtins(t_cmd cmd)
{
	int	retorno;

	retorno = 0;
	if (ft_strcmp(cmd.tkns[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd.tkns[0], "cd") == 0)
		retorno = ft_cd(cmd.tkns);
	else if (ft_strcmp(cmd.tkns[0], "pwd") == 0)
		retorno = ft_pwd();
	else if (ft_strcmp(cmd.tkns[0], "export") == 0)
		retorno = ft_export(cmd);
	else if (ft_strcmp(cmd.tkns[0], "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd.tkns[0], "env") == 0)
		ft_env(cmd.tkns);
	else if (ft_strcmp(cmd.tkns[0], "exit") == 0)
		retorno = ft_exit(cmd);
	return (retorno);
}

char	is_validexit(char *strnbr)
{
	int	i;

	i = 0;
	if (*strnbr == '+' || *strnbr == '-')
		strnbr++;
	while (ft_isdigit(strnbr[i]))
		i++;
	return ((strnbr[i] == '\0') && (i > 0));
}

int	ft_exit(t_cmd cmd)
{
	if (cmd.qtd_tkns == 1)
	{
		printf("%s\n", cmd.tkns[0]);
		exit(0);
	}
	else
	{
		if (!is_validexit(cmd.tkns[1]))
		{
			printf("exit\nminishell: %s: %s: numeric argument required\n",
				cmd.tkns[0], cmd.tkns[1]);
			exit(2);
		}
		if (cmd.qtd_tkns > 2)
		{
			printf("%s\nminishell: %s: too many arguments\n",
				cmd.tkns[0], cmd.tkns[0]);
			return (1);
		}
		printf("%s\n", cmd.tkns[0]);
		exit(ft_atoi(cmd.tkns[1]));
	}
}
