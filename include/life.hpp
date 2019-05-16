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
        
        int g_rows, g_cols;

        public:
        std::vector<std::vector<bool>> grid;

        Life (int rows, int cols) : g_rows{rows}, g_cols{cols} {
            grid.resize(rows);

            for(std::vector<bool> c : grid)
                c.resize(cols);

            for (int i = 0; i < g_rows; i++) {
                for (int j = 0; j < g_cols; j++) {
                    grid[i].push_back(false);
                }
            }
        }

        Life () {}

        ~Life() { 
            
        }

        void set_alive (int row, int col) {
            grid[row][col] = true;
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