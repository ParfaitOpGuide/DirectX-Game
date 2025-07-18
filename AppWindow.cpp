#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "EngineTime.h"
#include <cstdlib>
#include <DirectXMath.h>
#include "InputSystem.h"
#include "ViewportUIManager.h"
#include "RenderSystem.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "stb_image.h"

AppWindow* AppWindow::sharedInstance;
// Simple helper function to load an image into a DX11 texture with common settings
bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	// Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	GraphicsEngine::get()->getRenderSystem()->getDevice()->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	GraphicsEngine::get()->getRenderSystem()->getDevice()->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}

// Open and read a file, then forward to LoadTextureFromMemory()
bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	FILE* f = fopen(file_name, "rb");
	if (f == NULL)
		return false;
	fseek(f, 0, SEEK_END);
	size_t file_size = (size_t)ftell(f);
	if (file_size == -1)
		return false;
	fseek(f, 0, SEEK_SET);
	void* file_data = IM_ALLOC(file_size);
	fread(file_data, 1, file_size, f);
	fclose(f);
	bool ret = LoadTextureFromMemory(file_data, file_size, out_srv, out_width, out_height);
	IM_FREE(file_data);
	return ret;
}

AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{
}

void AppWindow::updateQuadPosition()
{
	std::cout << "b";
}

void AppWindow::onCreate()
{
	//Window::onCreate();

	InputSystem::get()->addListener(this);
	
	m_wood_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");

	m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
 	//std::cout << m_mesh;
	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);

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




	//quadList.push_back(Quads(0.6f, 0.6f, 0.6f, .0f, 0.0f, 0.f, colors, colors2, "quad"));
	//quadList[0].createBuffer(&shader_byte_code, &size_shader);
	// 
	//area bounds are 1.25 horizontally, 0.9 vertically
	/*cloneCircle = Circle(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f, Vector3D(((rand() % 20) - 10) / 1000.f, ((rand() % 20) - 10) / 1000.f, 0), colors, colors2, "circle");
	cloneCircle.createBuffer(&shader_byte_code, &size_shader);
	circleList.push_back(Circle(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f, Vector3D(((rand() % 20) - 10) / 1000.f, ((rand() % 20) - 10) / 1000.f, 0), colors, colors2, "circle"));
	circleList[0].createBuffer(cloneCircle);*/
	m_raster = GraphicsEngine::get()->getRenderSystem()->createRasterState();
	m_raster->use();
	cloneCube = Cube(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f, Vector3D(0, 0, 0), Vector3D(0, 0, 0), colors, colors2, "basecube", m_raster);
	cloneCube.createBuffer(&shader_byte_code, &size_shader);

	meshList.push_back(MeshObject(0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, Vector3D(0, 0, 0), Vector3D(0, 0, 0), colors, colors2, "cube", m_raster, m_mesh));
	meshList[0].createBuffer(&shader_byte_code, &size_shader);

	for (int i = 0; i < 10; i++) {
		// //                       w     h     d     cx   cy     cz      list
		cubeList.push_back(Cube(0.1f, 0.1f, 0.1f, ((rand() % 200) / 100.0f) - 1, ((rand() % 150 + 25) / 100.0f) - 1, 0.0f, Vector3D(0, 0, 0), Vector3D(((rand() % 200) / 100.0f) - 1, ((rand() % 200) / 100.0f) - 1, ((rand() % 200) / 100.0f) - 1), colors, colors2, "cube", m_raster));
	}

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

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();


	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	/*
	cam.SetPosition(-2.0f, .0f, -.1f);
	cam.SetRotation(DirectX::XMVectorSet(0, 1.6, 0, 0));
	*/
	//cam 1
	camList.push_back(Camera());
	camList[0].SetPosition(-0.0f, .0f, -1.0f);
	camList[0].SetRotation(DirectX::XMVectorSet(0.f, 0.f, 0, 0));
	camList[0].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);	
	//cam 2
	camList.push_back(Camera());
	camList[1].SetPosition(0.0f, 1.f, -.0f);
	camList[1].SetRotation(DirectX::XMVectorSet(1.5708f, .0f, 0, 0));
	camList[1].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);

	//port 2
	//cam 3
	camList.push_back(Camera());
	camList[2].SetPosition(-1.0f, 1.3f, -1.0f);
	camList[2].SetRotation(DirectX::XMVectorSet(0.6f, 0.8f, 0, 0));
	camList[2].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);
	//cam 4
	camList.push_back(Camera());
	camList[3].SetPosition(0.0f, 1.f, -.0f);
	camList[3].SetRotation(DirectX::XMVectorSet(1.5708f, .0f, 0, 0));
	camList[3].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);

	//port 3
	//cam 5
	camList.push_back(Camera());
	camList[4].SetPosition(.8f, .3f, 0.3f);
	camList[4].SetRotation(DirectX::XMVectorSet(0, -2, 0, 0));
	camList[4].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);
	//cam 6
	camList.push_back(Camera());
	camList[5].SetPosition(0.0f, 1.f, -.0f);
	camList[5].SetRotation(DirectX::XMVectorSet(1.5708f, .0f, 0, 0));
	camList[5].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);	
	
	//freecam
	camList.push_back(Camera());
	camList[6].SetProjectionValues(100.f, (rc.right - rc.left) / (rc.bottom - rc.top), 0.1f, 1000.f);





	EngineTime::initialize();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui_ImplWin32_Init(this->m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getRenderSystem()->getDevice(), GraphicsEngine::get()->getRenderSystem()->getDeviceContext());

	
	
	bool ret = LoadTextureFromFile("DLSU_Logo-green.png", &my_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
}

