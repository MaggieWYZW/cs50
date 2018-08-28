#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int s = get_int("enter string!\n");
    switch(s)
    {
        case 'a': printf("a\n"); break;
        case 'b': printf("b\n"); break;
    }
}