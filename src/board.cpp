#include <iostream>

#include "board.hpp"
#include <map>

BOARD::BOARD(int board_size, int num_of_blocks) :
    thread_running(false)
{
    unsigned char img[board_size * board_size];

    size = board_size;

    block_size = size / num_of_blocks;
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
                img[idx] = grey;
            }
            else
            {
                img[idx] = black;
            }
        }
    }

    __pic = cimg_library::CImg<unsigned char>(img, size, size);
    pic = cimg_library::CImg<unsigned char>(img, size, size);

    disp = cimg_library::CImgDisplay(size, size, "Conway's Game of Life");
    disp.display(pic);
}

void BOARD::Start()
{
    while (! disp.is_closed())
    {
        disp.wait();
        if (disp.button() && disp.mouse_y() >= 0)
        {
            const int y = disp.mouse_y();
            const int x = disp.mouse_x();

            if (! thread_running)
            {
                UpdateBoard(x / block_size, y / block_size);
                pic = __pic;
                disp.display(pic);
            }
	}
        else if (disp.is_keySPACE())
        {

            if (! _thread.joinable())
            {
                thread_running = true;
                _thread = std::thread(&BOARD::EvolveThread, this);
            }
            else
            {
                thread_running = false;
                _thread.join();
            }
        }
    }
}

/*
 * Private Functions
 * -----------------------
 */

/*
 * Thread that checks cells states and updates board
 */
void BOARD::EvolveThread()
{
    // we don't use 100
    unsigned char default_val = 100;
    int range[4];
    unsigned char val[8];
    int neighbor_idx[8][2] =
        {
            {-1, -1}, {-1,  0}, {-1,  1},
            { 0,  1}, { 1,  1},
            { 1,  0}, { 1, -1},
            { 0, -1}
        };

    while (thread_running)
    {
        for (int x = 0; x < num_blocks; x++)
        {
            for (int y = 0; y < num_blocks; y++)
            {
                int live_neighbors = 0;
                // TODO: Can I make this cleaner?

                // check states around current cell
                // will return default value if coordinates are out of range
                for (int i = 0; i < 8; i++)
                {
                    GetBlockRange(x + neighbor_idx[i][0], 
                                    y + neighbor_idx[i][1], &range[0]);
                    val[i] = pic.atXY(range[0], range[1], 0, 0,
                                        default_val);
                }

                // get current status of cell
                GetBlockRange(x, y, &range[0]);
                unsigned char curr_state = pic.atXY(range[0], range[1], 0, 0,
                                                        default_val);

                for (int i = 0; i < 8; i++)
                {
                    if (val[i] != default_val)
                    {
                        if (val[i] == white)
                        {
                            live_neighbors += 1;
                        }
                    }
                }

                if ( curr_state == white && 
                    (live_neighbors == 2 || live_neighbors == 3) )
                {
                      UpdateBoard(x, y, white);
                }
                else if (curr_state == black && live_neighbors == 3)
                {
                    UpdateBoard(x, y, white);
                }
                else
                {
                    UpdateBoard(x, y, black);
                }
            }
        }

        pic = __pic;
        disp.display(pic);

        // to keep people from having a seizure
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

}

/*
 * Changes the state of block at (x,y)
 * state_override : -1 (off by default), 255 (white), 0 (black)
 */
void BOARD::UpdateBoard(int x, int y, int s_override)
{

    int range[4];

    GetBlockRange(x, y, &range[0]);

    // turn block white if not overriden with black and currently black
    // turn block white if overriden with white
    if ( (__pic._atXY(range[0], range[1]) == black && s_override != black)
        || s_override == white )
    {
        __pic.draw_rectangle(range[0], range[1], range[2], range[3], &white);
    }

    // turn block black if not overriden with white and currently white
    // turn block black if overriden with black
    else if ( (__pic._atXY(range[0], range[1]) == white && s_override != white)
            || s_override == black )
    {
        __pic.draw_rectangle(range[0], range[1], range[2], range[3], &black);
    }

}

/*
 * Get range for given block by corrdinates 
 * NOTE : This is the number of blocks not image size
 */
int BOARD::GetBlockRange(int x, int y, int* range)
{
    /* range[0] : x1
     * range[1] : y1
     * range[2] : x2
     * range[3] : y2
     */

    // the constant values applied are because we need to only edit values
    // only within the grey border

    range[0] = x * block_size + 1;
    range[1] = y * block_size + 1;
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
