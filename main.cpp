#include "subclustering.h"
#include <time.h>
#include <fstream>
#include <vector>

using namespace alglib;
using namespace std;

int main(int argc, char **argv)
{

    clock_t start, end;
    start = clock();

    arguments_t args;

    // Read config
    ifstream conf("D:\\Projects\\CPP\\Subclustering-Algorithm-master\\src\\Configs.txt");
    if(!conf)
        return -1;

    conf >> args.dimension >> args.k >> args.input_filename >> args.output_filename;
    cout << args.dimension << " " << args.k << " " << args.input_filename << " " << args.output_filename << endl;
    conf.close();

    // Open the input file
    std::ifstream inputFile(args.input_filename);
    if(!inputFile)
        return -1;

    // Create a vector that contains rawdata
    std::vector<std::vector<double>> indata;

    int s = 0;
    // Read the contents of the file
    while (!inputFile.eof()){

        // Read values in add them to vector "rawdata"
        std::vector<double> point;
        for (int i = 0; i < args.dimension; ++i){
            double coordinate;
            inputFile >> coordinate;
            point.push_back(coordinate);
        }

        // Program will ignore empty line at the end
        indata.push_back(point);
        s++;
        if (s % 10000 == 0)
            cout << s << endl;
    }
    cout << s << endl;
    indata.pop_back();
    s--;
    // Close the input file
    inputFile.close();

    alglib::real_2d_array data;
    data.setlength(s, args.dimension);

    for (int indpoint = 0; indpoint < s; indpoint++){
        for (int indcoord = 0; indcoord < args.dimension; indcoord++){
            data[indpoint][indcoord] = indata[indpoint][indcoord];
        }
    }

    std::cout << data[0][0] << std::endl;

//    for (int i = 0; i < indata.size(); i++){
//        for (int j = 0; j < args.dimension; j++){
//            cout << data[i][j] << " ";
//        }
//        cout << endl;
//    }


    end = clock();
    std::cout << "time for reading file: " << double(end - start) / (double) CLOCKS_PER_SEC << " seconds" << std::endl;

    start = clock();
    SubClustering sc;
    sc.run(data, int(s/args.k), args.output_filename);

    std::cout << "Clustering done succesfully" << endl;
    end = clock();
    double time_in_seconds = (end - start) / (double) CLOCKS_PER_SEC;
    std::cout << "time for clusterization " << args.input_filename << " dataset: " << time_in_seconds << " seconds";
    return 0;
}