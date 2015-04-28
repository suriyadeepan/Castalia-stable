#ifndef _HMAC_H_
#define _HMAC_H_

#include <omnetpp.h>
#include "VirtualMac.h"
#include "VirtualMobilityManager.h"
#include "HMacPacket_m.h"

#include <vector>
#include <math.h>
#include "random"
 

using namespace std;

// ------- slot size ------- //
const double HMac_SLOT = 0.004;

enum HMac_PktType {
	SYNC_PKT = 1,
	REQ_PKT = 2,
	SCHED_PKT = 3,
	DATA_PKT = 4
};

// ------ NODE Type ------
enum HMac_NodeType { 
	CLUSTER_HEAD = 1,
	MOBILE_NODE = 2,
	BS = 3
};
// ----------------------

// ------ Timers --------
enum HMac_Timers {
	WAKE_TO_SYNC = 1,
	WAKE_TO_REQ = 2,
	WAKE_TO_SCHED = 3,
	WAKE_TO_DATA = 4,
	WAKE_TO_SEND_REQ = 5,
	WAKE_TO_REC_SCHED = 6,
	WAKE_TO_SEND_DATA = 7,
	WAKE_TO_RX = 8,
	WAKE_TO_SLEEP = 9
};
// ----------------------

enum HMac_PHASE {
	SYNC_P = 1,
	REQ_P = 2,
	SCHED_P = 3,
	DATA_P = 4,
};

enum HMac_PHASE_DURATION {
	SYNC_DURATION = 2,
	REQ_DURATION = 10,
	SCHED_DURATION = 2,
	DATA_DURATION = 10
};

int HMac_CntlPktCount = 0;
int HMac_DataPktCount = 0;
int HMac_DataPktRxCount = 0;

int CH_COUNT;
int MN_COUNT;

class HMac: public VirtualMac
{
	protected:
		void startup();
		void fromRadioLayer(cPacket *, double, double);
		void fromNetworkLayer(cPacket *, int);
		void timerFiredCallback(int);

		void sendPacket(HMacPacket*);

		void broadcastRequest();


		void broadcastSync(double);
		void sendReq(void);
		void broadcastSched(double);
		void sendData(void);

		// --- Mobility --- //
		void initMobManager();
		void getSelfLocation(int&, int&);

		int nodeType;
		int x,y;

		int myDataSlot;
		int myMetaSlot;

		int boundTo;
		int round;
		int phase;

		int boundNodes[10]; //Holds the list of Nodes who requested for connection
		int boundNodesSize;

		VirtualMobilityManager *nodeMobilityModule; 
};

#endif
