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
#include "MeshObject.h"


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

	void onFocus()override;
	void onKillFocus()override;


	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	
	virtual void onMouseMove(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos)  override;

	virtual void onRightMouseDown(const Point& mouse_pos)  override;
	virtual void onRightMouseUp(const Point& mouse_pos)  override;

	//singleton
	static AppWindow* get();
	static void initialize();
	static void destroy();

	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};
	static AppWindow* sharedInstance;

	void spawnCube();

private:
	SwapChainPtr m_swap_chain;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	TexturePtr m_wood_tex;
	MeshPtr m_mesh;
	MeshPtr m_mesh1;
	MeshPtr m_mesh2;
	float size = 0.5f;
	
	RasterState* m_raster;
	std::vector<Camera> camList;
	int currentCam;
	int prevCam;

	std::vector<Quads> quadList = {};
	std::vector<Cube> cubeList = {};
	std::vector<Circle> circleList = {};
	std::vector<MeshObject> meshList = {};

	Cube cloneCube;
	Circle cloneCircle;

	int freeCamNum = 0;
	bool freeCam = true;
	bool pressed = false;
	bool camPawn = false;

	bool window = false;
	int my_image_width = 0;
	int my_image_height = 0;
	ID3D11ShaderResourceView* my_texture = NULL;
};