void AppWindow::onUpdate()
{
	InputSystem::get()->update();
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//ImGui::SetNextWindowSize(ImVec2(300, 400));

	static bool truth = true;

	ImGuiWindowFlags flags = 0;
	flags |= ImGuiWindowFlags_NoTitleBar; 
	flags |= ImGuiWindowFlags_NoMove;
	flags |= ImGuiWindowFlags_NoResize;
	
	RECT rc = this->getClientWindowRect();
	auto width = rc.right - rc.left;
	auto height = rc.bottom - rc.top;
	/*
	ImGui::SetNextWindowSize(ImVec2(1, height / 2 - 20));
	ImGui::SetNextWindowPos(ImVec2(width/2, 20));
	ImGui::Begin("Divider", &truth, flags);
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(width, 0));
	ImGui::SetNextWindowPos(ImVec2(0, height / 2));
	ImGui::Begin("Divider2", &truth, flags);
	ImGui::End();
	*/
	
	
	ViewportUIManager::getInstance()->OnUpdate();


		ImGui::Begin("Credits");
	ImGui::Text("About\n\nBy Nathaniel Agasen\n\nSpecial Thanks to PardCode and JPres");
	
	ImGui::Text("pointer = %p", my_texture);
	ImGui::Text("size = %d x %d", my_image_width, my_image_height);
	ImGui::Image((ImTextureID)(intptr_t)my_texture, ImVec2(300, 300));
	ImGui::End();


	//set color here
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		.3, 0.3, 0, 1);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);


	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_wood_tex);



	for (int i = 0; i < cubeList.size();i++) {
		cubeList[i].draw((this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top), m_vs, m_ps, EngineTime::getDeltaTime(), camList, currentCam);
	}
	for (int i = 0; i < quadList.size();i++) {
		//quadList[i].draw((this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top), m_vs, m_ps, EngineTime::getDeltaTime(), camList, currentCam);
	}
	for (int i = 0; i < circleList.size();i++) {
		//circleList[i].draw((this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top), m_vs, m_ps, EngineTime::getDeltaTime(), camList, currentCam);
	}
	for (int i = 0; i < meshList.size();i++) {
		meshList[i].draw((this->getClientWindowRect().right - this->getClientWindowRect().left), (this->getClientWindowRect().bottom - this->getClientWindowRect().top), m_vs, m_ps, EngineTime::getDeltaTime(), camList, currentCam);
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	if (quadList.size() > 0)
		quadList[0].destroy();
	if (cubeList.size() > 0)
		cubeList[0].destroy();

}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
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

	//std::cout << key << "\n";
	if (key == 32)
	{
		if (!pressed) {
			//cubeList.push_back(Cube(0.1f, 0.1f, 0.1f, ((rand() % 200) / 100.0f) - 1, ((rand() % 150 + 25) / 100.0f) - 1, 0.0f, colors, colors, "cube"));
			//circleList.push_back(Circle(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f, Vector3D(((rand() % 20) - 10) / 1000.f, ((rand() % 20) - 10) / 1000.f, 0), colors, colors, "circle"));
			//circleList[circleList.size() - 1].createBuffer(cloneCircle);
			//pressed = true;
		}
	}
	else if (key == 46)
	{
		if (!pressed) {
			/*
			if (circleList.size() > 0)
				circleList.clear();
			pressed = true;*/

			/*if (!freeCam)
				freeCam = true;*/

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
		if (camPawn) {
			camPawn = false;
		//	cubeList.pop_back();
		}

	}
	else if (key == 50) //2
	{
		currentCam = 1;
		freeCam = false;

		if (camPawn) {
			camPawn = false;
		//	cubeList.pop_back();
		}
	}
	else if (key == 51) //3
	{
		currentCam = 2;
		freeCam = false;

		if (camPawn) {
			camPawn = false;
		//	cubeList.pop_back();
		}
	}
	else if (key == 52) //4
	{
		currentCam = 3;
		freeCam = false;

		if (camPawn) {
			camPawn = false;
		//	cubeList.pop_back();
		}
	}
	else if (key == 53) //5
	{
		currentCam = 4;
		freeCam = false;

		if (camPawn) {
			camPawn = false;
			//cubeList.pop_back();
		}
	}



	const float camSpeed = 0.04;
	if (key == 87) // W
	{	
		for (int i = 0; i < cubeList.size(); i++) {
				Vector3D r = cubeList[i].getLocalRotation();
				r.m_x += 0.1;
				r.m_y += 0.1;
				r.m_z += 0.1;
				cubeList[i].setRotation(r);
		if (freeCam) {
			XMFLOAT3 forwardFloat3;
			XMStoreFloat3(&forwardFloat3, camList[freeCamNum].GetForwardVector());

			float x = forwardFloat3.x * camSpeed * .1;
			float y = forwardFloat3.y * camSpeed * .1;
			float z = forwardFloat3.z * camSpeed * .1;
			if (freeCam) {
				camList[freeCamNum].AdjustPosition(x, y, z);
			}

		
			}
		}

	}
	else if (key == 65) // A
	{
		if (freeCam) {
			XMFLOAT3 forwardFloat3;
			XMStoreFloat3(&forwardFloat3, camList[freeCamNum].GetLeftVector());

			float x = forwardFloat3.x * camSpeed;
			float y = forwardFloat3.y * camSpeed;
			float z = forwardFloat3.z * camSpeed;
			if (freeCam) {
				camList[freeCamNum].AdjustPosition(x, y, z);
			}
		}
	}
	else if (key == 83) // S
	{
		if (freeCam) {
			XMFLOAT3 forwardFloat3;
			XMStoreFloat3(&forwardFloat3, camList[freeCamNum].GetBackwardVector());

			float x = forwardFloat3.x * camSpeed;
			float y = forwardFloat3.y * camSpeed;
			float z = forwardFloat3.z * camSpeed;
			if (freeCam) {
				camList[freeCamNum].AdjustPosition(x, y, z);
			}

			for (int i = 0; i < cubeList.size(); i++) {
				Vector3D r = cubeList[i].getLocalRotation();
				r.m_x -= 0.1;
				r.m_y -= 0.1;
				r.m_z -= 0.1;
				cubeList[i].setRotation(r);
			}
		}
	}
	else if (key == 68) // D
	{
		if (freeCam) {
			XMFLOAT3 forwardFloat3;
			XMStoreFloat3(&forwardFloat3, camList[freeCamNum].GetRightVector());

			float x = forwardFloat3.x * camSpeed;
			float y = forwardFloat3.y * camSpeed;
			float z = forwardFloat3.z * camSpeed;
			if (freeCam) {
				camList[freeCamNum].AdjustPosition(x, y, z);
			}
		}
	}
	else if (key == 81) // Q
	{
		if (freeCam) {
			XMFLOAT3 forwardFloat3;
			XMStoreFloat3(&forwardFloat3, camList[freeCamNum].GetUpVector());

			float x = forwardFloat3.x * camSpeed;
			float y = forwardFloat3.y * camSpeed;
			float z = forwardFloat3.z * camSpeed;
			if (freeCam) {
				camList[freeCamNum].AdjustPosition(x, y, z);
			}
		}
	}
	else if (key == 69) // E
	{
		if (freeCam) {
			XMFLOAT3 forwardFloat3;
			XMStoreFloat3(&forwardFloat3, camList[freeCamNum].GetDownVector());

			float x = forwardFloat3.x * camSpeed;
			float y = forwardFloat3.y * camSpeed;
			float z = forwardFloat3.z * camSpeed;
			if (freeCam) {
				camList[freeCamNum].AdjustPosition(x, y, z);
			}
		}
	}

	//cube cam despawn



}

