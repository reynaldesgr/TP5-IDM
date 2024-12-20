/**
 * @file testRand.cpp
 * @brief generates random numbers using CLHEP MTwistEngine and writes them to a binary file.
 *
 * creates 3,000,000 random numbers using the CLHEP::MTwistEngine. 
 * each random number is scaled to an unsigned integer and written to a file named "rngbForMarsagliaTests".
 *
 * @details
 * - random numbers are generated in the ran       ge [0, UINT_MAX].
 *
 * @author SEGERIE Reynalde
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <iostream>
#include "CLHEP/Random/MTwistEngine.h"

/**
 * @brief main function to generate and save random numbers.
 *
 * initializes a CLHEP::MTwistEngine object to generate random numbers.
 * the numbers are scaled to unsigned integers and written to a file named "rngbForMarsagliaTests".
 *
 * @return int exit status.
 */
int main () {
   CLHEP::MTwistEngine * s = new CLHEP::MTwistEngine();

   int fs; ///< file descriptor for the output file
   double f; ///< temporary variable to store the random number
   unsigned int nbr; ///< variable to store the scaled random number

   fs = open("./rngbForMarsagliaTests", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
   
   if (fs == -1) {
       std::cerr << "Error opening file" << std::endl;
       delete s;
       return 1;
   }

   /**
    * loop to generate and write random numbers.
    *
    * generates 2,999,999 random numbers using the MTwistEngine.
    * each number is scaled to an unsigned int and written to the file.
    */
   for(int i = 1; i < 3000000; ++i) {
     f = s->flat(); ///< generate a random number between 0 and 1
     nbr = static_cast<unsigned int>(f * UINT_MAX); ///< scale to an unsigned int range
     std::cout << f << std::endl; ///< print the random number to the console

     if (write(fs, &nbr, sizeof(unsigned int)) == -1) {
         std::cerr << "Error writing to file" << std::endl;
         close(fs);
         delete s;
         return 1;
     }
   }
   
   close(fs);

   delete s;

   return 0;
}
