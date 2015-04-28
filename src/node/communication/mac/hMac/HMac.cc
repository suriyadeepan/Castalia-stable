#include "HMac.h"

Define_Module(HMac);

void HMac::startup(){

	round = 0;
	boundTo = -1;
	boundNodesSize = 0;

	HMac_DataPktRxCount = 0;
	HMac_DataPktCount = 0;
	HMac_CntlPktCount = 0;

	trace() << "NODE:" << SELF_MAC_ADDRESS << " startup()";

	nodeType = par("nodeType");
	CH_COUNT = par("chCount");
	MN_COUNT = par("mnCount");

	initMobManager();

	// --- if CH : SYNC_P; else RX --- //
	if(nodeType == CLUSTER_HEAD)
		setTimer(WAKE_TO_SYNC, 0.8);
	else
		toRadioLayer(createRadioCommand(SET_STATE, RX));
}

void HMac::fromNetworkLayer(cPacket * pkt, int destination){ }


void HMac::fromRadioLayer(cPacket * pkt, double rssi, double lqi){

	HMacPacket *rpkt = dynamic_cast <HMacPacket*>(pkt);

	switch(rpkt->getPtype()){

		case SYNC_PKT: // --------- SYNC PKT ---------- //
			if( rssi > -90 && nodeType == MOBILE_NODE ){
				boundTo = rpkt->getSource();
				myMetaSlot = rand() % 10;
				setTimer(WAKE_TO_REC_SCHED, (REQ_DURATION * HMac_SLOT) + rpkt->getSleep_time() - (HMac_SLOT * 0.5));
				//trace() << "To Wake receive SCHED @" << simTime().dbl() + (REQ_DURATION*HMac_SLOT) + rpkt->getSleep_time();
				setTimer(WAKE_TO_SEND_REQ,(myMetaSlot * HMac_SLOT) + rpkt->getSleep_time());
				toRadioLayer(createRadioCommand(SET_STATE,SLEEP));
				trace() << "Received SYNC_PKT from " << boundTo;
			}
			else
				return;
			break; // ------------------------------- //

		case REQ_PKT: // ---------- REQ PKT ---------- //
			if(nodeType == CLUSTER_HEAD && phase == REQ_P && rpkt->getDestination() == SELF_MAC_ADDRESS && rssi > -90){
				trace() << "Received REQ_PKT from " << rpkt->getSource();
				boundNodes[boundNodesSize++] = rpkt->getSource();
			}
			else
				return;
			break; // ------------------------------- //

		case SCHED_PKT: // --------- SCHED PKT ---------- //
			if(nodeType == MOBILE_NODE && rpkt->getSource() == boundTo && rssi > -90){
				trace() << "Received SCHED_PKT from " << boundTo;
				for(int i=0;i<rpkt->getSlots();i++)
					if(rpkt->getNode_id(i) == SELF_MAC_ADDRESS){
						setTimer(WAKE_TO_RX,(rpkt->getSlots() * HMac_SLOT) + rpkt->getSleep_time());
						setTimer(WAKE_TO_SEND_DATA, (i * HMac_SLOT) + rpkt->getSleep_time());
						toRadioLayer(createRadioCommand(SET_STATE,SLEEP));
					}
			}
			else
				return;
			break; // ------------------------------- //

		case DATA_PKT: // ---------- DATA PKT ---------- //
			if(nodeType == CLUSTER_HEAD && phase == DATA_P && rpkt->getDestination() == SELF_MAC_ADDRESS){
				trace() << "Received DATA_PKT from " << rpkt->getSource();
				HMac_DataPktRxCount++;
			}
			else
				return;
			break; // ------------------------------- //


		default:
			break;

	}
}



