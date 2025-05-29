#include "AppWindow.h"
AppWindow* AppWindow::sharedInstance;




AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	//Window::onCreate();
	GraphicsEngine::initialize();


	this->m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();

	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	/*
		{1,0,0},
		{1,0,0},
		{0,1,0},
		{0,0,1}*/

		/*{-0.8f, -0.5f, 0.0f, 0,.5,0},
		{-0.8f, 0.5f, 0.0f,  0,1,0},
		{0.8f, -0.5f, 0.0f,  0,1,0},
		{0.8f, 0.5f, 0.0f,   0,.4,0}*/



	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	std::vector<vec3> colors;
	colors.push_back({ 1,0,0 });
	colors.push_back({ 0,1,0 });
	colors.push_back({ 0,0,1 });
	colors.push_back({ 1,1,0 });
	//                       w     h     cx   cy  list
	quadList.push_back(Quads(0.3f, 0.4f, 0.6f, 0.6f, colors));
	quadList.push_back(Quads(0.4f, 0.2f, -0.6f, -0.3f, colors));
	colors.clear();
	colors.push_back({ 0,0,1 });
	colors.push_back({ 0,1,1 });
	colors.push_back({ 1,0,1 });
	colors.push_back({ 0,1,0 });
	quadList.push_back(Quads(0.7f, 0.5f, 0.2f, -0.5f, colors));
	for (int i = 0; i < quadList.size();i++) {
		quadList[i].createBuffer(&shader_byte_code, &size_shader);
	}


	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();
}

void AppWindow::onUpdate()
{
	//set color here
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		.4, 0.4, 0, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	for (int i = 0; i < quadList.size();i++) {
		quadList[i].draw();
	}

	m_swap_chain->present(false);
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
	GraphicsEngine::get()->release();
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