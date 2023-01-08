# fillit

Backtracking algorithm which takes 1-26 tetriminos blocks as an input and finds the smallest square that those blocks fit into. Blocks are not rotated.\
Accepts input in only correct format:\
• Precisely 4 lines of 4 characters, each followed by a new line (well... a 4x4 square).\
• A Tetrimino is a classic piece of Tetris composed of 4 blocks.\
• Each character must be either a block character(’#’ ) or an empty character (’.’).\
• Each block of a Tetrimino must touch at least one other block on any of his 4 sides (up, down, left and right).\
Examples in test dir.

### Installation
clone git\
make\
./fillit <param>\
For example:\
./fillit test/Valid_blocks/26Pieces\

Hope you have as fun using it as I have making it!
