#include "CImg.h"

#include <thread>

class BOARD
{
    public:

        BOARD(int, int);

        // cimg does all cleanup for me
        ~BOARD() {};

        void Start();

    private:

        void EvolveThread();

        void UpdateBoard(int, int, int state_override = -1);

        int GetBlockRange(int, int, int*);
        int GetIndex(int, int);

        // used for blocks
        const unsigned char white = 255;
        const unsigned char black = 0;
        const unsigned char grey = 255 / 2;

        int size;
        int num_blocks;
        int block_size;

        cimg_library::CImgDisplay disp;

        std::thread _thread;
        bool thread_running;

        // data being displayed to the user.
        cimg_library::CImg<unsigned char> pic;
        // internal buffer
        cimg_library::CImg<unsigned char> __pic;
};