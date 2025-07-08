#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "EngineTime.h"
#include <cstdlib>
#include <DirectXMath.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

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
	srand(time(0));
	float r = 0.0f;
	/*
	for (int i = 0; i < 100; i++) {
		// //                       w     h     d     cx   cy     cz      list
		cubeList.push_back(Cube(0.1f, 0.1f, 0.1f, ((rand() % 200) / 100.0f) - 1, ((rand() % 150 + 25) / 100.0f) - 1, 0.0f, colors, colors2, "cube"));
	}*/

	quadList.push_back(Quads(0.6f, 0.6f, 0.6f, .0f, 0.0f, 0.f, colors, colors2, "quad"));
	cubeList.push_back(Cube(0.2f, 0.2f, 0.2f, .0f, 0.0f, 0.0f, colors, colors2, "cube"));
	//cubeList.push_back(Cube(0.6f, 0.01f, 0.6f, .0f, 0.0f, 0.0f, colors, colors2, "cube2"));
	for (int i = 0; i < quadList.size();i++) {
		quadList[i].createBuffer(&shader_byte_code, &size_shader);
	}
	for (int i = 0; i < cubeList.size();i++) {
		cubeList[i].createBuffer(&shader_byte_code, &size_shader);
	}

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	/*
	cam.SetPosition(-2.0f, .0f, -.1f);
	cam.SetRotation(DirectX::XMVectorSet(0, 1.6, 0, 0));
	*/
	cam.SetPosition(0.0f, .3f, -1.0f);
	cam.SetRotation(DirectX::XMVectorSet(0, 0, 0, 0));
	cam.SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);


	m_raster = GraphicsEngine::get()->createRasterState();
	m_raster->use();

	EngineTime::initialize();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(this->m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());


}

void AppWindow::onUpdate()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hello, world!");
	ImGui::Text("aaaaaaaaaa");
	ImGui::End();

	//set color here
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		.4, 0.4, 0, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);




	for (int i = 0; i < cubeList.size();i++) {
		cubeList[i].draw((this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top), m_vs, m_ps, EngineTime::getDeltaTime(), cam);

		Vector3D pos = cubeList[i].getLocalPosition();
		pos.m_y += 0.001f;
		cubeList[i].setPosition(pos);

	}
	for (int i = 0; i < quadList.size();i++) {
		quadList[i].draw((this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top), m_vs, m_ps, EngineTime::getDeltaTime(), cam);
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


	m_swap_chain->present(true);




}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();


	for (int i = 0; i < quadList.size();i++) {
		quadList[i].destroy();
	}

	for (int i = 0; i < cubeList.size();i++) {
		cubeList[i].destroy();
	}

	GraphicsEngine::get()->release();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
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