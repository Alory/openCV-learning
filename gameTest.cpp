//-------程序说明----------------------
//照着抄的开发游戏的程序框架
//2016.8.6
//--------------------------------------

#include<Windows.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE L"游戏程序开发框架"

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	//1、窗口设计步骤一：开始设计一个完整的窗口类
	WNDCLASSEX wndClass = {0};//定义一个窗口类
	wndClass.cbSize = sizeof(WNDCLASSEX);//设置结构体字节数大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW;//设置窗体样式
	wndClass.lpfnWndProc = WndProc;//设置指向窗口过程函数的指针
	wndClass.cbClsExtra = 0;//窗口类的附加内存，取0
	wndClass.cbWndExtra = 0;//窗口的附加内存，取0；
	wndClass.hInstance = hinstance;//指定包含窗口过程的实例句柄
	wndClass.hIcon = (HICON)::LoadImage(NULL,L"girl.ico",IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_LOADFROMFILE);//本地加载自定义icon
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);//指定窗口类的光标句柄
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);//为hbrBackground成员指定画刷句柄
	wndClass.lpszMenuName = NULL;//指定菜单资源名字，以空字符结尾
	wndClass.lpszClassName = L"fuckingTheDream";//指定窗口类名字

	//2、窗口设计步骤二：注册窗口类
	if (!RegisterClassEx(&wndClass))
		return -1;

	//3、窗口设计步骤三：正式创建一个窗口
	HWND hwnd = CreateWindow(L"fuckingTheDream",WINDOW_TITLE,WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT,CW_USEDEFAULT,WINDOW_WIDTH,WINDOW_HEIGHT,
								NULL,NULL,hinstance,NULL);

	//4、窗口设计步骤四：窗口的移动、显示和更新
	MoveWindow(hwnd,250,80,WINDOW_WIDTH,WINDOW_HEIGHT,true);//调整窗口显示的位置，使窗口左上角在(250,80)位置
	ShowWindow(hwnd,nCmdShow);//调用showWindow函数显示窗口
	UpdateWindow(hwnd);//更新窗口，【就像买房子装修一样】
	
	//5、消息循环过程
	MSG msg = { 0 };//定义和初始化一个msg
	while (msg.message != WM_QUIT)//循环，当消息不是WM_QUIT消息时保持循环
	{
		if (PeekMessage(&msg,0,0,0,PM_REMOVE))//查看消息队列，有消息时将队列的消息派发出去
		{
			TranslateMessage(&msg);//将虚拟键消息转变成字符消息
			DispatchMessage(&msg);//分发一个消息到窗口程序
		}
	}

	//6、注销窗口类
	UnregisterClass(L"fuckingTheDream",wndClass.hInstance);//注销窗口
	return 0;
}

//--------------------------------------【WndProc()函数】-----------------------------------------------
//描述：窗口过程函数，对窗口消息进行处理
//----------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	switch (message)
	{
	case WM_PAINT : //客户区重绘消息
		ValidateRect(hwnd,NULL);//更新客户区的显示
		break;
	case WM_KEYDOWN://键盘按下消息
		if(wParam == VK_ESCAPE)//按下ESC键
			DestroyWindow(hwnd);//销毁窗口，并发送一条WM_ESTROY消息
		break;
	case WM_DESTROY://窗口销毁消息
		PostQuitMessage(0);//向系统表明有线程有终止请求
		break;
	default:
		return DefWindowProc(hwnd,message,wParam,lParam);//调用默认窗口过程
	}
	return 0;
}
