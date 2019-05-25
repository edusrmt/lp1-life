#ifndef LIFE_H
#define LIFE_H

#include <vector>
#include <iostream>

namespace life {
    /**
     * @brief A class that represents a generation.
     * @author Eduardo Sarmento & Victor Vieira
     * 
     * Stores all data of one generation.
     */   
    class Life {
        private:        
        int g_rows;                             //!< Number of game space's rows.
        int g_cols;                             //!< Number of game space's columns.
        std::vector<std::vector<bool>> grid;    //!< Matrix that stores the state of all cells in the generation.

        public:
        /*! Default constructor.
         *
         * @param rows Number of rows.
         * @param cols Number of columns.
         */
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

        /// Empty constructor.
        Life () {}

        /// Class destructor.
        ~Life() { 
            
        }

        /*! Change the state of a cell to alive.
         *
         * @param row Row where the cell is located.
         * @param col Column where the cell is located.
         */
        void set_alive (int row, int col) {
            grid[row][col] = true;
        }

        /*! Check if the all cells of the generation are dead.
         *
         * @return Population is extinct?
         */
        bool extinct () {
            for (int i = 0; i < g_rows; i++) {
                for (int j = 0; j < g_cols; j++) {
                    if(grid[i][j] == true)
                        return false;
                }
            }

            return true;
        }

        /*! Check if a cell is alive or not.
         *
         * @param row Row where the cell is located.
         * @param col Column where the cell is located.
         * @return Cell is alive?
         */
        bool check_cell (int row, int col) {
            if ((row >= 0 && row < g_rows) && (col >= 0 && col < g_cols))
                return grid[row][col];
            else
                return false;
            
        }

        /// Assignment operator.
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

        /// Equality comparison operator.
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