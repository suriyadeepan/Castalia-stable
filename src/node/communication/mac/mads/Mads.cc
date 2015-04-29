#include "Mads.h"

Define_Module(Mads);

void Mads::startup(){

	round = 0;
	boundTo = -1;

	Mads_CntlPktCount = 0;
	Mads_DataPktCount = 0;
	Mads_DataPktRxCount = 0;

	trace() << "NODE:" << SELF_MAC_ADDRESS << " startup()";

	nodeType = par("nodeType");

	initMobManager();
	initResManager();

	// --- if CH : SYNC_P; else RX --- //
	if(nodeType == CLUSTER_HEAD)
		setTimer(WAKE_TO_DISC_REQ, 0.8);
	else
		toRadioLayer(createRadioCommand(SET_STATE, RX));
}

void Mads::fromNetworkLayer(cPacket * pkt, int destination){ }

bool Mads::safePushNode(int node_id){

	if(boundNodesSize > 14)
		return false;

	for(int i=0;i<boundNodesSize;i++)
		if(boundNodes[i] == node_id)
			return false;

	boundNodes[boundNodesSize++] = node_id;
	return true;
}

void Mads::fromRadioLayer(cPacket * pkt, double rssi, double lqi){

	MadsPacket *rpkt = dynamic_cast <MadsPacket*>(pkt);

	switch(rpkt->getPtype()){

		case DISC_REQ_PKT:
			if(nodeType == MOBILE_NODE && rssi > -90 && rpkt->getClusterSize() < 10){
				boundTo = rpkt->getSource();
				trace() << "Received DISC_REQ_PKT from " << boundTo;
				myDrepSlot = rand() % 10;
				setTimer(WAKE_TO_REC_SCHED, (DISC_REP_D   * Mads_SLOT) + rpkt->getSleep_time() - (Mads_SLOT * 0.5));
				setTimer(WAKE_TO_SEND_DISC_REP,(myDrepSlot * Mads_SLOT) + rpkt->getSleep_time());
				toRadioLayer(createRadioCommand(SET_STATE,SLEEP));
			}
			break;

		case DISC_REP_PKT:
			if(nodeType == CLUSTER_HEAD && rssi > -90 && rpkt->getDestination() == SELF_MAC_ADDRESS){
				if(safePushNode(rpkt->getSource()))
					newNodesJoined = true;
				trace() << "Received DISC_REP_PKT from " << rpkt->getSource();
			}
			break;

		case SCHED_PKT:
			if(nodeType == MOBILE_NODE && rssi > -90 && rpkt->getSource() == boundTo){
				trace() << "Received SCHED_PKT from " << boundTo;

				for(int i=0;i<rpkt->getSlots();i++)
					if(rpkt->getNode_id(i) == SELF_MAC_ADDRESS){
						setTimer(WAKE_TO_REC_DATA_REQ, (i * 2 * Mads_SLOT) + rpkt->getSleep_time() + 0.008);
						trace() << "I should wake up for DATA_REQ @" << simTime().dbl() + (i * Mads_SLOT) + rpkt->getSleep_time(); 
						toRadioLayer(createRadioCommand(SET_STATE,SLEEP));
					}
			}
			break;

		case DATA_REQ_PKT:
			if(nodeType == MOBILE_NODE && rpkt->getSource() == boundTo && rpkt->getDestination() == SELF_MAC_ADDRESS){
				trace() << "Received DATA_REQ_PKT from " << boundTo;
				setTimer(WAKE_TO_REC_DATA_REQ,  Mads_SLOT * rpkt->getNextSlot() - 0.0004);
				setTimer(WAKE_TO_SEND_DATA_REP, Mads_SLOT * 0.2);
			}

		case DATA_REP_PKT:
			if(nodeType == CLUSTER_HEAD && rpkt->getDestination() == SELF_MAC_ADDRESS){
				trace() << "Received DATA_REP_PKT from " << rpkt->getSource();
				Mads_DataPktRxCount++;
			}


		default:
			break;
	}

	return;
}

