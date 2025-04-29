/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_to_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:40:10 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 17:10:00 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**get_cmd_paths(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	return (ft_split(path_env, ':'));
}

char	*build_full_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

int	try_exec_path(const char *full_path, t_cmd *cmd)
{
	extern char	**environ;

	if (access(full_path, X_OK) == 0)
	{
		execve(full_path, cmd->tkns, environ);
		fprintf(stderr, "minishell: %s: %s\n", cmd->tkns[0], strerror(errno));
		return (-1);
	}
	return (0);
}

void	ft_free_split_and_status(t_main *main_st, char	**paths, int status)
{
	ft_free_split(paths);
	main_st->status = status;
}

void	ft_path(t_main *main_st, t_cmd *cmd, int i)
{
	char	**paths;
	char	*full_path;

	paths = get_cmd_paths();
	if (report_error(main_st, cmd, paths))
		return ;
	while (paths[++i])
	{
		full_path = build_full_path(paths[i], cmd->tkns[0]);
		if (!full_path)
		{
			fprintf(stderr, "minishell: memory allocation error\n");
			ft_free_split_and_status(main_st, paths, 1);
			return ;
		}
		if (try_exec_path(full_path, cmd) == -1)
		{
			free(full_path);
			ft_free_split_and_status(main_st, paths, 126);
			return ;
		}
		free(full_path);
	}
	fprintf(stderr, "minishell: %s: command not found\n", cmd->tkns[0]);
	ft_free_split_and_status(main_st, paths, 127);
}
