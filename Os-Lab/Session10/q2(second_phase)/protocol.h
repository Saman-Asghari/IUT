#ifndef PROTOCOL_H
#define PROTOCOL_H

#define NAME "/shmem-oslab"

#define NUM 7

#define NAME_LEN 50

struct player
{
    char player_name[NAME_LEN];
    int score;
};

#define ARRAY_S (NUM * sizeof(struct player));

#endif
