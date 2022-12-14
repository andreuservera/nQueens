#include "ChromosomePrinter.h"

#include <iostream>

using namespace std;

ChromosomePrinter::ChromosomePrinter(t_chromosome_data data)
{
    for (size_t row = N_QUEENS - 1; row < N_QUEENS; row--) {
        cout << row;
        for (size_t col = 0; col < N_QUEENS; col++) {
            if (data.at(col) == row) {
                cout << "|O";
            }else{
                cout << "| ";
            }
        }
        cout << "|\n";
    }
    cout << endl;
}