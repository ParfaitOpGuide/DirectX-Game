#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	static AppWindow* get();
	static void initialize();
	static void destroy();



	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

	void creategraphicsWindow();

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;	
	
	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};
	static AppWindow* sharedInstance;
};



