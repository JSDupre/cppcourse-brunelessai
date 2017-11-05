#include <vector>
#include "Constants.hpp"
#include "gtest/gtest_prod.h"

#ifndef NEURONE_H
#define NEURONE_H

/**
 * class for a neuron
 */
class Neurone {
	private:
	
	unsigned int neurone_ID_;	//!< the neuron ID in the network
	double membranePotential_; //!< the neuron membrane potential (in mV)
	std::vector<int> SpikesTimeInNumberOfTimeIncrement_; //!< the neuron spikes' times (in number of since the beginning of the simulation)
	int localClock_;                                     //!< local clock for the neurone (can be incremented before the global simulation clock)
	std::vector<unsigned int> connections_;               //!< indices of the post-synaptic neurons the neuron is connected to 
	std::vector<double> spikeRingBuffer_;		     //!< ring buffer used to store the arriving spikes from pre-synaptic neurons in order to compute them after a certain delay
	double Iext_;					     //!< Intensity comming from the outside of the brain
	bool isExitatory_;				//!< type of the neuron : true if the neuron is excitatory and flase if the neuron is inhibitory
	double ExternalRandomSpikesFrequencyPerTimeStep_; //!< the external random spikes frequency per time step (=NuExtTimeH in default but can be set to 0 for unit testing)
	FRIEND_TEST(test1Neurone,receivePuttingCorrectValueAtCorrectIndix); //unit testing
	
	public:
	/** \brief construct a neuron
	 * 
	 * @param clock local clock for the neuron
	 * @param Iext intensity comming from the outside of the brain
	 * @param isExitatory boolean true if the neuron is excitatory false if inhibitory
	 * @param neuroneID the neuron ID
	 * @param ExternalRandomSpikesFrequencyPerTimeStep the external random spikes frequency per time step (=NuExtTimeH in default but can be set to 0 for unit testing of neuron without noise)
	 */
	Neurone (int const& clock,double const& Iext,bool const& isExitatory,unsigned int const& neuroneID,double const& ExternalRandomSpikesFrequencyPerTimeStep=NuExtTimeH);
	
	/** \brief update a neuron for a certain number of time step return true if the neuron has spiked during the update
	 * 
	 * @param NumberOfTimeIncrement the number of time step during wich the neuron has to be updated
	 */
	bool update(unsigned int const& NumberOfTimeIncrement);
	
	/** \brief return the membrane potential
	 */
	double getMembranePotential() const;
	
	/** \brief return the neuron's spikes' times (in number of since the beginning of the simulation) in a vector
	 */
	std::vector<int> getSpikesTimeInNumberOfTimeIncrement() const;
	
	/** \brief return the neuron's connections (ID of the post synaptic neurons)
	 */
	std::vector<unsigned int> getConnections() const;
	
	/** \brief set the neuron's connections (ID of the postsynaptic neurons)
	 */
	void setConnections (std::vector<unsigned int> const& connections);
	
	/** \brief store a receiving spike from a pre synaptic neuron 
	 * it will be computed in the calculus of the membrane potential after a certain delay
	 * 
	 * @param clockPlusDelay the time (in number of time increment) at which the arriving spike must be computed
	 * @param J potential of the arriving spike
	 */
	void receive(int const& clockPlusDelay,double const& J);
	
	/** \brief return the eletric potential (mV) sent to postsynaptic neuron, either Je if isExitatory==true or -Ji if isExitatory==false 
	 */
	double getJsentToPostSynapticNeurone() const;
};

#endif