void HMac::timerFiredCallback(int timer) {


	switch(timer){

		case WAKE_TO_SLEEP:
			toRadioLayer(createRadioCommand(SET_STATE, SLEEP));
			break;

		case WAKE_TO_RX:
			toRadioLayer(createRadioCommand(SET_STATE, RX));
			break;


	// ==--------------------- CH TIMERS ------------------------== //
		case WAKE_TO_SYNC:
			trace() << "WAKE_TO_SYNC";
			phase = SYNC_P;
			setTimer(WAKE_TO_REQ,SYNC_DURATION*HMac_SLOT);
			trace() << "STAT> Round:" << ++round;
			trace() << "STAT> DataPkts:" << HMac_DataPktCount;
			trace() << "STAT> DataPktsRx:" << HMac_DataPktRxCount;
			trace() << "STAT> PDR:" << 100 * (double)HMac_DataPktRxCount/(double)HMac_DataPktCount << "%";
			trace() << "STAT> ThroughPut:" << 100 * (double)HMac_DataPktRxCount/(double)(25 * round) << "%";
			trace() << "STAT> CntPkts:" << HMac_CntlPktCount;
			trace() << "STAT> CntPkts/DataPkt:" << (double)HMac_CntlPktCount/(double)HMac_DataPktCount;
			boundNodesSize = 0;
			broadcastSync(getTimer(WAKE_TO_REQ).dbl() - simTime().dbl() );
			break;

		case WAKE_TO_REQ:
			trace() << "WAKE_TO_REQ";
			phase = REQ_P;
			setTimer(WAKE_TO_SCHED,REQ_DURATION*HMac_SLOT);
			break;

		case WAKE_TO_SCHED:
			trace() << "WAKE_TO_SCHED";
			phase = SCHED_P;
			setTimer(WAKE_TO_DATA,SCHED_DURATION*HMac_SLOT);
			if(boundNodesSize > 0)
				broadcastSched(getTimer(WAKE_TO_DATA).dbl() - simTime().dbl() );
			break;

		case WAKE_TO_DATA:
			trace() << "WAKE_TO_DATA";
			phase = DATA_P;
			setTimer(WAKE_TO_SYNC,(boundNodesSize+3)*HMac_SLOT);
			break;
	// --------------------- END OF CH TIMERS --------------------- //



	// =============---------- MN TIMERS ----------================ //
		case WAKE_TO_SEND_REQ:
			trace() << "WAKE_TO_SEND_REQ";
			sendReq();
			setTimer(WAKE_TO_SLEEP,HMac_SLOT*0.1);
			break;

		case WAKE_TO_REC_SCHED:
			trace() << "WAKE_TO_REC_SCHED";
			toRadioLayer(createRadioCommand(SET_STATE,RX));
			break;

		case WAKE_TO_SEND_DATA:
			trace() << "WAKE_TO_SEND_DATA";
			sendData();
			setTimer(WAKE_TO_SLEEP,HMac_SLOT*0.1);
			break;
	// --------------------- END OF MN TIMERS --------------------- //
	}

}


void HMac::sendPacket(HMacPacket *packet) {

	packet->setSource(SELF_MAC_ADDRESS);
	toRadioLayer(packet);
	toRadioLayer(createRadioCommand(SET_STATE, TX));
}


void HMac::initMobManager(){
	nodeMobilityModule = check_and_cast<VirtualMobilityManager*>(getParentModule()->getParentModule()->getParentModule()->getSubmodule("node",SELF_MAC_ADDRESS)->getSubmodule("MobilityManager"));
}

void HMac::getSelfLocation(int& x, int& y){
	x = nodeMobilityModule->getLocation().x;
	y = nodeMobilityModule->getLocation().y;
}







// ==============---------- Message Passing Functions ----------=============== //
void HMac::sendReq(){

	HMac_CntlPktCount++;
	HMacPacket *reqPkt;
	reqPkt = new HMacPacket("Request Packet", MAC_LAYER_PACKET);
	reqPkt->setSource(SELF_MAC_ADDRESS);
	reqPkt->setDestination(boundTo);
	reqPkt->setPtype(REQ_PKT);
	sendPacket(reqPkt);
}

void HMac::sendData(){

	HMac_DataPktCount++;
	HMacPacket *dataPkt;
	dataPkt = new HMacPacket("Data Packet", MAC_LAYER_PACKET);
	dataPkt->setDestination(boundTo);
	dataPkt->setPtype(DATA_PKT);
	sendPacket(dataPkt);
}

void HMac::broadcastSched(double sleep_t){

	HMac_CntlPktCount++;
	HMacPacket *schedPkt;
	schedPkt = new HMacPacket("Schedule Packet", MAC_LAYER_PACKET);

	schedPkt->setDestination(BROADCAST_MAC_ADDRESS);
	schedPkt->setPtype(SCHED_PKT);

	schedPkt->setSlots(boundNodesSize);
	schedPkt->setSleep_time(sleep_t);

	trace() << "||||||------------_____________ SCHEDULE ____________-------------||||||";
	for(int i=0;i<boundNodesSize;i++){
		schedPkt->setNode_id(i,boundNodes[i]);
		trace() << "[" << i << "] " << boundNodes[i];
	}
	trace() << " ---------------------------------------------------------------------- ";

	sendPacket(schedPkt);
}

void HMac::broadcastSync(double sleep_t){

	HMac_CntlPktCount++;
	HMacPacket *syncPacket;
	syncPacket = new HMacPacket("Synchronization Packet", MAC_LAYER_PACKET);
	syncPacket->setDestination(BROADCAST_MAC_ADDRESS);
	syncPacket->setPtype(SYNC_PKT);
	syncPacket->setSleep_time(sleep_t);
	sendPacket(syncPacket);
}

// ---------------------------------------------------------------------- //













