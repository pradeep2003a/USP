#include<stdio.h>
#include<unistd.h>
#include<limits.h>
//#define _POSIX_SOURCE
//#define _POSIX_C_SOURCE 199309L
int main()
{
printf("Runtime values\n");
printf("The max number of clock ticks : %ld\n",sysconf(_SC_CLK_TCK));
printf("The max runtime child processes : %ld\n",sysconf(_SC_CHILD_MAX));
printf("The max runtime path length :%ld\n",pathconf("usp1.cpp",_PC_PATH_MAX));
printf("The max characters in a file name :%ld\n",pathconf("usp1.cpp",_PC_NAME_MAX));
printf("The max number of opened files : %ld\n",sysconf(_SC_OPEN_MAX));
return 0;
}
