/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bultins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:20:38 by llundage          #+#    #+#             */
/*   Updated: 2025/04/23 21:42:59 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_matrix_lines(char **src)
{
	int	qtd;

	qtd = 0;
	while (src[qtd] != NULL)
		qtd++;
	return (qtd);
}

int	get_last_option_n(t_cmd cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd.tkns[i])
	{
		if (cmd.tkns[i][0] == '-')
		{
			j = 1;
			while (cmd.tkns[i][j] == 'n')
				j++;
			if (cmd.tkns[i][j] != '\0')
				break ;
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	ft_get_envname_posi(char *name, char **environ)
{
	int		i;
	char	*current_name;

	i = 0;
	while (environ[i])
	{
		current_name = ft_get_env_name(environ[i]);
		if (current_name && ft_strcmp(current_name, name) == 0)
		{
			free(current_name);
			return (i);
		}
		free(current_name);
		i++;
	}
	return (-1);
}

int	is_valid_envname(char *str)
{
	char	*name;
	int		i;

	if (!str)
		return (0);
	name = NULL;
	if (str)
	{
		name = ft_get_env_name(str);
		i = 1;
		while (name[i])
		{
			if (!ft_isalnum(name[i]))
			{
				free(name);
				return (0);
			}
			i++;
		}
		free(name);
		return (1);
	}
	free(name);
	return (0);
}

char	*ft_get_env_name(char *key_value)
{
	char	*realname;
	int		len;

	len = 0;
	if (!key_value)
		return (NULL);
	while (key_value[len] != '=' && key_value[len] != '\0')
		len++;
	if (key_value[len] == '\0')
		realname = ft_strdup(key_value);
	else
		realname = ft_substr(key_value, 0, len);
	return (realname);
}