void Mads::timerFiredCallback(int timer) {


	switch(timer){

		case WAKE_TO_SLEEP:
			toRadioLayer(createRadioCommand(SET_STATE, SLEEP));
			break;

		case WAKE_TO_RX:
			toRadioLayer(createRadioCommand(SET_STATE, RX));
			break;

	// ------------------ CLUSTER_HEAD TIMERS ------------------- //
	
		case WAKE_TO_DISC_REQ:
			trace() << "WAKE_TO_DISC_REQ";
			phase = DISC_REQ_P;
			setTimer(WAKE_TO_DISC_REP,DISC_REQ_D * Mads_SLOT);
			trace() << "STAT> Round:" << ++round;
			trace() << "STAT> DataPkts:" << Mads_DataPktCount;
			trace() << "STAT> DataPktsRx:" << Mads_DataPktRxCount;
			trace() << "STAT> PDR:" << 100 * (double)Mads_DataPktRxCount/(double)Mads_DataPktCount << "%";
			trace() << "STAT> ThroughPut:" << 100 * (double)Mads_DataPktRxCount/(double)(5 * round) << "%";
			trace() << "STAT> CntPkts:" << Mads_CntlPktCount;
			trace() << "STAT> CntPkts/DataPkt:" << (double)Mads_CntlPktCount/(double)Mads_DataPktCount;
			//trace() << "STAT> EnergySpent:" << Mads_EnergySpent;
			broadcastDiscReq(getTimer(WAKE_TO_DISC_REP).dbl() - simTime().dbl());
			break;

		case WAKE_TO_DISC_REP:
			trace() << "WAKE_TO_DISC_REP";
			phase = DISC_REP_P;
			setTimer(WAKE_TO_SCHED,DISC_REP_D * Mads_SLOT);
			break;

		case WAKE_TO_SCHED:
			trace() << "WAKE_TO_SCHED";
			phase = SCHED_P;
			setTimer(WAKE_TO_DATA_PHASE,SCHED_D * Mads_SLOT);
			if(boundNodesSize > 0 && newNodesJoined){
				broadcastSched(getTimer(WAKE_TO_DATA_PHASE).dbl() - simTime().dbl());
				newNodesJoined = false;
			}
			break;

		case WAKE_TO_DATA_PHASE:
			trace() << "WAKE_TO_DATA_PHASE";
			phase = DATA_P;
			servicedNodes = 0;
			setTimer(WAKE_TO_DISC_REQ, ( (boundNodesSize*2) + 1) * Mads_SLOT);
			setTimer(WAKE_TO_SEND_DATA_REQ,Mads_SLOT*0.1);
			break;

		case WAKE_TO_SEND_DATA_REQ:
			phase = DATA_REQ_P;
			if(servicedNodes == boundNodesSize)
				break;
			else{
				trace() << "WAKE_TO_SEND_DATA_REQ to " << boundNodes[servicedNodes];
				setTimer(WAKE_TO_SEND_DATA_REQ,2*Mads_SLOT);
				// --- Prototype : sendDataReq(node_id,nextSlot,time_val); --- //
				sendDataReq(boundNodes[servicedNodes], 15 + (2*boundNodesSize),getTimer(WAKE_TO_SEND_DATA_REQ).dbl() - simTime().dbl());
				servicedNodes++;
			}
			break;
	
	
	// --------------------------------------------------------- //

	
	// ------========== MOBILE_NODE TIMERS =========----------- //
	
		case WAKE_TO_SEND_DISC_REP:
			trace() << "WAKE_TO_SEND_DISC_REP";
			sendDiscRep();
			setTimer(WAKE_TO_SLEEP,Mads_SLOT*0.1);
			break;

		case WAKE_TO_REC_SCHED:
			trace() << "WAKE_TO_REC_SCHED";
			toRadioLayer(createRadioCommand(SET_STATE,RX));
			break;

		case WAKE_TO_REC_DATA_REQ:
			trace() << "WAKE_TO_REC_DATA_REQ";
			toRadioLayer(createRadioCommand(SET_STATE,RX));
			break;

		case WAKE_TO_SEND_DATA_REP:
			trace() << "WAKE_TO_SEND_DATA_REP";
			sendDataRep();
			setTimer(WAKE_TO_SLEEP,Mads_SLOT*0.1);
			break;


	// ------------------------------------------------------ //
	
	}

}


