/* 
 * File:   main.cpp
 * Author: vitex
 *
 * Created on 12. červenec 2015, 1:39
 */



#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) {
    // Check the number of parameters
    if (argc < 2) {
        // Tell the user how to run the program
        cerr << "Usage: " << argv[0] << " SIZE" << endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return 1;
    }
        unsigned int count;
        unsigned int number;


        unsigned int size;
        
        if (argv[1]) {
            size = atoi(argv[1]);
        } else {
            size = 1024;
        }
        if (argv[2]) {
            count = atoi(argv[2]);
        } else {
            count = 1000000;
        }


        for (unsigned int i = 0; i < count; i++) {
            number = rand() % (size + 1);
            cout << number << "\n";


        }
    return 0;
}

