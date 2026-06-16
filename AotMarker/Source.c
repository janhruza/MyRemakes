#include <Windows.h>

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	MessageBox(NULL, TEXT("This works flawlessly."), TEXT("AotMaker"), MB_OK | MB_ICONINFORMATION);
	return 0;
}