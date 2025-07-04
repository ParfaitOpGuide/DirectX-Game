#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "EngineTime.h"
#include <cstdlib>
#include <DirectXMath.h>
#include"InputSystem.h"

AppWindow* AppWindow::sharedInstance;

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::updateQuadPosition()
{

}

void AppWindow::onCreate()
{
	//Window::onCreate();

	InputSystem::get()->addListener(this);


	GraphicsEngine::get()->init();

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();

	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	std::vector<Vector3D> colors;
	std::vector<Vector3D> colors2;
	colors.push_back(Vector3D(1, 0, 0));
	colors.push_back(Vector3D(0, 1, 0));
	colors.push_back(Vector3D(0, 0, 1));
	colors.push_back(Vector3D(1, 1, 0));

	colors2.push_back(Vector3D(1, 0, 1));
	colors2.push_back(Vector3D(1, 1, 0));
	colors2.push_back(Vector3D(1, 0, 1));
	colors2.push_back(Vector3D(0, 1, 0));

	/*
	for (int i = 0; i < 100; i++) {
		// //                       w     h     d     cx   cy     cz      list
		cubeList.push_back(Cube(0.1f, 0.1f, 0.1f, ((rand() % 200) / 100.0f) - 1, ((rand() % 150 + 25) / 100.0f) - 1, 0.0f, colors, colors2, "cube"));
	}*/

	//quadList.push_back(Quads(0.6f, 0.6f, 0.6f, .0f, 0.0f, 0.f, colors, colors2, "quad"));
	//quadList[0].createBuffer(&shader_byte_code, &size_shader);
	// 
	//area bounds are 1.25 horizontally, 0.9 vertically
	/*cloneCircle = Circle(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f, Vector3D(((rand() % 20) - 10) / 1000.f, ((rand() % 20) - 10) / 1000.f, 0), colors, colors2, "circle");
	cloneCircle.createBuffer(&shader_byte_code, &size_shader);
	circleList.push_back(Circle(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f, Vector3D(((rand() % 20) - 10) / 1000.f, ((rand() % 20) - 10) / 1000.f, 0), colors, colors2, "circle"));
	circleList[0].createBuffer(cloneCircle);*/

	cloneCube = Cube(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f, Vector3D(0, 0, 0), Vector3D(0, 0, 0), colors, colors2, "basecube");
	cloneCube.createBuffer(&shader_byte_code, &size_shader);
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, -0.052f, 0.0f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, 1.3), colors, colors2, "layer1"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, 0.052f, 0.0f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, -1.3), colors, colors2, "layer1"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, 0.16f, 0.0f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, 1.3), colors, colors2, "layer1"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, 0.264f, 0.0f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, -1.3), colors, colors2, "layer1"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, -0.264f, 0.0f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, 1.3), colors, colors2, "layer1"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, -0.16f, 0.0f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, -1.3), colors, colors2, "layer1"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, -0.16f, 0.2f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, -0), colors, colors2, "layer1Flat"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, 0.16f, 0.2f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, -0), colors, colors2, "layer1Flat"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, -0.156f, 0.4f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, 1.3), colors, colors2, "layer2"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, -0.052f, 0.4f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, -1.3), colors, colors2, "layer2"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, 0.052f, 0.4f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, 1.3), colors, colors2, "layer2"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, 0.156f, 0.4f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, -1.3), colors, colors2, "layer2"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, 0.0f, 0.6f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, -0), colors, colors2, "layer2Flat"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, -0.054f, 0.8f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, 1.3), colors, colors2, "layer3"));
	cubeList.push_back(Cube(0.4f, .01f, 0.4f, 0.054f, 0.8f, 0.0f, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, -1.3), colors, colors2, "layer3"));
	cubeList[0].createBuffer(cloneCube);


	//cubeList.push_back(Cube(0.6f, 0.01f, 0.6f, .0f, 0.0f, 0.0f, colors, colors2, "cube2"));
	//std::cout<< cubeList.size() << "\n";
	for (int i = 0; i < quadList.size();i++) {
		quadList[i].createBuffer(quadList[0]);
	}
	for (int i = 0; i < cubeList.size();i++) {
		cubeList[i].createBuffer(cloneCube);
	}

	for (int i = 0; i < circleList.size();i++) {
		circleList[i].createBuffer(cloneCircle);
	}

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	/*
	cam.SetPosition(-2.0f, .0f, -.1f);
	cam.SetRotation(DirectX::XMVectorSet(0, 1.6, 0, 0));
	*/
	//cam 1
	camList.push_back(Camera());
	camList[0].SetPosition(0.0f, .3f, -2.0f);
	camList[0].SetRotation(DirectX::XMVectorSet(0, 0, 0, 0));
	camList[0].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);
	//cam 2
	camList.push_back(Camera());
	camList[1].SetPosition(1.0f, 1.3f, -1.0f);
	camList[1].SetRotation(DirectX::XMVectorSet(0.6f, -0.8f, 0, 0));
	camList[1].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);	
	//cam 3
	camList.push_back(Camera());
	camList[2].SetPosition(-1.0f, 1.3f, -1.0f);
	camList[2].SetRotation(DirectX::XMVectorSet(0.6f, 0.8f, 0, 0));
	camList[2].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);
	//cam 4
	camList.push_back(Camera());
	camList[3].SetPosition(-.8f, .3f, 0.3f);
	camList[3].SetRotation(DirectX::XMVectorSet(0, 2, 0, 0));
	camList[3].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);
	//cam 5
	camList.push_back(Camera());
	camList[4].SetPosition(.8f, .3f, 0.3f);
	camList[4].SetRotation(DirectX::XMVectorSet(0, -2, 0, 0));
	camList[4].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);
	currentCam = 0;

	m_raster = GraphicsEngine::get()->createRasterState();
	m_raster->use();

	EngineTime::initialize();
}

