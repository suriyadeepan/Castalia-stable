package node.mobilityManager.randWpMobilityManager;

simple RandWpMobilityManager like node.mobilityManager.iMobilityManager {
 parameters:
	bool collectTraceInfo = default (false);
	double updateInterval = default (100);
	double xLimit = default (0);
	double yLimit = default (0);
	double speed = default (50);
}
