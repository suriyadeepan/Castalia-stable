package node.communication.mac.hMac;

simple HMac like node.communication.mac.iMac {
 parameters:
	bool collectTraceInfo = default (false);
	int macMaxPacketSize = default (0);		//RobustMac does not limit packet size
	int macPacketOverhead = default (8);	//only 2 fields are added in simple MAC frame, 8 bytes in total
	int macBufferSize = default (0);		//RobustMac does not use buffers
	int nodeType = default (2);				//2 = MOBILE NODE,  1 CLUSTER HEAD, 3 STATIC NDOE, 4 BASE STATION

	int chCount = default (25);
	int mnCount = default (25);
 gates:
	output toNetworkModule;
	output toRadioModule;
	input fromNetworkModule;
	input fromRadioModule;
	input fromCommModuleResourceMgr;
}

