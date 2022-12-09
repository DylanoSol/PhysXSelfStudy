#include <string>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "../Entities/Player.h"
#include "../physics/Physics.h"


float var1, var2, var3; 

Physics physics = Physics(); 
std::condition_variable condition;
std::vector<std::thread> workers; 
std::mutex inputMutex; 
const int amountOfInputThreads = 1; 
bool waiting = true;
bool running = true;
bool wantsToClose = false; 
Player* testPlayer;

void CheckInput()
{
	while (running)
	{
		printf("Swing %d: \n", testPlayer->AmountOfSwings + 1);
	
		printf("Input X \n");
		std::cin >> var1;	
		printf("Input Y \n");
		std::cin >> var2;
		printf("Input Z \n");
		std::cin >> var3;
		
		testPlayer->SetSwing(physx::PxVec3(var1, var2, var3));
		testPlayer->m_lock = true; 

		//Lock the thread until the swing has been completed.
		std::unique_lock<std::mutex> lock(inputMutex); 
		condition.wait(lock); 
	}
}

int main(int argc, char* args[])
{
	printf("Hello World \n");
	testPlayer = new Player(physx::PxVec3(0.f), physx::PxQuat(0.f), physx::PxVec3(1.f), &physics);


	

	for (int i = 0; i < amountOfInputThreads; i++)
	{
		//Launch the input thread
		workers.emplace_back(std::thread([i] {CheckInput(); }));
	}

	while (running)
	{
		//Update physics simulation
		physics.UpdatePhysics(0.f); 
		testPlayer->Update(0.f); 

		if (GetAsyncKeyState(VK_SPACE))
		{
			//close the program
			running = false;

			condition.notify_all(); 

			for (int i = 0; i < amountOfInputThreads; i++)
			{
				//Kill threads
				workers[i].join();
			}

			exit(0);
		}

		//Notifies the input thread. 
		if (!testPlayer->m_lock && testPlayer->m_sleeping) condition.notify_all(); 
	}
}

