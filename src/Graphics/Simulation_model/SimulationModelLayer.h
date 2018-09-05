#ifndef GRAPHICS_SIMULATIONMODELLAYER_H
#define GRAPHICS_SIMULATIONMODELLAYER_H
#pragma once

#include "Models/F9S1Model.h"
#include "Models/F9S2Model.h"
#include "Models/ASDSModel.h"
#include "Models/EarthModel.h"
#include "Models/ExhaustJet.h"
#include "Cameras/CameraSystem.h"

#include <GraphicsFramework/Renderer.h>
#include <GraphicsFramework/SkyBox.h>

namespace Graphics {
	
	class SimulationModelLayer {
	private:
		GF::Graphics::Renderer
			mSolidRenderer,
			mWireframeRenderer;

		GF::ResourceSet mResourceBucket;
		Physics::Hardware::Falcon9& mDataSource;
		
		std::unique_ptr<F9S1Model> mF9S1Model;
		std::unique_ptr<F9S2Model> mF9S2Model;
		std::unique_ptr<ASDSModel> mASDSModel;
		std::unique_ptr<EarthModel> mEarthModel;

		std::vector<std::unique_ptr<ExhaustJet>> mStage1Exhausts;

		CameraSystem mCameras;

	public:
		SimulationModelLayer(Physics::Hardware::Falcon9& simDataSource, float startWindowAspect);
		~SimulationModelLayer() = default;

		void render(float windowAspect, float dt);
		void checkInput(float dt, glm::vec2 windowDimensions);

		const CameraSystem& getCameraSystem() const { return mCameras; }

	private:
		void load();
		void flushRenderers();

	};

}

#endif
