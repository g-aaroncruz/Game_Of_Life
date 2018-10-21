#include <iostream>
#include <getopt.h>

#include "CImg.h"
#include "board.hpp"

void help()
{
    std::cout << "-h\t\t Help" << std::endl;
    std::cout << "-s <num>\t Number of Pixels on both X and Y axis"
        << std::endl;
    std::cout << "-b <num>\t The number of blocks to create per row" 
        << std::endl;
}

int main(int argc, char** argv)
{
    int opt;
    int size = 500, num_of_blocks = 10;
    while ( (opt = getopt(argc, argv, "s:b:h")) != -1 )
    {
        switch (opt)
        {
            case 's':
                size = atoi(optarg);
                break;
            case 'b':
                num_of_blocks = atoi(optarg);
                break;
            case 'h':
                help();
                exit(EXIT_SUCCESS);
                break;
        }
    }
    BOARD game(size, num_of_blocks);
    game.Start();
    return 0;
}
