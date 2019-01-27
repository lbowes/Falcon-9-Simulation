#ifndef PHYSICS_SIMULATION_H
#define PHYSICS_SIMULATION_H
#pragma once

#include "Internal/Hardware/Falcon_9/F9.h"

#include <chrono/physics/ChSystemNSC.h>
#include <map>

/*
Currently working on finding out how to store the state of the simulation each timestep.
Stuff found so far that might be useful are:
- ChState class
- ChVariablesBody class
*/

namespace Physics {

	class Simulation {
	private:
		const double mDuration;

		const unsigned short 
			mUpdatesPerSec,
			mDataSnapsPerSec;

		chrono::ChSystemNSC mSystem;
		Hardware::F9 mFalcon9;

		std::map<const unsigned, const F9_DSS> mStateHistory;

	public:
		Simulation();
		~Simulation() = default;

		void run();
		const std::map<const unsigned, const F9_DSS>& getStateHistory() const { return mStateHistory; }
		double getSnapshotInterval_s() const { return 1.0 / mDataSnapsPerSec; }
		double getDuration() const { return mDuration; }

	private:
		bool terminationCondMet();
		void serialiseSnapshot(unsigned long snapshotNumber);

	};

}

#endif