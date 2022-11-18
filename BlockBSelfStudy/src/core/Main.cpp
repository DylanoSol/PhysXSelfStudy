#include <string>
#include <Windows.h>
#include "../physics/Physics.h"

Physics physics = Physics(); 

int main(int argc, char* args[])
{
	printf("Hello World");

	while (true)
	{
		physics.UpdatePhysics(0.f); 

		if (GetAsyncKeyState(VK_SPACE)) exit(0); 
	}
}