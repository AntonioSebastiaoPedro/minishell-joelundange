#include "main.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

size_t	my_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	len;
	int		quote;

	i = 0;
	quote = 0;
	len = 0;
	while ((src[i] != '\0') && (i < size))
	{
		if ((src[i] == '\'' && quote == 1)
			|| (src[i] == '"' && quote == 2))
			quote = 0;
		else if (src[i] == '\'' && quote == 0)
			quote = 1;
		else if (src[i] == '"' && quote == 0)
			quote = 2;
		if ((src[i] == '\'' && quote == 2) || (src[i] == '"' && quote == 1)
			|| !isquote(src[i]))
			dest[len++] = src[i];
		i++;
	}
	if (size != 0)
		dest[len] = '\0';
	return (len);
}

void print_cmds(t_main main_st)
{
    int i;
    int j;

    i = 0;
    printf("Quantidade de comandos: %d\n", main_st.qtd_cmds);
    while (i < main_st.qtd_cmds)
    {
            j = 0;
            while (main_st.cmds[i].tkns[j] != NULL)
                printf("%s ", main_st.cmds[i].tkns[j++]);
            printf("\n");            
            i++;
    }
    printf("---------------------------\n");
}

void    set_main_st(t_main *main_st)
{
    main_st->qtd_cmds = ft_count_cmd(main_st, main_st->tkns) + 1;
    //main_st->cmds = 
	ft_create_cmds(main_st, -1);
    //main_st->status = -1; 
	main_st->stdin_dup = dup(STDIN_FILENO);
    main_st->stdout_dup = dup(STDOUT_FILENO);
    //main_st->has_pipe = 0;
}

int	cmds_validator(t_tkn *tkns)
{
	int	i;

	i = 0;
	while (tkns[i].str)
	{
		if (!tkns[i].quoted && (tkns[0].str[0] == '|'
			|| (i && tkns[i - 1].str[0] == '|' && tkns[i].str[0] == '|')
			|| (tkns[i].str[0] == '|' && !tkns[i].nxt)))
		{
			printf("minishell: erro de sintaxe próximo ao token inesperado `|'\n");
			break ;
		}
		else if (!tkns[i].quoted && isctrlop(tkns[i].str[0])
			&& tkns[i].str[0] != '|' && !tkns[i].nxt)
		{
			printf("minishell: erro de sintaxe próximo ao token inesperado `newline'\n");
			break ;
		}
		else if (!tkns[i].quoted && isctrlop(tkns[i].str[0])
			&& tkns[i].nxt && isctrlop(tkns[i].nxt->str[0]))
		{
			printf("minishell: erro de sintaxe próximo ao token inesperado `%s'\n",
				tkns[i].nxt->str);
			break ;
		}
		i++;
	}
	if (tkns[i].str)
		return (0);
	else
		return (1);
}

t_tkn	*get_nxtkn(char *inpt, int *i)
{
	char	*tkn_init;
	char	*tkn_end;
	t_tkn	*tkn;

	tkn_init = NULL;
	tkn_end = NULL;
	tkn = NULL;
	while (ft_isspace(inpt[*i]))
		(*i)++;
	if (inpt[*i])
		tkn_init = inpt + *i;;
	if (!isctrlop(inpt[*i]))
		while (inpt[*i] && !ft_isspace(inpt[*i]) && !isctrlop(inpt[*i]))
		{
			if (isquote(inpt[*i]))
				*i = ft_strchr(inpt + *i + 1, inpt[*i]) - inpt;
			(*i)++;
		}
	else
		if (isctrlop(inpt[++(*i)]) && inpt[*i] == inpt[*i - 1]
			&& inpt[*i] != '|')
			(*i)++;
	if (tkn_init)
		tkn_end = inpt + *i;
	if (!tkn_init && !tkn_end)
		return (tkn);
	tkn = malloc(sizeof(t_tkn));
	tkn->str = malloc(sizeof(char) * (tkn_end - tkn_init + 1));
	my_strlcpy(tkn->str, tkn_init, tkn_end - tkn_init);
	tkn->quoted = isquote(*tkn_init);
	return (tkn);
}

int	cont_tkn(char *inpt)
{
	int		i;
	int		qtd_tkns;
	t_tkn	*tkn;

	i = 0;
	qtd_tkns = 0;
	while (inpt[i])
	{
		//printf("INP:%s | ",inpt);
		tkn = get_nxtkn(inpt, &i);
		//printf("i:%d | Tk:%s\n",i,tkn->str);
		if (tkn)
		{
			qtd_tkns++;
			//printf("tok:%s\n", tkn);
			free(tkn->str);
			free(tkn);
		}
		//write(2, "ErorMsg3\n", 9);
		//exit (-1);
	}
	//write(2, "ErorMsg4\n", 9);
	return (qtd_tkns);
}

void	add_tkn(t_tkn *tkns, t_tkn *tkn)
{
	int		i;
	//char	*aux;

	if (!tkns || !tkn || !tkn->str)
		return ;
	i = 0;
	//printf("ADD:%s\n", tkns[i].str);
	while (tkns[i].str)
		i++;
	/*if (isquote(tkn->str[0]))
	{
		tkns[i].quoted = 1;
		aux = tkn->str;
		tkn->str = malloc(ft_strlen(aux) - 1);
		ft_strlcpy(tkn->str, aux + 1, ft_strlen(aux) - 2);
		free(aux);
	}*/
	if (i)
		tkns[i - 1].nxt = tkns + i;
	tkns[i].str = tkn->str;
	tkns[i].quoted = tkn->quoted;
	tkns[i].nxt = NULL;
	free(tkn);
}

