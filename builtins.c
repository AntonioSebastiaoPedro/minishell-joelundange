/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 01:36:07 by llundage          #+#    #+#             */
/*   Updated: 2025/04/24 02:37:44 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_echo(t_cmd cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd.write_to == -42)
		cmd.write_to = 1;
	i = get_last_option_n(cmd);
	if (i > 1)
		newline = 0;
	while (cmd.tkns[i])
	{
		write(cmd.write_to, cmd.tkns[i], ft_strlen(cmd.tkns[i]));
		if (cmd.tkns[i + 1])
			write(cmd.write_to, " ", 1);
		i++;
	}
	if (newline)
		write(cmd.write_to, "\n", 1);
}

int	ft_cd(char **args)
{
	int	matrix_len;

	matrix_len = get_matrix_lines(args);
	if (matrix_len == 1)
	{
		printf("cd: need a relative or absolute path\n");
		return (1);
	}
	else if (matrix_len > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			printf("minishell: cd: %s: %s\n", args[1], strerror(errno));
			return (1);
		}
	}
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		printf("Error:> pwd");
		return (1);
	}
	return (0);
}

void	ft_unset(t_cmd cmd)
{
	extern char	**environ;
	int			i;
	int			j;
	int			env_size;
	int			posi;

	i = 1;
	while (cmd.tkns[i])
	{
		posi = ft_get_envname_posi(cmd.tkns[i], environ);
		if (posi != -1)
		{
			env_size = get_matrix_lines(environ);
			j = 0;
			while (j < env_size)
			{
				environ[posi + j] = environ[posi + j + 1];
				j++;
			}
			environ[env_size] = NULL;
		}
		i++;
	}
}

void	ft_env(char **args)
{
	extern char	**environ;
	int			i;

	i = 0;
	if (!args[1])
	{
		while (environ[i] != NULL)
		{
			if (ft_strchr(environ[i], '='))
				printf("%s\n", environ[i++]);
		}
	}
	else
		printf("env: '%s': No such file or directory\n", args[1]);
}
