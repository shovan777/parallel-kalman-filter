#include <iostream>
#include <fstream>
int main( int argc, char* argv[] )
{

    int data[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

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

      for (int i = 0; i < 20; i++)
      {
          myfile << data[i] << ",";
      }

      myfile.close();
      return 0;
}