t_tkn	*tokenizer(t_main *main_st)
{
	int		i;
	t_tkn	*tkns;
	t_tkn	*tkn;

	if (main_st->inpt == NULL)
		return (NULL);
	//printf("NTokens:%d\n", cont_tkn(inpt));
	tkns = ft_calloc(sizeof(t_tkn), cont_tkn(main_st->inpt) + 1);
	if (!tkns)
		return (NULL);
	i = 0;
	while (main_st->inpt[i])
	{
		tkn = get_nxtkn(main_st->inpt, &i);
		//write(2, "ErorMsg5\n", 9);
		if (tkn)
			add_tkn(tkns, tkn);
	}
	//write(2, "ErorMsg6\n", 9);
	if (cmds_validator(tkns))
		return (tkns);
	else
	{
		main_st->status = 2;
		return (NULL);
	}
}

/*void	free_all(t_main *main_st)
{
	t_tkn *tok;
	t_tkn *nxt_tok;

	tok = main_st->tkns;
	if (tok == NULL)
	{
		//write(2, "ola1\n", 5);
		return;  // No tokens to free, return early
	}

	while (tok != NULL)  // Traverse the list until NULL
	{
		nxt_tok = tok->nxt;  // Save the next token before freeing the current one
		if (tok->str != NULL)
		{
			free(tok->str);  // Free the string associated with this token
		}
		tok = nxt_tok;
		free(tok); // Move to the next token
	}//main_st->has_pipe = 0;
}*/

void    free_all(t_main *main_st)
{
    int i;
	
	i = 0;
    if (main_st->tkns == NULL)
        return;
    while (main_st->tkns[i].str != NULL)
    {
        free(main_st->tkns[i].str);
		main_st->tkns[i].str= NULL;
        i++;
    }
    free(main_st->tkns);
}

int ft_strcmp(const char *s1, const char *s2)
{
    // Enquanto os caracteres de s1 e s2 forem iguais e não for o final da string
	if (s1 == NULL || s2 == NULL)
	{
		return (-1);
	}
	
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    
    // Retorna a diferença entre os caracteres onde a comparação falhou (se houver)
    // Se ambos chegarem ao final ('\0'), a diferença será 0
    return (unsigned char)*s1 - (unsigned char)*s2;
}

void    print_tkn(t_tkn *tkns)
{
    int i;

    if (!tkns)
        return ;
    i = 0;
    while (tkns[i].str)
    {
        printf("Token:%s -> Type:%d\n", tkns[i].str, tkns[i].quoted);
        i++;
    }
}

bool has_unclosedquotes(char *str)
{
    int     i;
    char    *aux;

    i = 0;
    aux = NULL;
    while (str[i] != '\0')
    {
        if (isquote(str[i]))
        {
            aux = ft_strchr(str + i + 1, str[i]);
            if (aux)
                i = aux - str;
            else
                return (false);
        }
        //printf("%d\n", i);
        i++;
    }
    return (true);
}

void ft_add_history(char *inpt)
{
	if (inpt != NULL && inpt[0] != '\0')
		add_history(inpt);
}

int main()
{
    //char    *inpt;
    t_main  main_st;
	char	*inpt_trimed;

    main_st.status = 0;
	while (1)
    {
		main_st.has_pipe = 0;
		if (signal(SIGINT, ft_sigint_handle) == SIG_ERR)
		{
			printf("Erro ao configurar manipulador de sinal");
			main_st.status = -1;
		}
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		{
			printf("Erro ao configurar manipulador de sinal");
			main_st.status = -1;
		}
		printf("STATUS:%d\n",main_st.status);
        main_st.inpt = readline("Mini$hell> ");
        ft_add_history(main_st.inpt);
		inpt_trimed = ft_strtrim(main_st.inpt, " \n\t");
		free(main_st.inpt);
		//main_st.inpt = NULL;
		main_st.inpt = inpt_trimed;
		if (main_st.inpt == NULL)
       	{
            printf("exit\n");
            break ;
        }
        /*else if (*inpt == '\0')
        {
            //free(inpt);
            continue ;
        }*/
        else if(!has_unclosedquotes(main_st.inpt))
        {
            //free(inpt);
            printf("Error: Quotes nao fechadas\n");
			main_st.status = 2;
            //continue ;
        }
        /*if (check_multiple_sequence(inpt))
        {
            free(inpt);
            printf("Error: Muitos redirecionamentos consecutivos\n");
            continue;
        }*/
        //printf("inpt:%s\n", inpt);
        else if (main_st.inpt[0] != '\0')
        {
			env_expand(&main_st);
			/*if (!main_st.inpt)
			{
				free(main_st.inpt);
				continue ;
			}*/
            //printf("EXPANDED:%s\n", main_st.inpt);
			if (main_st.inpt[0] == '\0')
				continue ;
			main_st.tkns = tokenizer(&main_st);
			//print_tkn(main_st.tkns);
			if (main_st.tkns == NULL)
				continue ;
			set_main_st(&main_st);
			//print_cmds(main_st);
			start_execution(&main_st);
			free_all(&main_st);
			//print_cmds(main_st);
			//return 1;
		}
			if (main_st.inpt != NULL)
				free(main_st.inpt);
    }
    return (0);
}
