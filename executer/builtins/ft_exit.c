#include "../../minishell.h"
//handling overflow
//whene i will exit
//check unsigned long
int ft_exit(t_command *command)
{
   int status=0;
   int one_arg=1;
   unsigned char test;

    printf("exit\n");
    if((command->args && is_num(command->args[1])==-1 ) || ft_atoi(command->args[1])==-1 || ft_atoi(command->args[1])==0)
        status=print_cmd_error(command->cmd,command->args[1],"numeric argument required", 255);
    if (command->args && command->args[2] && !status)
    {
        one_arg=0;
        status=print_cmd_error(command->cmd,NULL,"too many arguments", 1);
    }
    if(command->args && is_num(command->args[1]) && one_arg)
    {
        test=(unsigned char)ft_atoi(command->args[1]);
       // printf("%d\n",test);
        //const char *cast=(const char *)test;
       status=test;

    }
   
    return status;
}