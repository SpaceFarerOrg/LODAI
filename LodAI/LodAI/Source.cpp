//Begin SFML Libraries
#ifdef _DEBUG
#pragma comment(lib, "sfml-system-d")
#pragma comment(lib, "sfml-window-d")
#pragma comment(lib, "sfml-graphics-d")
#else
#pragma comment(lib, "sfml-system")
#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-graphics")
#endif
//End SFML Libraries

#include "Core/Public/Application.h"

int main()
{
	bool ShouldRun = true;
	CApplication Application(ShouldRun);

	Application.Initialize();

	while (ShouldRun)
	{
		Application.Tick();
	}


	return 0;
}