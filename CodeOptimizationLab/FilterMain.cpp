#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Filter.h"
#include <omp.h>

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

class Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}


double
applyFilter(class Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();
  int filterArray[3][3];
          filterArray[0][0] = filter -> get(0, 0);
          filterArray[0][1] = filter -> get(0, 1);
          filterArray[0][2] = filter -> get(0, 2);
     
          filterArray[1][0] = filter -> get(1, 0);
          filterArray[1][1] = filter -> get(1, 1);
          filterArray[1][2] = filter -> get(1, 2);
     
          filterArray[2][0] = filter -> get(2, 0);
          filterArray[2][1] = filter -> get(2, 1);
          filterArray[2][2] = filter -> get(2, 2);
  
  output -> width = input -> width;
  output -> height = input -> height;
  //int size = filter -> getSize(); Size always = 3
  const short width= (input -> width)-1; //Replace width in loop
  const short height = (input -> height)-1; //Replace height in loop
  const short divisor = filter -> getDivisor(); //Get getDivisor out of loop
  int plane0, plane1, plane2;
  if (filterArray[0][0] == 1 && filterArray[0][1] == 1 && filterArray[0][2] == 1 &&
           filterArray[1][0] == 1 && filterArray[1][1] == 1 && filterArray[1][2] == 1 &&
           filterArray[2][0] == 1 && filterArray[2][1] == 1 && filterArray[2][2] == 1){
    #pragma omp parallel for
    for(int row = 1; row < height; row++) {
        int row0 =row - 1;
        int row1 =row + 1;
          for(int col = 1; col < width; col++) {
              
            plane0 = (input -> color[0][row0][col - 1] ) + (input -> color[0][row0]
                     [col] ) + (input -> color[0][row0][col + 1] )+ (input -> color[0][row][col - 1]  ) + (input -> color[0][row]
                     [col] ) + (input -> color[0][row][col + 1] )+ (input -> color[0][row1][col - 1] ) + (input -> color[0][row1]
                     [col] ) + (input -> color[0][row1][col + 1] );
            
              
            plane1 = (input -> color[1][row0][col - 1] ) + (input -> color[1][row0]
                     [col] ) + (input -> color[1][row0][col + 1]  )+ (input -> color[1][row][col - 1] ) + (input -> color[1][row]
                     [col] ) + (input -> color[1][row][col + 1] )+ (input -> color[1][row1][col - 1]  ) + (input -> color[1][row1]
                     [col]  ) + (input -> color[1][row1][col + 1] );
            
              
            plane2 = (input -> color[2][row0][col - 1]  ) + (input -> color[2][row0]
                     [col]) + (input -> color[2][row0][col + 1]  )+ (input -> color[2][row][col - 1]  ) + (input -> color[2][row]
                     [col] ) + (input -> color[2][row][col + 1])+ (input -> color[2][row1][col - 1] ) + (input -> color[2][row1]
                     [col] ) + (input -> color[2][row + 1][col + 1] );
              
            if(divisor !=1){
                plane0 = plane0/ divisor;
                plane1 = plane1/ divisor;
                plane2 = plane2/ divisor;
            }
              
            output -> color[0][row][col] = plane0  < 0  ? 0: plane0  > 255  ? 255: plane0;
            output -> color[1][row][col] = plane1  < 0  ? 0: plane1  > 255  ? 255: plane1;
            output -> color[2][row][col] = plane2  < 0  ? 0: plane2  > 255  ? 255: plane2;
          }
        
      }
  }
  else{
     #pragma omp parallel for
      for(int row = 1; row < height; row++) {
        int row0 =row - 1;
        int row1 =row + 1;
          for(int col = 1; col < width; col++) {

            plane0 = (input -> color[0][row0][col - 1] * filterArray[0][0] ) + (input -> color[0][row0]
                     [col] * filterArray[0][1] ) + (input -> color[0][row0][col + 1] * filterArray[0][2] ) +
            (input -> color[0][row][col - 1] * filterArray[1][0] ) + (input -> color[0][row]
                     [col] * filterArray[1][1] ) + (input -> color[0][row][col + 1] * filterArray[1][2] )
            + (input -> color[0][row1][col - 1] * filterArray[2][0] ) + (input -> color[0][row1]
                     [col] * filterArray[2][1] ) + (input -> color[0][row1][col + 1] * filterArray[2][2] );
            
              
            plane1 = (input -> color[1][row0][col - 1] * filterArray[0][0] ) + (input -> color[1][row0]
                     [col] * filterArray[0][1] ) + (input -> color[1][row0][col + 1] * filterArray[0][2] )
            + (input -> color[1][row][col - 1] * filterArray[1][0] ) + (input -> color[1][row]
                     [col] * filterArray[1][1] ) + (input -> color[1][row][col + 1] * filterArray[1][2] )
            + (input -> color[1][row1][col - 1] * filterArray[2][0] ) + (input -> color[1][row1]
                     [col] * filterArray[2][1] ) + (input -> color[1][row1][col + 1] * filterArray[2][2] );
            
              
            plane2 =  (input -> color[2][row0][col - 1] * filterArray[0][0] ) + (input -> color[2][row0]
                     [col] * filterArray[0][1] ) + (input -> color[2][row0][col + 1] * filterArray[0][2] )
            +(input -> color[2][row][col - 1] * filterArray[1][0] ) + (input -> color[2][row]
                     [col] * filterArray[1][1] ) + (input -> color[2][row][col + 1] * filterArray[1][2] )
            + (input -> color[2][row1][col - 1] * filterArray[2][0] ) + (input -> color[2][row1]
                     [col] * filterArray[2][1] ) + (input -> color[2][row + 1][col + 1] * filterArray[2][2] );
              
            if(divisor !=1){
                plane0 = plane0/ divisor;
                plane1 = plane1/ divisor;
                plane2 = plane2/ divisor;
            }
              
            output -> color[0][row][col] = plane0  < 0  ? 0: plane0  > 255  ? 255: plane0;
            output -> color[1][row][col] = plane1  < 0  ? 0: plane1  > 255  ? 255: plane1;
            output -> color[2][row][col] = plane2  < 0  ? 0: plane2  > 255  ? 255: plane2;
          }
        
      }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
