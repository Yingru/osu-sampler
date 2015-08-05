//===============================================================================
//  iSpectraSampler
//===============================================================================
//
//  Zhi Qiu & Chun Shen
//    qiu.24@asc.ohio-state.edu
//    shen.201@asc.ohio-state.edu
//
//        Date: 03/2012
// Version info written in the main function.



#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>

#include "main.h"
#include "ParameterReader.h"
#include "Table.h"
#include "readindata.h"
#include "emissionfunction.h"
#include "arsenal.h"

using namespace std;


int main(int argc, char** argv)
{
   // read in parameters
   ParameterReader *paraRdr = new ParameterReader;
   paraRdr->readFromFile("sampler.conf");
   paraRdr->readFromArguments(argc, argv);

   // Chun's input reading process
   string path="results";

   //load freeze out information
   read_FOdata freeze_out_data(paraRdr, path);

   int FO_length = 0;
   FO_length = freeze_out_data.get_number_of_freezeout_cells();

   FO_surf* FOsurf_ptr = new FO_surf[FO_length];
   for(int i=0; i<FO_length; i++)
     for(int j=0; j<Maxparticle; j++)
         FOsurf_ptr[i].particle_mu[j] = 0.0e0;

   freeze_out_data.read_in_freeze_out_data(FO_length, FOsurf_ptr);

   //read the chemical potential on the freeze out surface
   particle_info *particle = new particle_info [Maxparticle];
   int Nparticle = freeze_out_data.read_in_chemical_potentials(path, FO_length, FOsurf_ptr, particle);

   // Next, Zhi's turn...
   // init random seed from system time
   timeval a;
   gettimeofday(&a, 0);
   long randomSeed=paraRdr->getVal("randomSeed");
   if (randomSeed<0) randomSeed=a.tv_usec; // randomSeed<0 means to use CPU clock
   srand48(randomSeed);

   Table chosen_particles("tables/chosen_particles.dat"); // skip others except for these particle
   Table pT_tab("tables/pT_gauss_table.dat"); // pt position and weight table
   Table phi_tab("tables/phi_gauss_table.dat"); // phi position and weight table
   //Table eta_tab("tables/eta_gauss_table_30_full.dat"); // eta uniform dist table
   Table eta_tab("tables/eta_uni_table.dat"); // eta uniform dist table
   EmissionFunctionArray efa(&chosen_particles, &pT_tab, &phi_tab, &eta_tab, particle, Nparticle, FOsurf_ptr, FO_length, paraRdr);

   std::cout << std::fixed;

   efa.shell();
   //efa.combine_samples_to_OSCAR();
}
