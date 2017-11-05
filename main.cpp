#include <iostream>
#include <fstream>
#include "Network.hpp"

using namespace std;
/** \brief read the entry (a double expected) on the terminal
 */
double AskUserADouble();
/** \brief write the spiking time of the first numberOfNeuronsToRecord (in Constants.hpp) neurons (we suppose they represent the activity of the whole network)
 */
//void writeSpikesDataFile(Network const& network);

/** \brief main function of the program
 * create a Network and run a simulation on it during a certain time asked to the user, then write wich neuron spiked at wich time
 * in a "spikes.gdf" file
 */
int main() {
			//simulation
		cout<<"simulation time? (ms)"<<endl;
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
	
	
/*void writeSpikesDataFile(Network const& network)
{
	ofstream out("spikes.gdf",ios::trunc); //declaration stream d'ecriture
	for(unsigned int i(0);i<numberOfNeuronsToRecord;++i){
		for(unsigned int j(0);j<(network.getSpikesVectorForNeuroneAtIndix(i)).size();++j){
		out<<network.getSpikesVectorForNeuroneAtIndix(i)[j]*0.001<<"\t"<<i<<"\n"; //the 0.001 is to adjust the graph to the settings of the web application wich draw
																				// the graph in wich unit are second
		}
	}
}*/


double AskUserADouble() {
	double result;
	cin>>result;
	if(cin.fail()){throw;}
	return result;
	}
