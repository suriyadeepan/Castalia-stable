/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2010                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Yuriy Tselishchev                                            *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *  
 ****************************************************************************/

#ifndef _MOBILITYMODULE_H_
#define _MOBILITYMODULE_H_

#include "MobilityManagerMessage_m.h"
#include "VirtualMobilityManager.h"

#include "random"

using namespace std;

class RandWpMobilityManager: public VirtualMobilityManager {
 private:
	/*--- The .ned file's parameters ---*/
	double updateInterval;
	double loc1_x;
	double loc1_y;
	double loc1_z;
	double loc2_x;
	double loc2_y;
	double loc2_z;
	double speed;

	double dx,dy;

	double theta;

	int xlim,ylim;

	/*--- Custom class parameters ---*/
	double incr_x;
	double incr_y;
	double incr_z;
	double distance;
	double tmp;

	double direction;

	bool sign;

 protected:
	void initialize();
	void handleMessage(cMessage * msg);
	double dist(double&,double&,double&,double&);
};

#endif
