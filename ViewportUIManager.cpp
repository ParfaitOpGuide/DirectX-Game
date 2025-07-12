#include "ViewportUIManager.h"
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
ViewportUIManager* ViewportUIManager::sharedInstance = nullptr;

ViewportUIManager* ViewportUIManager::getInstance()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new ViewportUIManager();
	}
	return sharedInstance;
}

ViewportUIManager::ViewportUIManager()
{

}

ViewportUIManager::~ViewportUIManager()
{
	delete sharedInstance;
}

void ViewportUIManager::OnUpdate()
{
	static bool truth = true;
	static bool menuOpen[3] = { false, false, false };

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Viewports")) {
			if (ImGui::MenuItem("Viewport 1")) menuOpen[0] = true;
			if (ImGui::MenuItem("Viewport 2")) menuOpen[1] = true; //does nothing yet
			if (ImGui::MenuItem("Viewport 3")) menuOpen[2] = true; //does nothing yet
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	};

	if (menuOpen[0])
	{
		ImGui::Begin("Viewport 1", &menuOpen[0], ImGuiWindowFlags_AlwaysAutoResize);
		if (view1CameraNum == 1)
			ImGui::Text("Current View: Top-Down");
		else if (!wireframeCameraView[0] && !perspectiveCameraView[0])
			ImGui::Text("Current View: Lit View");
		else if (perspectiveCameraView[0])
			ImGui::Text("Current View: Perspective View");
		else
			ImGui::Text("Current View: Wireframe View");

		if (ImGui::Button("Lit View"))
		{
			view1CameraNum = 0;
			perspectiveCameraView[0] = false;
			wireframeCameraView[0] = false;
		}
		if (ImGui::Button("Perspective View"))
		{
			view1CameraNum = 0;
			perspectiveCameraView[0] = true;
			wireframeCameraView[0] = false;
		}
		if (ImGui::Button("Wireframe View"))
		{
			view1CameraNum = 0;
			perspectiveCameraView[0] = true;
			wireframeCameraView[0] = true;
		}
		if (ImGui::Button("Top-Down View"))
			view1CameraNum = 1;
		ImGui::End();
	}

	if (menuOpen[1])
	{
		ImGui::Begin("Viewport 2", &menuOpen[1], ImGuiWindowFlags_AlwaysAutoResize);
		if (view2CameraNum == 3)
			ImGui::Text("Current View: Top-Down");
		else if (wireframeCameraView[1] && perspectiveCameraView[1])
			ImGui::Text("Current View: Wireframe View");
		else if (perspectiveCameraView[1])
			ImGui::Text("Current View: Perspective View");
		else
			ImGui::Text("Current View: Lit View");

		if (ImGui::Button("Lit View"))
		{
			view2CameraNum = 2;
			perspectiveCameraView[1] = false;
			wireframeCameraView[1] = false;
		}
		if (ImGui::Button("Perspective View"))
		{
			view2CameraNum = 2;
			perspectiveCameraView[1] = true;
			wireframeCameraView[1] = false;
		}
		if (ImGui::Button("Wireframe View"))
		{
			view2CameraNum = 2;
			perspectiveCameraView[1] = true;
			wireframeCameraView[1] = true;
		}
		if (ImGui::Button("Top-Down View"))
			view2CameraNum = 3;
		ImGui::End();
	}
	if (menuOpen[2])
	{
		ImGui::Begin("Viewport 3", &menuOpen[2], ImGuiWindowFlags_AlwaysAutoResize);
		if (view3CameraNum == 5)
			ImGui::Text("Current View: Top-Down");
		else if (!wireframeCameraView[2] && !perspectiveCameraView[2])
			ImGui::Text("Current View: Lit View");
		else if (perspectiveCameraView[2])
			ImGui::Text("Current View: Perspective View");
		else
			ImGui::Text("Current View: Wireframe View");

		if (ImGui::Button("Lit View"))
		{
			view3CameraNum = 4;
			perspectiveCameraView[2] = false;
			wireframeCameraView[2] = false;
		}
		if (ImGui::Button("Perspective View"))
		{
			view3CameraNum = 4;
			perspectiveCameraView[2] = true;
			wireframeCameraView[2] = false;
		}
		if (ImGui::Button("Wireframe View"))
		{
			view3CameraNum = 4;
			perspectiveCameraView[2] = true;
			wireframeCameraView[2] = true;
		}
		if (ImGui::Button("Top-Down View"))
			view3CameraNum = 5;
		ImGui::End();
	}
}

int ViewportUIManager::getViewCameraNum(int viewNumber)
{
	switch (viewNumber)
	{
	case 1:
		return view1CameraNum;
	case 2:
		return view2CameraNum;
	case 3:
		return view3CameraNum;
	default:
		std::cout << "Invalid view number: " << viewNumber << std::endl;
		return -1;
	}
}

bool ViewportUIManager::getPerspectiveCameraBool(int viewNumber)
{
	if (viewNumber == 1 || viewNumber == 2 || viewNumber == 3)
		return perspectiveCameraView[viewNumber - 1];
	else
	{
		std::cout << "Invalid view number: " << viewNumber << std::endl;
		return false; 
	}
}

bool ViewportUIManager::getWireframeCameraBool(int viewNumber)
{
	if (viewNumber == 1 || viewNumber == 2 || viewNumber == 3)
		return wireframeCameraView[viewNumber - 1];
	else
	{
		std::cout << "Invalid view number: " << viewNumber << std::endl;
		return false;
	}
}




