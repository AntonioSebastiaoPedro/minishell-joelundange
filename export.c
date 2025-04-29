/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:40:38 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 09:43:51 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_valid_export(char *str)
{
	return ((str[0] == '_' || ft_isalpha(str[0])) && is_valid_envname(str));
}

int	invalid_identifier_error(char *cmd, char *str)
{
	printf("%s: %s: not a valid identifier\n", cmd, str);
	return (1);
}

int	ft_setenv(char *key_value, char *equal, int overwrite, int i)
{
	extern char		**environ;
	static char		*new_environ[10000];
	char			*name;
	int				len;

	name = ft_get_env_name(key_value);
	if (!key_value)
		return (-1);
	len = get_matrix_lines(environ);
	while (environ[i] && ft_strcmp(ft_get_env_name(environ[i]), name) != 0)
		i++;
	if (environ[i] == NULL || equal == NULL)
	{
		i = -1;
		while (++i < len)
			new_environ[i] = environ[i];
		new_environ[len] = key_value;
		new_environ[len + 1] = NULL;
		environ = new_environ;
	}
	else if (environ[i] != NULL && overwrite)
		environ[i] = key_value;
	free(name);
	return (0);
}

void	handle_export(char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		ft_setenv(str, str + ft_strlen(str), 1, 0);
	else
		ft_setenv(str, equal, 1, 0);
}

int	ft_export(t_cmd cmd)
{
	int	i;

	if (!cmd.tkns[1])
	{
		ft_print_export();
		return (0);
	}
	i = 0;
	while (cmd.tkns[++i])
	{
		if (is_valid_export(cmd.tkns[i]))
			handle_export(cmd.tkns[i]);
		else
			return (invalid_identifier_error(cmd.tkns[0], cmd.tkns[i]));
	}
	return (0);
}
