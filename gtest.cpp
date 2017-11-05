#include "gtest/gtest.h"
#include "Network.hpp"
#include <vector>
using namespace std;

int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

TEST(test1Neurone,correctPotWithIext){
	Neurone n(0,1,true,1,0.0);
	cout<<"neurone with Iext=1 and no noise"<<endl;
	bool test1=n.update(1);
	EXPECT_EQ(n.getMembranePotential(),1*R2);
	bool spike=n.update(10000);
	EXPECT_FALSE(spike);
}

TEST(test1Neurone,SpikeAtACorrectTime){
	Neurone n(0,1.01,true,1,0.0);
	cout<<"neurone with Iext=1.01 and no noise"<<endl;;
	bool spike=n.update(3000);
	EXPECT_TRUE(spike);
	EXPECT_TRUE(n.getSpikesTimeInNumberOfTimeIncrement()[0]==924);
	EXPECT_TRUE(n.getSpikesTimeInNumberOfTimeIncrement()[1]==1732);
	EXPECT_TRUE(n.getSpikesTimeInNumberOfTimeIncrement()[2]==2540);
}

TEST(test1Neurone,receivePuttingCorrectValueAtCorrectIndix){
	Neurone n(0,0.0,true,1,0.0);
	n.receive(15,Je);
	n.receive(15,Je);
	EXPECT_TRUE(n.spikeRingBuffer_[15]==2*Je);
	n.update(16);
	EXPECT_TRUE(n.getMembranePotential()==2*Je);
	n.update(16);
	EXPECT_TRUE(n.spikeRingBuffer_[15]==0.0);
	EXPECT_TRUE(n.getMembranePotential()<2*Je);//normal decay : the buffer has been reset correctly
}

TEST(test2Neurons,correctConnection){
	Neurone n1(0,1,true,1);
	Neurone n2(0,1,true,2);
	std::vector<unsigned int> co(1,2);
	n1.setConnections(co);
	EXPECT_TRUE(n1.getConnections()[0]==2);
}


TEST(testNetwork,correctConstruction){
	Network network0 (0,1,1,0,0);
	EXPECT_TRUE((network0.neurones_).size()==0);
	Network network1 (2,1,1,0,0);
	cout<<"2 exitatory neurons with each other connected"<<endl;
	EXPECT_TRUE(network1.neurones_[0]->getConnections().size()==2);
	EXPECT_TRUE(network1.neurones_[1]->getConnections().size()==2);
	EXPECT_TRUE(network1.neurones_[0]->getJsentToPostSynapticNeurone()==Je);
	EXPECT_TRUE(network1.neurones_[1]->getJsentToPostSynapticNeurone()==Je);
	Network network2 (4,0.5,0.5,0.5,0);
	cout<<"2 exitatory and 2 inhibitory neurons each connected to one exitatory and one inhibitory"<<endl;
	EXPECT_TRUE(network2.neurones_[0]->getJsentToPostSynapticNeurone()==Je);//the first 2 neurons are exitatory
	EXPECT_TRUE(network2.neurones_[1]->getJsentToPostSynapticNeurone()==Je);
	EXPECT_TRUE(network2.neurones_[2]->getJsentToPostSynapticNeurone()==-Ji);
	EXPECT_TRUE(network2.neurones_[3]->getJsentToPostSynapticNeurone()==-Ji);
	EXPECT_TRUE(network2.neurones_[0]->getConnections().size()==2);
	EXPECT_TRUE(network2.neurones_[1]->getConnections().size()==2);
	EXPECT_TRUE(network2.neurones_[2]->getConnections().size()==2);
	EXPECT_TRUE(network2.neurones_[3]->getConnections().size()==2);
	if(network2.neurones_[(network2.neurones_[0]->getConnections()[0])]->getJsentToPostSynapticNeurone()==Je)//if the first neuron is exitatory
	{
		EXPECT_TRUE(network2.neurones_[(network2.neurones_[0]->getConnections()[1])]->getJsentToPostSynapticNeurone()==-Ji);
	}else {
		EXPECT_TRUE(network2.neurones_[(network2.neurones_[0]->getConnections()[1])]->getJsentToPostSynapticNeurone()==Je);
	}
	
	if(network2.neurones_[(network2.neurones_[2]->getConnections()[0])]->getJsentToPostSynapticNeurone()==Je)//if the first neuron is exitatory
	{
		EXPECT_TRUE(network2.neurones_[(network2.neurones_[2]->getConnections()[1])]->getJsentToPostSynapticNeurone()==-Ji);
	}else {
		EXPECT_TRUE(network2.neurones_[(network2.neurones_[2]->getConnections()[1])]->getJsentToPostSynapticNeurone()==Je);
	}
	
}
	//for further test we will see if the graph are correct 
