#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <vector>
#include "Quads.h"
#include "Cube.h"
#include "Circle.h"
#include "RasterState.h"
#include "InputListener.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	void updateQuadPosition();

	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;


	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	//singleton
	static AppWindow* get();
	static void initialize();
	static void destroy();

	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};
	static AppWindow* sharedInstance;

private:
	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;

	
	RasterState* m_raster;
	Camera cam;

	std::vector<Quads> quadList = {};
	std::vector<Cube> cubeList = {};
	std::vector<Circle> circleList = {};

	Cube cloneCube;
	Circle cloneCircle;


	bool pressed = false;
};

