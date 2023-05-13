#include "../minishell.h"
void initilizer(char**envs)
{
    bzero(&g_data, sizeof(t_data));
    init_envs(envs);
    //ft_env();

}