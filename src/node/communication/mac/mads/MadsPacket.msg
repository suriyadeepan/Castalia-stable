cplusplus {{
	#include "MacPacket_m.h"
}}
class MacPacket;
packet MadsPacket extends MacPacket {
	int ptype; 

	int slots;
	int node_id[10];
	int nextSlot;

	int clusterSize;

	double sleep_time;
}


