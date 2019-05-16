#ifndef LIFE_H
#define LIFE_H

#include <vector>

namespace life {
    //! Manages the game execution.
    /*!
     * Insert description of Life here.
    */    
    class Life {
        private:
        bool **grid;
        int g_rows, g_cols;

        public:
        Life (int rows, int cols) : g_rows{rows}, g_cols{cols} {
            grid = new bool*[rows];

            for(int i = 0; i < rows; i++)
                grid[i] = new bool[cols];
        }

        Life () {}

        ~Life() { 
            /*for(int i = 0; i < g_rows; i++)
                if (grid[i] != nullptr) delete [] grid[i];

            if (grid != nullptr) delete [] grid;*/
        }

        bool stable () {
            return false;
        }

        bool extinct () {
            for (int i = 0; i < g_rows; i++) {
                for (int j = 0; j < g_cols; j++) {
                    if(grid[i][j] == true)
                        return false;
                }
            }

            return true;
        }
    };
}
#endif