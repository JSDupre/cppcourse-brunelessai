#include <cmath>

		//Constants obtained from the Brunel Paper
	const double SpikeThreshold(20); //!< the potential threshold before a neuron spike (in mV)
	const double Tau(20);//!< the membrane time constant (in ms)
	const double TimeIncrement(0.1);//!< our simulation time step (in ms)
	const double C(1.0);//!< a neuron caracteristic (in ms/ohm)
	const double STANDART_POTENTIAL(0.0);//!< the standart potential of our neuron (in mV)
	const double RefractoryTime(2);//!<the period during wich the neuron potential is insensitive to stimulation (in ms) 
	const double RefractoryPotential(10.0);//!< the membrane potential of the neuron in the refractory period (in mV)
	const int NumberOfExitatoryNeurone(10000);//!< the number of excitatory neurons in our network
	const int NumberOfInhibitoryNeurone(2500);//!< the number of inhibitory neurons in our network
	const double ProbabilityOfConnection(0.1);//!< the probability of connection with another neuron of the network
	const double g(3);//!< relative strength of inhibitory synapses over excitatory synapses (=Ji/Je) 
	const double D(1.5); //!< the delay between the reception of a spike and its integration in the calculus of the membrane potential(in ms)
	const double Je(0.1); //!< the potential of an arriving spike, the same for each exitatory connection for simplification
	const double Eta(2); //!< Nuext/NuThr, see Brunel's paper for more detailed information
	const double Iexterieur(0.0); //!< external current input from the outside of the brain
	
	//for graph procuction
	const int numberOfNeuronsToRecord(100);

		//Precomputation of constants depending the previous ones to avoid useless operation
	const double NeuroneResistance(Tau/C);
	const int RefractoryTimeInTimeIncrement(RefractoryTime/TimeIncrement);
	const int DelayInTimeIncrement(D/TimeIncrement);
	const double Ji(g*Je); //see Model
	const double NuExt((Eta*SpikeThreshold)/(Je*Tau)); //spikes*ms^-1, see Brunel paper
	const double NuExtTimeH (NuExt*TimeIncrement);
	const double R1(exp(-TimeIncrement/Tau));
	const double R2(NeuroneResistance*(1-exp(-TimeIncrement/Tau)));
	const int Ce(NumberOfExitatoryNeurone*ProbabilityOfConnection);
	const int Ci(NumberOfInhibitoryNeurone*ProbabilityOfConnection);
	const int TOTAL_NUMBER_OF_NEURONES(NumberOfExitatoryNeurone+NumberOfInhibitoryNeurone);
	const double NumberOfExitatoryNeuroneInDouble(NumberOfExitatoryNeurone);
	const double NumberOfInhibitoryNeuroneInDouble(NumberOfInhibitoryNeurone);
	const double EXITATORY_PROPORTION(NumberOfExitatoryNeuroneInDouble/(NumberOfExitatoryNeuroneInDouble+NumberOfInhibitoryNeuroneInDouble));

	
	
	
	

