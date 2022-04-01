#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char* my_env_var = getenv("MY_ENV_VAR");

    if(my_env_var)
        printf("Var found: %s", my_env_var );
    else
        printf("Var not found.");                

    return 0;
}
