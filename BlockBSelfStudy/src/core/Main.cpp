#include <string>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "../physics/Physics.h"

int testVar = 0; 

Physics physics = Physics(); 
std::condition_variable condition;
std::vector<std::thread> workers; 
std::mutex inputMutex; 
const int amountOfThreads = 1; 
bool waiting = true;
bool running = true;

void CheckInput()
{
	while (running)
	{
		waiting = false; 
		std::cin >> testVar;	
		waiting = true; 

		std::unique_lock<std::mutex> lock(inputMutex); 
		condition.wait(lock); 
	}
}

int main(int argc, char* args[])
{
	printf("Hello World \n");

	for (int i = 0; i < amountOfThreads; i++)
	{
		workers.emplace_back(std::thread([i] {CheckInput(); }));
	}

	while (running)
	{
		//Update physics simulation
		physics.UpdatePhysics(0.f); 

		if (GetAsyncKeyState(VK_SPACE) || testVar == 100)
		{
			//close the program
			running = false;
			condition.notify_all(); 
			for (int i = 0; i < amountOfThreads; i++)
			{
				//Kill threads
				workers[i].join();
			}

			exit(0);
		}
		if (waiting) condition.notify_all(); 
	}
}

