#include <iostream>
#include <fstream>
#include "Network.hpp"

using namespace std;
/** \brief read the entry (a double expected) on the terminal
 */
double AskUserADouble();

/** \brief main function of the program
 * create a Network and run a simulation on it during a certain time asked to the user, then write wich neuron spiked at wich time
 * in a "spikes.gdf" file
 */
int main() {
			//simulation
		cout<<"simulation time? (ms) ("<<TimeIncrement<<")"<<endl;
		double Tstop(AskUserADouble());
		int clock(0);
		Network network (TOTAL_NUMBER_OF_NEURONES,EXITATORY_PROPORTION,ProbabilityOfConnection,ProbabilityOfConnection,clock);
		cerr<<"build network finished"<<endl;
		network.runSimulation(Tstop);
		cerr<<"simulation finished"<<endl;
			//writing simulation result for latter analisys
		network.writeSpikesDataFile("spikes.gdf");
		cerr<<"writing data file finished"<<endl;
		
		return 0;
	}


double AskUserADouble() {
	double result;
	cin>>result;
	if(cin.fail()){throw;}
	return result;
	}