// ---------------------- Message Transfer ------------------------------------- //
void Mads::sendPacket(MadsPacket *packet) {

	packet->setSource(SELF_MAC_ADDRESS);
	toRadioLayer(packet);
	toRadioLayer(createRadioCommand(SET_STATE, TX));
}

void Mads::sendDiscRep(){

	Mads_CntlPktCount++;
	MadsPacket *reqPkt;
	reqPkt = new MadsPacket("Request Packet", MAC_LAYER_PACKET);
	reqPkt->setDestination(boundTo);
	reqPkt->setPtype(DISC_REP_PKT);
	sendPacket(reqPkt);
}

void Mads::sendDataReq(int node_id, int next_slot, double time_val){

	Mads_CntlPktCount++;
	MadsPacket *dataPkt;
	dataPkt = new MadsPacket("Data Request Packet", MAC_LAYER_PACKET);
	dataPkt->setDestination(node_id);
	dataPkt->setPtype(DATA_REQ_PKT);
	dataPkt->setNextSlot(next_slot);
	dataPkt->setSleep_time(time_val);
	sendPacket(dataPkt);
}


void Mads::sendDataRep(){

	Mads_DataPktCount++;
	MadsPacket *dataPkt;
	dataPkt = new MadsPacket("Data Reply Packet", MAC_LAYER_PACKET);
	dataPkt->setDestination(boundTo);
	dataPkt->setPtype(DATA_REP_PKT);
	sendPacket(dataPkt);
}

void Mads::broadcastSched(double sleep_t){

	Mads_CntlPktCount++;
	MadsPacket *schedPkt;
	schedPkt = new MadsPacket("Schedule Packet", MAC_LAYER_PACKET);

	schedPkt->setDestination(BROADCAST_MAC_ADDRESS);
	schedPkt->setPtype(SCHED_PKT);

	schedPkt->setSlots(boundNodesSize);

	trace() << "---------------- SCHED -----------------";
	for(int i=0;i<boundNodesSize;i++){
		schedPkt->setNode_id(i,boundNodes[i]);
		trace() << "[" << i << "] " << boundNodes[i];
	}
	trace() << "----------------------------------------";

	sendPacket(schedPkt);
}

void Mads::broadcastDiscReq(double sleep_t){

	Mads_CntlPktCount++;
	MadsPacket *syncPacket;
	syncPacket = new MadsPacket("Discovery Request Packet", MAC_LAYER_PACKET);
	syncPacket->setDestination(BROADCAST_MAC_ADDRESS);
	syncPacket->setPtype(DISC_REQ_PKT);
	syncPacket->setSleep_time(sleep_t);
	syncPacket->setClusterSize(boundNodesSize);
	sendPacket(syncPacket);
}
// ------------------------------------------------------------------------------- //


void Mads::initMobManager(){ nodeMobilityModule = check_and_cast<VirtualMobilityManager*>(getParentModule()->getParentModule()->getParentModule()->getSubmodule("node",SELF_MAC_ADDRESS)->getSubmodule("MobilityManager")); }

void Mads::getSelfLocation(int& x, int& y){
	x = nodeMobilityModule->getLocation().x;
	y = nodeMobilityModule->getLocation().y;
}

// ----------- Resource Manager -------------- //
void Mads::initResManager(){ nodeResModule = check_and_cast<ResourceManager*>(getParentModule()->getParentModule()->getParentModule()->getSubmodule("node",SELF_MAC_ADDRESS)->getSubmodule("ResourceManager")); }


