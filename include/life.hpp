#ifndef LIFE_H
#define LIFE_H

namespace life {
    //! Manages the game execution.
    /*!
     * Insert description of Life here.
    */    
    class Life {
        private:
        bool **grid;
        int g_rows;

        public:
        Life (int rows, int cols) : g_rows{rows} {
            grid = new bool*[rows];

            for(int i = 0; i < rows; i++)
                grid[i] = new bool[cols];
        }

        ~Life() {
            for (int i = 0; i < g_rows; i++)
                delete [] grid[i];
            
            delete [] grid;
        }
    };
}
#endif