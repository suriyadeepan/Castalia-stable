
#include "RandWpMobilityManager.h"

Define_Module(RandWpMobilityManager);

void RandWpMobilityManager::initialize()
{
	VirtualMobilityManager::initialize();

	updateInterval = par("updateInterval");
	updateInterval = updateInterval / 1000;

	loc1_x = nodeLocation.x;
	loc1_y = nodeLocation.y;
	loc1_z = nodeLocation.z;

	xlim = par("xLimit");
	ylim = par("yLimit");
	speed = par("speed");

	loc1_z = 0;
	loc2_z = 0;

	// calculate destination
	loc2_x = rand() % xlim;
	loc2_y = rand() % ylim;

	trace() << "Chosen Destination : (" << loc2_x << "," << loc2_y << ")";

	distance = sqrt(pow(loc1_x - loc2_x, 2) + pow(loc1_y - loc2_y, 2) );
		 
	direction = 1;
	if (speed > 0 && distance > 0) {
		tmp = (distance / speed) / updateInterval;
		//incr_x = (loc2_x - loc1_x) / tmp;
		//incr_y = (loc2_y - loc1_y) / tmp;
		incr_z = 0;

		incr_x = speed * updateInterval;
		incr_y = incr_x;
	
		dx = (loc2_x - loc1_x)/tmp;//definir le pas de X
		dy = (loc2_y - loc1_y)/tmp;// definir le pas de y	

		if(dx != 0)
			direction =  atan2(dy,dx);
		else
			direction = 1.571428571;

		trace() << "direction : " << direction;

		setLocation(loc1_x, loc1_y, loc1_z);
		scheduleAt(simTime() + updateInterval,
			new MobilityManagerMessage("Periodic location update message", MOBILITY_PERIODIC));
	}
}

double RandWpMobilityManager::dist(double& loc1_x,double& loc1_y,double& loc2_x,double& loc2_y)
{ return sqrt(pow(loc1_x - loc2_x, 2) + pow(loc1_y - loc2_y, 2) ); }


void RandWpMobilityManager::handleMessage(cMessage * msg)
{
	int msgKind = msg->getKind();
	switch (msgKind) {

		case MOBILITY_PERIODIC:{

   			distance = dist(nodeLocation.x,nodeLocation.y,loc2_x,loc2_y); 

				if(distance > 5 && nodeLocation.x <= xlim && nodeLocation.y <= ylim && nodeLocation.x >= 0 && nodeLocation.y >= 0 ){

					trace() << "x_inc = " << incr_x << " * " << cos(direction);
					trace() << "y_inc = " << incr_y << " * " << sin(direction);
					nodeLocation.x += incr_x * cos(direction);
					nodeLocation.y += incr_y * sin(direction);
					nodeLocation.z += incr_z;
				}
				else{

					// calculate destination
					loc2_x = rand() % xlim;
					loc2_y = rand() % ylim;
					trace() << "Chosen Destination : (" << loc2_x << "," << loc2_y << ")";

					dx = (loc2_x - nodeLocation.x)/tmp;//definir le pas de X
					dy = (loc2_y - nodeLocation.y)/tmp;// definir le pas de y	

					if(dx != 0)
						direction =  atan2(dy,dx);
					else
						direction = 1.571428571;

					trace() << "New Direction : " << direction;
					trace() << "cos: " << cos(direction);
					trace() << "sin: " << sin(direction);

				}

				

			notifyWirelessChannel();
			scheduleAt(simTime() + updateInterval,
				new MobilityManagerMessage("Periodic location update message", MOBILITY_PERIODIC));

			trace() << "changed location(x:y:z) to " << (int)nodeLocation.x << 
					":" << (int)nodeLocation.y << ":" << (int)nodeLocation.z;
			break;
		}

		default:{
			trace() << "WARNING: Unexpected message " << msgKind;
		}
	}

	delete msg;
	msg = NULL;
}

