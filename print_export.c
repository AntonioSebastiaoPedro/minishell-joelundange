/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:32:56 by llundage          #+#    #+#             */
/*   Updated: 2025/04/25 09:34:53 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_and_print_line(char *str)
{
	print_line(str);
	free(str);
}

void	sort_matrix(char **dest)
{
	int		j;
	int		swap;
	int		n;
	char	*temp;

	n = get_matrix_lines(dest);
	while (1)
	{
		swap = 0;
		j = 0;
		while (j < n - 1)
		{
			if (strcmp(dest[j], dest[j + 1]) > 0)
			{
				temp = dest[j];
				dest[j] = dest[j + 1];
				dest[j + 1] = temp;
				swap = 1;
			}
			j++;
		}
		n--;
		if (!swap)
			break ;
	}
}

char	**ft_copy_matrix(char **src, int qtd)
{
	char	**dest;
	int		i;

	dest = malloc((qtd + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < qtd)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			while (i--)
				free(dest[i]);
			free(dest);
			return (NULL);
		}
		i++;
	}
	dest[qtd] = NULL;
	return (dest);
}

void	print_line(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 1;
	printf("declare -x ");
	while (str[i])
	{
		printf("%c", str[i]);
		if (str[i] == '=' && flag && ft_strchr(str, '='))
			printf("\"");
		if (!str[i + 1] && !flag && ft_strchr(str, '='))
			printf("\"");
		if (str[i] == '=')
			flag = 0;
		i++;
	}
	printf("\n");
}

void	ft_print_export(void)
{
	int			i;
	extern char	**environ;
	char		**tmp;

	tmp = ft_copy_matrix(environ, get_matrix_lines(environ));
	if (!tmp)
		return ;
	sort_matrix(tmp);
	i = 0;
	while (tmp[i])
		free_and_print_line(tmp[i++]);
	free(tmp);
}
