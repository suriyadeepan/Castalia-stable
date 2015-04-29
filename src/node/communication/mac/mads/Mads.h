#ifndef _MADS_H_
#define _MADS_H_

#include <omnetpp.h>
#include "VirtualMac.h"
#include "VirtualMobilityManager.h"
#include "MadsPacket_m.h"

#include <vector>
#include <math.h>
#include "random"
 

using namespace std;

// ------- slot size ------- //
const double Mads_SLOT = 0.004;

enum Mads_PktType {
	DISC_REQ_PKT = 1,
	DISC_REP_PKT = 2,
	SCHED_PKT = 3,
	DATA_REQ_PKT = 4,
	DATA_REP_PKT = 5
};

// ------ NODE Type ------
enum Mads_NodeType { 
	CLUSTER_HEAD = 1,
	MOBILE_NODE = 2,
	BS = 3
};
// ----------------------

// ------ Timers --------
enum Mads_Timers {
	WAKE_TO_RX = 1,
	WAKE_TO_SLEEP = 2,

	WAKE_TO_DISC_REQ = 3,
	WAKE_TO_DISC_REP = 4,
	WAKE_TO_SCHED = 5,
	WAKE_TO_REC_SCHED = 6,
	WAKE_TO_DATA_PHASE = 7,
	WAKE_TO_SEND_DATA_REQ= 8,
	WAKE_TO_REC_DATA_REQ = 9,
	WAKE_TO_SEND_DATA_REP = 10,

	WAKE_TO_SEND_DISC_REP = 11

};
// ----------------------

enum Mads_PHASE {
	DISC_REQ_P = 1,
	DISC_REP_P = 2,
	SCHED_P = 3,
	DATA_P = 4,
	DATA_REQ_P = 5,
	DATA_REP_P = 6
};

enum Mads_PHASE_DURATION {
	DISC_REQ_D = 2,
	DISC_REP_D = 10,
	SCHED_D = 2,
	DATA_REQ_D = 1,
	DATA_REP_D = 1
};

int Mads_CntlPktCount = 0;
int Mads_DataPktCount = 0;
int Mads_DataPktRxCount = 0;

double Mads_EnergySpent = 0.0;


class Mads: public VirtualMac
{
	protected:
		void startup();
		void fromRadioLayer(cPacket *, double, double);
		void fromNetworkLayer(cPacket *, int);
		void timerFiredCallback(int);

		void sendPacket(MadsPacket*);

		void broadcastRequest();


		void broadcastDiscReq(double);
		void sendDiscRep(void);
		void broadcastSched(double);
		void sendDataReq(int,int,double);
		void sendDataRep(void);

		// --- Buffer Handline --- //
		bool safePushNode(int);

		// --- Mobility --- //
		void initMobManager();
		void getSelfLocation(int&, int&);

		// --- Energy Consumption --- //
		void initResManager();

		int nodeType;
		int x,y;

		int boundTo;
		int round;
		int phase;

		int myDrepSlot;

		bool newNodesJoined;

		int servicedNodes;

		int boundNodes[15]; //Holds the list of cluster members
		int boundNodesSize;

		VirtualMobilityManager *nodeMobilityModule; 
		ResourceManager *nodeResModule; 
};

#endif
