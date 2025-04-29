/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeagost <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:47:15 by joeagost          #+#    #+#             */
/*   Updated: 2025/02/03 16:47:20 by joeagost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_valid_envinit(char chr)
{
	return (chr == '?' || chr == '_' || ft_isalpha(chr));
}

char	*get_envval(t_main *main, int env_init, int *env_len)
{
	int		i;
	char	*envname;
	char	*envval;
	char	*tmp;

	tmp = main->inpt + env_init + 1;
	while (is_valid_envinit(tmp[*env_len]) || ft_isdigit(tmp[*env_len]))
		(*env_len)++;
	if (tmp[0] == '?')
		*env_len = 1;
	envname = malloc(sizeof(char) * (*env_len + 1));
	if (!envname)
		return (NULL);
	i = -1;
	while (*env_len > ++i)
		envname[i] = tmp[i];
	envname[*env_len] = '\0';
	if (envname[0] == '?')
		envval = ft_itoa(main->status);
	else
		envval = getenv(envname);
	free(envname);
	return (envval);
}

void	replace_env(t_main *main, int env_init, int *env_len)
{
	char	*envval;
	int		i;
	int		inpt_len;
	int		envval_len;
	int		j;
	char	*xpandd_inpt;

	envval = get_envval(main, env_init, env_len);
	//printf("replaceInit:%s\n", envval);
	// if (!envval)
	// 	return (NULL);
	inpt_len = ft_strlen(main->inpt);
	envval_len = ft_strlen(envval);
	//printf("envalLen:%d\n", envval_len);
	xpandd_inpt = malloc(inpt_len - *env_len + envval_len + 1);
	i = -1;
	while (++i < env_init)
		xpandd_inpt[i] = main->inpt[i];
	j = 0;
	while (j < envval_len)
		xpandd_inpt[i++] = envval[j++];
	j = env_init + *env_len + 1;
	//printf("j:%d\n", j);
	while (j <= inpt_len)
		xpandd_inpt[i++] = main->inpt[j++];
	//free(main->inpt);
	*env_len = envval_len;
	//printf("replaced: %s\n", xpandd_inpt);
	//return (xpandd_inpt);
	main->inpt = xpandd_inpt;
}

void	env_expand(t_main *main)
{
	int	i;
	int	env_len;
	int	quote;

	i = 0;
	env_len = 0;
	quote = 0;
	while (main->inpt[i])
	{
		if ((main->inpt[i] == '\'' && quote == 1)
			|| (main->inpt[i] == '"' && quote == 2))
			quote = 0;
		else if (main->inpt[i] == '\'' && quote == 0)
			quote = 1;
		else if (main->inpt[i] == '"' && quote == 0)
			quote = 2;
		if (main->inpt[i] == '$' && (is_valid_envinit(main->inpt[i + 1])
			|| (isquote(main->inpt[i + 1]) && quote == 0)) && quote != 1)
		{
			replace_env(main, i, &env_len);
			if (!main->inpt)
				return ;
			i += env_len - 1;
			env_len = 0;
			//printf("expanded:%s\n", inpt);
		}
		i++;
	}
	//return (main->inpt);
}
