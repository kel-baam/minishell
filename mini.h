#ifndef MINI_H
#define MINI_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>
# include <fcntl.h>
#include <string.h>
typedef struct t_list
{
    void *content;
    struct t_list *next;

}   t_list;
typedef struct t_data
{
    //char    **cmds;
    char *cmd;
    char    *envs;
    char    **paths;
    char **args;
    int redi;
    char *outfile;  
   // t_list  *commands;

}t_data;
t_data* read_cmds(t_data *data,char **av ,int ac);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
t_list	*ft_lstlast(t_list *lst);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
char	*ft_strchr(const char *s, int c);
void	print_cmd_error(char *cmd, char *msg_err, int status_code,int output_fd);
#endif