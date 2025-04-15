#include <iostream>
#include <fstream>
#include "include/write.h"

int writeDoubles(double data[][1000][8])
{
      std::cout << "Writing started" << std::endl;

      std::ofstream myfile;
      myfile.open ("data.csv");
      myfile << "This is the first cell in the first column.\n";
      myfile << "a,b,c,\n";
      myfile << "c,s,v,\n";
      myfile << "1,2,3.456\n";
      myfile << "semi;colon\n";
      myfile << "data[0][0]\n";
      // myfile << data[0] << "\n";
      myfile << "data all values:\n";

      // write first 8000 values of data into file

      for (int k = 0; k < 10; k++) {

        for (int i = 0; i < 8; i++) {

          for (int j = 0; j < 1000; j++) {

          
              myfile << data[k][j][i] << ",";
          

          }
          myfile << std::endl;

        }
        myfile << "*" << std::endl << std::endl;

      }

      myfile.close();
      std::cout << "WRITE SUCCESSFUL" << std::endl;
      return 0;
}