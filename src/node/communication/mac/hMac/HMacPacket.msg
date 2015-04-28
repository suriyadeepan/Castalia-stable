cplusplus {{
	#include "MacPacket_m.h"
}}
class MacPacket;
packet HMacPacket extends MacPacket {

	int ptype; 

	int slots;
	int slot_info[10];
	int node_id[10];

	double sleep_time;
}


