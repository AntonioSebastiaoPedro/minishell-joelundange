#ifndef MAIN_H
#define MAIN_H

extern int g_signal;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>

typedef struct s_token
{
    char *str;
    int quoted;
    struct s_token *nxt;
} t_tkn;

typedef struct s_command
{
    int qtd_tkns;
    char **tkns;
    int read_from;
    int write_to;
    int pipe_fd[2];
    struct s_command *nxt;
    int exit_status;
    int pid;
    //t_builtin builtins;
} t_cmd;

typedef struct s_main
{
    char *inpt;
    char **enviro;
    t_tkn *tkns;
    t_cmd *cmds;
    int qtd_cmds;
    int status;
    int stdin_dup;
    int stdout_dup;
    int pipefd[2];
    int has_pipe;
} t_main;

void    ft_sigint_handle(int sig);
void    ft_sigquit_handle(int sig);
void    ft_sigint_on_child(int sig);
void print_cmds(t_main main_st );
void start_execution(t_main *main_st );
t_cmd   *ft_create_cmds(t_main *main_st , int i);
bool    ft_is_builtin(char *cmd);
void    ft_relative_path(t_cmd *cmd);
void    ft_absolute_path(t_cmd *cmd);
void	handle_signals_in_child(void);
void	execute_cmd(t_main *main_st , t_cmd *cmd);
void	apply_redirections(t_cmd *cmd);
char	**get_cmd_paths(void);
char	*build_full_path(const char *dir, const char *cmd);
int	try_exec_path(const char *full_path, t_cmd *cmd);
void	wait_for_child(t_main *main_st , pid_t pid);
void	ft_free_split_and_status(t_main *main_st , char	**paths, int status);
void    ft_path(t_main *main_st , t_cmd *cmd, int i);
void    ft_execute_binary(t_main *main_st , t_cmd *cmd);
void	ft_execute(t_main *main_st , t_cmd *cmd);
void	start_execution(t_main *main_st );
void	ft_free_split(char **matrix);

int	set_to_redir(t_tkn *tkns, t_cmd *cmd, int *status);
char	**set_tkns(t_tkn *tkns, t_cmd *cmd, t_main *main_st , int i);
int	is_valid_export(char *str);
int	invalid_identifier_error(char *cmd, char *str);
int	ft_setenv(char *key_value, char *equal, int overwrite, int i);
void	handle_export(char *str);
int	ft_export(t_cmd cmd);

void	handle_heredoc(int pipefd[2], t_cmd *cmd,
char *delimiter, int *status);
void	heredoc_child(int write_fd, char *delimiter);

void	free_and_print_line(char *str);
void	sort_matrix(char **dest);
char	**ft_copy_matrix(char **src, int qtd);
void	print_line(char *str);
void	ft_print_export(void);
void check_error(int nbr);

int	is_out_redir(t_tkn *tkn);
int	is_append_redir(t_tkn *tkn);
int	is_in_redir(t_tkn *tkn);
int	is_heredoc(t_tkn *tkn);
int	check_redir_errors(t_cmd *cmd, int *status);

char	is_validexit(char *strnbr);
int	ft_count_tkns(t_tkn *tkns);
int	ft_count_cmd(t_main *main_st , t_tkn *tkns);
void	ft_create_pipe(t_cmd *cmds, int pipes, int *status);
void	ft_set_cmds(t_main *main_st );


void	ft_sigint_handle(int sig);
void	ft_sigint_on_child(int sig);
void	ft_sigquit_handle(int sig);
void	ft_sigint_on_heredoc_child(int sig);

int	get_matrix_lines(char **src);
int	get_last_option_n(t_cmd cmd);
int	ft_get_envname_posi(char *name, char **environ);
int	is_valid_envname(char *str);
char	*ft_get_env_name(char *key_value);
void	free_cmd_args(t_main *main_st , int i);
t_tkn	*skip_pipe_tkns(t_tkn *tmp);
int	set_cmd_tkns(t_tkn *tmp, t_main *main_st , int i);


int    ft_execute_builtins(t_cmd cmd);
int	report_error(t_main *main_st , t_cmd *cmd, char **paths);
int	isctrlop(char c);
void	handle_fork_error(t_cmd *cmd);
int	is_invalid_redir(t_cmd *cmd);
int ft_count_cmd(t_main *main_st , t_tkn *tkns);
void ft_echo(t_cmd cmd);
int ft_cd(char **args);
int ft_pwd(void);
int ft_export(t_cmd cmd);
void ft_unset(t_cmd cmd);
void ft_env(char **args) ;
int ft_exit(t_cmd cmd);
int ft_strcmp(const char *s1, const char *s2);
void	free_all(t_main *main_st );
void	env_expand(t_main *main_st );
int	isquote(char c);

#endif
