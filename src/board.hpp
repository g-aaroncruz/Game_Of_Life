#include "CImg.h"

class BOARD
{
    public:

        explicit BOARD(int);

        // cimg does all cleanup for me
        ~BOARD() {};

        void UpdateBoard();
    private:;


        int GetBlockRange(int, int, int*);
        int GetIndex(int, int);

        // used for blocks
        unsigned char white = 255;
        unsigned char black = 0;

        int size;
        int num_blocks;
        int block_size;

        cimg_library::CImgDisplay disp;

        // data being displayed to the user.
        cimg_library::CImg<unsigned char> pic;
        // internal buffer
        cimg_library::CImg<unsigned char> __pic;
};