void AppWindow::onUpdate()
{
	InputSystem::get()->update();

	//set color here
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		.0, 0, 0, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);




	for (int i = 0; i < cubeList.size();i++) {
		cubeList[i].draw((this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top), m_vs, m_ps, EngineTime::getDeltaTime(), camList[currentCam]);
	}
	for (int i = 0; i < quadList.size();i++) {
		quadList[i].draw((this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top), m_vs, m_ps, EngineTime::getDeltaTime(), camList[currentCam]);
	}
	for (int i = 0; i < circleList.size();i++) {
		circleList[i].draw((this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top), m_vs, m_ps, EngineTime::getDeltaTime(), camList[currentCam]);
	}
	m_swap_chain->present(true);


}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();

	if (quadList.size() > 0)
		quadList[0].destroy();
	if (cubeList.size() > 0)
		cubeList[0].destroy();


	GraphicsEngine::get()->release();
}

void AppWindow::onKeyDown(int key)
{
	std::vector<Vector3D> colors;
	std::vector<Vector3D> colors2;
	colors.push_back(Vector3D(1, 1, 1));
	colors.push_back(Vector3D(1, 1, 1));
	colors.push_back(Vector3D(1, 1, 1));
	colors.push_back(Vector3D(1, 1, 1));

	colors2.push_back(Vector3D(1, 0, 1));
	colors2.push_back(Vector3D(1, 1, 0));
	colors2.push_back(Vector3D(1, 0, 1));
	colors2.push_back(Vector3D(0, 1, 0));

	std::cout << key << "\n";
	if (key == 32)
	{
		if (!pressed) {
			//cubeList.push_back(Cube(0.1f, 0.1f, 0.1f, ((rand() % 200) / 100.0f) - 1, ((rand() % 150 + 25) / 100.0f) - 1, 0.0f, colors, colors, "cube"));
			circleList.push_back(Circle(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f, Vector3D(((rand() % 20) - 10) / 1000.f, ((rand() % 20) - 10) / 1000.f, 0), colors, colors, "circle"));
			circleList[circleList.size() - 1].createBuffer(cloneCircle);
			pressed = true;
		}
	}
	else if (key == 8)
	{
		if (!pressed) {
			if (circleList.size() > 0)
				circleList.pop_back();
			pressed = true;
		}
	}
	else if (key == 46)
	{
		if (!pressed) {
			/*
			if (circleList.size() > 0)
				circleList.clear();
			pressed = true;*/

			if (!freeCam)
				freeCam = true;
		}
	}
	else if (key == 27)
	{
		PostMessage(this->m_hwnd, WM_CLOSE, 0, 0);
	}
	else if (key == 49) //1
	{
		currentCam = 0;
		freeCam = false;
	}
	else if (key == 50) //2
	{
		currentCam = 1;
		freeCam = false;
	}
	else if (key == 51) //3
	{
		currentCam = 2;
		freeCam = false;
	}
	else if (key == 52) //4
	{
		currentCam = 3;
		freeCam = false;
	}
	else if (key == 53) //5
	{
		currentCam = 4;
		freeCam = false;
	}
}

void AppWindow::onKeyUp(int key)
{
	if (key == 32)
	{
		pressed = false;
	} 
	else if (key == 8)
	{
		pressed = false;
	}
	else if (key == 46)
	{
		pressed = false;
	}
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::destroy()
{
	if (sharedInstance != NULL) {
		sharedInstance->release();
	}
}

AppWindow* AppWindow::get()
{
	if (!sharedInstance) {
		initialize();
	}

	return sharedInstance;
}