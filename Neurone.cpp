#include <iostream>
#include "Neurone.hpp"
#include <cmath>
#include <random>
using namespace std;

#define NDEBUG
#include <cassert>

	Neurone::Neurone (int const& clock,double const& Iext,bool const& isExitatory,unsigned int const& neuroneID,double const& ExternalRandomSpikesFrequencyPerTimeStep)
	:spikeRingBuffer_(DelayInTimeIncrement+1,0.0),membranePotential_(STANDART_POTENTIAL),localClock_(clock),Iext_(Iext)
	,isExitatory_(isExitatory),neurone_ID_(neuroneID),ExternalRandomSpikesFrequencyPerTimeStep_(ExternalRandomSpikesFrequencyPerTimeStep){}
	
	bool Neurone::update(unsigned int const& NumberOfTimeIncrement){
		bool spike(false);
		for(unsigned int i(1);i<=NumberOfTimeIncrement;++i){
			size_t currentIndex(localClock_%spikeRingBuffer_.size());
				if(membranePotential_>=SpikeThreshold)
				{
					//1 we store the spike time
					SpikesTimeInNumberOfTimeIncrement_.push_back(localClock_);
					//2 the neurone goes refractory: the potential fall down to Constants::RefractoryPotential
					membranePotential_=RefractoryPotential;
					//the neuron has spiked
					spike=true;
				} 
				
				else if(not SpikesTimeInNumberOfTimeIncrement_.empty() and (localClock_-SpikesTimeInNumberOfTimeIncrement_.back())<=RefractoryTimeInTimeIncrement) //on regarde le temps ecoulé depuis le dernier spike
				{
					membranePotential_=RefractoryPotential;
				} 
				else
				{
					static random_device rd;
					static mt19937 gen(rd());
					poisson_distribution<> distribution (ExternalRandomSpikesFrequencyPerTimeStep_);
					int numberOfExternalSpike(distribution(gen));
					assert(numberOfExternalSpike>=0);
					double externalRandomPart(Je*(double)numberOfExternalSpike);
					
					double decayingPart(membranePotential_*R1);
					double externalCurrentPart(Iext_*R2);
					membranePotential_=decayingPart+externalCurrentPart+spikeRingBuffer_[currentIndex]+externalRandomPart;
				}
				localClock_+=1;
				//reset ring buffer slot
				spikeRingBuffer_[currentIndex]=0.0;
				}
			
			return spike;
		}
	
	double Neurone::getMembranePotential() const{
		return membranePotential_;
	}

	std::vector<int> Neurone::getSpikesTimeInNumberOfTimeIncrement() const{
		return SpikesTimeInNumberOfTimeIncrement_;
	}
	vector<unsigned int> Neurone::getConnections() const{
		return connections_;
	}
	void Neurone::setConnections (vector<unsigned int> const& connections){
		connections_=connections;
	}
	void Neurone::receive(int const& clockPlusDelay,double const& J){
		assert(clockPlusDelay>localClock_);
		size_t storageIndex(clockPlusDelay % spikeRingBuffer_.size());
		spikeRingBuffer_[storageIndex]+=J;
	}
	double Neurone::getJsentToPostSynapticNeurone() const{
		if(isExitatory_){return Je;}
		else{return-Ji;}
	}
