#include <iostream>
#include <fstream>
#include "include/write.h"

int writeDoubles(double * data)
{

    

      std::ofstream myfile;
      myfile.open ("data.csv");
      myfile << "This is the first cell in the first column.\n";
      myfile << "a,b,c,\n";
      myfile << "c,s,v,\n";
      myfile << "1,2,3.456\n";
      myfile << "semi;colon\n";
      myfile << "data[0]\n";
      myfile << data[0] << "\n";
      myfile << "data all values:\n";

      //write first 20 values of data into file

      for (int i = 0; i < 8; i++)
      {
          for (int j = 0; j < 1000; j++) {
              myfile << data[i][j] << ",";
          }
      }

      myfile.close();
      return 0;
}