void AppWindow::onKeyUp(int key)
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

	if (key == 8)
	{
		if (!freeCam)
			freeCam = true;

		camList[freeCamNum].SetPosition(camList[currentCam].getPosition().m_x, camList[currentCam].getPosition().m_y, camList[currentCam].getPosition().m_z);
		camList[freeCamNum].SetRotation(camList[currentCam].getRotation().m_x, camList[currentCam].getRotation().m_y, camList[currentCam].getRotation().m_z);
		/*
		cubeList.push_back(Cube(0.1f, 0.1f, 0.1f, camList[currentCam].getPosition().m_x,
			camList[currentCam].getPosition().m_y, camList[currentCam].getPosition().m_z, Vector3D(0.0, -0.0, 0), Vector3D(0, 0.0, 1.3), colors, colors2, "camCube"));
		cubeList[cubeList.size() - 1].createBuffer(cloneCube);*/

		camPawn = true;

		currentCam = freeCamNum;
	}
}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
	if (freeCam) {
		camList[freeCamNum].AdjustRotation(delta_mouse_pos.m_y * 0.01, delta_mouse_pos.m_x * 0.01, 0);
	}

}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{

}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	//sharedInstance->init();
}

void AppWindow::destroy()
{
	if (sharedInstance != NULL) {
		  //sharedInstance->release();
	}
}

AppWindow* AppWindow::get()
{
	if (!sharedInstance) {
		initialize();
	}

	return sharedInstance;
}