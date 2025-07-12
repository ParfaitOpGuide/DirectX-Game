#pragma once
class ViewportUIManager
{
public:
	static ViewportUIManager* getInstance();

	void OnUpdate();
	int getViewCameraNum(int viewNumber);
	bool getPerspectiveCameraBool(int viewNumber); 
	bool getWireframeCameraBool(int viewNumber);

private:
	int view1CameraNum = 0;
	int view2CameraNum = 2;
	int view3CameraNum = 4;

	bool perspectiveCameraView[3] = { false, true, false };
	bool wireframeCameraView[3] = { false, false, true };
	static ViewportUIManager *sharedInstance;
	ViewportUIManager();
	~ViewportUIManager();
	ViewportUIManager(ViewportUIManager const&) {};
	ViewportUIManager& operator=(ViewportUIManager const&) {};
};

