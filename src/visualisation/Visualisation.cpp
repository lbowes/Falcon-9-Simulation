#include "Visualisation.h"

#include <IMGUI/imgui.h>
#include <iostream>


Visualisation::Visualisation() {
    initIrrlicht();
    mGUI.initWith(*mDevice);

    mEventReceiver.addReceiver(&mHWInput);
    mEventReceiver.addReceiver(&mGUI.getEventReceiver());
}


void Visualisation::initIrrlicht() {
    using namespace irr;

    SIrrlichtCreationParameters params;
    params.DriverType = video::EDT_OPENGL;

    IrrlichtDevice* temp = createDevice(video::EDT_NULL);
    core::dimension2du monitorRes = temp->getVideoModeList()->getDesktopResolution();
    temp->drop();
    params.WindowSize = monitorRes / 2;

    params.Bits = 16;
    params.Fullscreen = false;
    params.Stencilbuffer = true;
    params.Vsync = true;
    params.EventReceiver = &mEventReceiver;

    mDevice = createDeviceEx(params);

    if(!mDevice) {
        printf("Error creating Irrlicht device\n");
        std::cin.get();
        return;
    }

    mDevice->setWindowCaption(L"Falcon 9 Simulation");

    mVidDriver = mDevice->getVideoDriver();
    mSceneMgr = mDevice->getSceneManager();
}


void Visualisation::run() {
    unsigned lastTime = mDevice->getTimer()->getRealTime();

    while(mDevice->run()) {
        const unsigned now = mDevice->getTimer()->getRealTime();
        const float frameTime_s = static_cast<float>(now - lastTime) / 1000.0f;

        mGUI.start();
        // handleInput(frameTime_s);
        // update(frameTime_s);
        render();

        lastTime = now;
    }
}


void Visualisation::render() {
    mVidDriver->beginScene(true, true, irr::video::SColor(255, 128, 128, 128));

    // mModel->render(mCameraSystem->getCurrentSimCamera().getPosition_world());
    mGUI.render();

    mVidDriver->endScene();
}
