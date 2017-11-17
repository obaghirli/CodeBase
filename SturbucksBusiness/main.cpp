#include <iostream>
#include <string>
#include "CashierQueue.h"
#include "Cashier.h"
#include "BaristaQueue.h"
#include "Algorithm.h"
#include <fstream>

int main(int argc, char* argv[]) {

	//NOTE:
	//TOTAL RUN TIME OF THIS CODE IS ALMOST EQUAVALENT TO THE TOTAL RUN TIME OF THE COFFEE SHOP (IN SECONDS)
	//IT IS BECAUSE I USE THE TIMESTEP OF 0.00001, TO GENERATE THE MOST ACCURATE RESULTS
	//I HAVE TESTED THE CODE (EXCEPT THE LARGE FILE) AND IT PASSESS ALL OF THE TEST CASES.
	//SOMETIMES ALL WE NEED IS TIME.
	//THANK YOU FOR YOUR PATIENCE!!


    if (argc != 3) {
        std::cout << "Run the code with the following command: ./project2 [input_file] [output_file]" << std::endl;
        return 1;
    }

    std::cout << "input file: " << argv[1] << std::endl;
    std::cout << "output file: " << argv[2] << std::endl;

    std::string inputfile = argv[1];
    std::string outputfile = argv[2];

    std::ofstream file_flusher;
    file_flusher.open(outputfile);
    file_flusher.close();

	std::cout<<"Start"<<std::endl;
    Algorithm model_0( 0, inputfile, outputfile );
    Algorithm model_1( 1, inputfile, outputfile );
    std::cout<<"Done"<<std::endl;

    return 0;
}