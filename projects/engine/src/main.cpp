#include "Mat4.h"
#include "Vec4.h"
#include "Quat.h"

#include "Simulation\SimData.h"
#include "Simulation\SimManager.h"
#include "Simulation\CloudRenderManager.h"

#include <iostream>
#include <vector>
#include <string>

#include <thread>
#include <mutex>

using namespace math;

#define MAX_FRAMERATE_MILISECONDS 1000.0/60.0

// The size of the grid (must be powers of 2)
int gridX = 128;
int gridY = 128;
int gridZ = 128;
int frameCap = 60;
double simulationCap = 2;


std::unique_ptr<SimData> simulationData;
std::unique_ptr<SimManager> simulationManager;
std::unique_ptr<CloudRenderManager> rendererModule;

// Simulation thread
std::thread simThread;
// Final simulation data mutex
std::mutex simMutex;

// True when program begins exit
bool exitLoop = false;

bool simPaused = false;


// Function that asynchronously runs simulation 
void Simulate(void *arg) {

	while (!exitLoop) {
		if (!simPaused) {

			double startTime = glfwGetTime();

			// Perform the part of the simulation that can be done 
			// asynchronously
			simulationManager->stepAsych(simulationData.get());

			// Lock mutex and do the rest of the simulation
			simMutex.lock();
			simulationManager->stepMutex(simulationData.get(), glfwGetTime());
			simMutex.unlock();

			clock_t sleep_time = 1.0 / simulationCap - glfwGetTime() + startTime;
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
		}
	}
}


void run()
{
	

	// Allocate simulation data on the heap
	simulationData = std::unique_ptr<SimData>(new SimData(gridX, gridY, gridZ));

	//// Initialize cloud renderer module
	rendererModule = std::unique_ptr<CloudRenderManager>(new CloudRenderManager());
	if (!rendererModule->initialize(gridX, gridY, gridZ)) return;

	// Initialize cloud simulation module
	simulationManager = std::unique_ptr<SimManager>(new SimManager(gridX, gridY, gridZ));

	void* arguments[] = { &simulationData, &simulationManager };

	// Create the simulation thread and data mutex
	simThread = std::thread(Simulate, arguments);

	// The main loop
	while (true)
	{

		double startTime = glfwGetTime();
		clock_t start_clock = clock();
		rendererModule->draw(*simulationData.get(), simMutex, startTime);
	}

	exitLoop = true;

	// Wait for the other thread to finish
	simThread.join();

	// Terminate
	rendererModule->terminate();

}


int main()
{
	run();
	int wait = 0;
	std::cin >> wait;
	exit(EXIT_SUCCESS);
}