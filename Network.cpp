#include <iostream>
#include "Network.hpp"
#include <random>
#include <string>
#include <fstream>

#define NDEBUG
#include <cassert>

using namespace std;
		
	Network::Network(unsigned int const& numberOfNeurones,double const& exitatoryProportion,
      	double const& exitatoryConnectionProbability,double const& inhibitoryConnectionProbability,int const& clock)
	:clock_(clock){
		//assert the probability are in the correct range
			assert(exitatoryProportion>=0.0 and exitatoryProportion<=1.0);
			assert(exitatoryConnectionProbability>=0.0 and exitatoryConnectionProbability<=1.0);
			assert(inhibitoryConnectionProbability>=0.0 and inhibitoryConnectionProbability<=1.0);
		
			//creating our neurones
			int numberOfExitatoryNeurones(numberOfNeurones*exitatoryProportion);
			
		for (unsigned int i(0);i<numberOfNeurones;++i){ //i start at 0 so < and not <=
			if(i<numberOfExitatoryNeurones){ //i start at 0 so < and not <=
				neurones_.push_back(new Neurone(clock,Iexterieur,true,i));
			}
			else{
				neurones_.push_back(new Neurone(clock,Iexterieur,false,i));
			}
		}
			//creating the connection
		for (unsigned int i(0);i<numberOfNeurones;++i){
			neurones_[i]->setConnections(createConnectionForANeurone(numberOfNeurones,exitatoryProportion,
 				exitatoryConnectionProbability,inhibitoryConnectionProbability,i));
		}
	}

	vector<unsigned int> Network::createConnectionForANeurone(unsigned int const& numberOfNeurones,double const& exitatoryProportion,
      	double const& exitatoryConnectionProbability,double const& inhibitoryConnectionProbability,unsigned int const& NeuroneIndix){
			vector<unsigned int> connections;
			unsigned int indixAfterWichEachNeuroneIsInhibitory(numberOfNeurones*exitatoryProportion-1);
			//generation aléatoire
			static random_device rd;
			static mt19937 gen(rd());

			//uniforme sur les excitatoires
			std::uniform_int_distribution<int> distributionEx(0,indixAfterWichEachNeuroneIsInhibitory);
			int numberOfExitatoryNeuronesConnection (numberOfNeurones*exitatoryProportion*exitatoryConnectionProbability);
			for(unsigned int i(0);i<numberOfExitatoryNeuronesConnection;++i){
				int indix = distributionEx(gen);
				connections.push_back(indix);
			}

			//uniforme sur les inhib
			std::uniform_int_distribution<> distributionIn(indixAfterWichEachNeuroneIsInhibitory+1,numberOfNeurones-1);
			//static std::uniform_int_distribution<> distributionIn(0,(numberOfNeurones-1)-(indixAfterWichEachNeuroneIsInhibitory+1));
			int numberOfInhibitoryNeuronesConnection ((numberOfNeurones-exitatoryProportion*numberOfNeurones)*inhibitoryConnectionProbability);
			for(unsigned int i(0);i<numberOfInhibitoryNeuronesConnection ;++i){
				int indix(distributionIn(gen));
				connections.push_back(indix);
			}
			
			return connections;
	}

      Network::~Network(){
      	for(auto& ptr:neurones_){
      		ptr=nullptr;
      		delete ptr;
      	}
      }

     void Network::runSimulation(double const& Tstop){
     	int TotalNumberOfTimeIncrement(Tstop/TimeIncrement);
     	cout<<"simulation running ... "<<endl;
     	int OnePercent(0.01*TotalNumberOfTimeIncrement);
     	//simulation loop
     	while (clock_<TotalNumberOfTimeIncrement){
			if(clock_%OnePercent==0){
				cout<<(double)clock_*100/(double)TotalNumberOfTimeIncrement<<"%"<<flush;
				cerr<<"\r";
			}
			for(auto& n:neurones_){ 
				bool spike(n->update(1));
				if(spike){
					for(auto& indixNeuroneConnected:n->getConnections()){
						neurones_[indixNeuroneConnected]->receive((clock_+D),n->getJsentToPostSynapticNeurone());
					}
				}
			}
			clock_+=1;
		}
     }
     
     std::vector<int> Network::getSpikesVectorForNeuroneAtIndix(unsigned int const& indix)const{
		 assert(indix<neurones_.size());
		 return (neurones_[indix]->getSpikesTimeInNumberOfTimeIncrement());
	 }
	 
	 void Network::writeSpikesDataFile(string const& fileName) const
{
	ofstream out(fileName,ios::trunc); //declaration stream d'ecriture
	for(unsigned int i(0);i<numberOfNeuronsToRecord;++i){
		for(unsigned int j(0);j<(neurones_[i]->getSpikesTimeInNumberOfTimeIncrement()).size();++j){
		out<<neurones_[i]->getSpikesTimeInNumberOfTimeIncrement()[j]*0.001<<"\t"<<i<<"\n"; //the 0.001 is to adjust the graph to the settings of the web application wich draw
																				// the graph in wich unit are second
		}
	}
}
	 
