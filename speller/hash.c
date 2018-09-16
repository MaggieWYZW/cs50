#include "hash.h"
#include "dictionary.h"

unsigned long hash_djb2(char *str)
{
    unsigned long hash = 5381;
    int c;

    while((c = *str++))
    {
        hash = (hash << 5) + hash + c;
    }
    return hash % HASHSIZE;
}


// static unsigned long hash_sdbm(char *str)
// {
//     unsigned long hash = 0;
//     int c;

//     while( c = *str++)
//     {
//         hash = c + (hash << 6) + (hash  << 16) - hash;
//     }
//     return hash;
// }