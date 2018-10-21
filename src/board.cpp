#include "board.hpp"

#include <unistd.h> // for usleep

BOARD::BOARD(int board_size)
{
    unsigned char img[board_size * board_size];

    size = board_size;
    
    // i want 10 blocks per row / col
    block_size = size / 10;
    num_blocks = size / block_size;

    // init to black
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            int idx = GetIndex(x, y);
            if (y % block_size == 0 || x % block_size == 0)
            {
                // set border
                img[idx] = 255 / 2;
            }
            else
            {
                img[idx] = 0;
            }
        }
    }

    __pic = cimg_library::CImg<unsigned char>(img, size, size);
    pic = cimg_library::CImg<unsigned char>(img, size, size);

    disp = cimg_library::CImgDisplay(size, size, "Conway's Game of Life");
    disp.display(pic);
}

/*
 * Private Functions
 */

void BOARD::UpdateBoard()
{
    // for x
    // for y
    // check surrounding states

    int range[4];
    for (int x = 0; x < num_blocks; x++)
    {
        for (int y = 0; y < num_blocks; y++)
        {
            GetBlockRange(x, y, &range[0]);

            __pic.draw_rectangle(range[0], range[1],
                range[2], range[3], &white);

            pic = __pic;
            disp.display(pic);
            usleep(100000);


        }
    }
}

/*
 * Get range for given block by corrdinates 
 * NOTE : This is the number of blocks not image size
 */
int BOARD::GetBlockRange(int x, int y, int* range)
{
    /* 0 : x1
     * 1 : y1
     * 2 : x2
     * 3 : y2
    */

    // the 2 is to keep the bordering around the images
    range[0] = x * block_size + 2;
    range[1] = y * block_size + 2;
    range[2] = range[0] + (block_size - 2);
    range[3] = range[1] + (block_size - 2);

}

/*
 * Get the array index of given coordinates
 */
int BOARD::GetIndex(int x, int y)
{
    return (x * size) + y;            
}