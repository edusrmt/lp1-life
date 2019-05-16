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
        std::vector<std::vector<bool>> grid;

        public:
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


        bool check_cell (int row, int col) {
            if ((row >= 0 && row < g_rows) && (col >= 0 && col < g_cols))
                return grid[row][col];
            else
                return false;
            
        }

        Life& operator=(const Life& other) {
            g_rows = other.g_rows;
            g_cols = other.g_cols;
            grid = other.grid;

            for (int i = 0; i < g_rows; i++) {
                for (int j = 0; j < g_cols; j++) {
                    grid[i][j] = other.grid[i][j];
                }
            }

            return *this;
        }

        bool operator==(const Life& other) {
            for (int i = 0; i < g_rows; i++) {
                for (int j = 0; j < g_cols; j++) {
                    if(grid[i][j] != other.grid[i][j])
                        return false;
                }
            }

            return true;
        }
    };
}
#endif