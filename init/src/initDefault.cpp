#include "initDefault.h"

#include <chrono>

#include "factory.h"


Init::InitDefault::InitDefault(const std::string& name) : m_name(name)
{
}


Init::InitDefault::~InitDefault()
{
}


void Init::InitDefault::preInit()
{
	// First Thing to do! Create all objects in preInit Factory method!
	FACTORY.preInit();
	FACTORY.createObjects();


	std::cout << "[Pre Initialisation]" << '\n';

	// -- Start Measurement --
	auto start = std::chrono::system_clock::now();

	// 1] CONTROLs
	std::cout << "    Controls: ";

	for (auto it : FACTORY.getControlIfVec())
	{
		// it->preInit();
		std::cout << ".";
	}
	std::cout << " [DONE]" << '\n';

	// 2] CAMERAs
	std::cout << "    Cameras: ";

	for (auto it : FACTORY.getCameraIfVec())
	{
		// it->preInit();
		std::cout << ".";
	}
	std::cout << " [DONE]" << '\n';

	// 3] LIGHTs
	std::cout << "    Lights: ";

	for (auto it : FACTORY.getLightIfVec())
	{
		//it->preInit();
		std::cout << ".";
	}
	std::cout << " [DONE]" << '\n';

	// 4] LOADERs
	std::cout << "    Loaders: ";

	for (auto it : FACTORY.getLoaderIfVec())
	{
		// it->preInit();
		std::cout << ".";
	}
	std::cout << " [DONE]" << '\n';

	// 5] GPUObjects
	std::cout << "    GPUObjects: ";
	for (auto it : FACTORY.getGPUObjectIfVec())
	{
		// it->preInit();
		std::cout << ".";
	}
	std::cout << " [DONE]" << '\n';

	// 6] MODELs
	std::cout << "    Models: ";
	for (auto it : FACTORY.getModelIfVec())
	{
		// it->preInit();
		std::cout << ".";
	}
	std::cout << " [DONE]" << '\n';

	// 7] SHADERs
	std::cout << "    Shaders: ";
	for (auto it : FACTORY.getShaderIfVec())
	{
		// it->preInit();
		std::cout << ".";
	}
	std::cout << " [DONE]" << '\n';

	// -- Stop Measurement --
	auto end = std::chrono::system_clock::now();

	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	// auto elapsed = end - start;

	std::cout << " Elapsed Time: " << elapsed.count()  << " [ms]" << '\n';

}


// Combine all things together
void Init::InitDefault::postInit()
{
	FACTORY.postInit();

	FACTORY.getLog()->INFOCMDNONEWLINE(LOG "[Post Initialisation]");
	std::cout << '\n';

	// 1] CONTROLs
	FACTORY.getLog()->INFOCMDNONEWLINE(LOG "    Controls: ");
	for (auto it : FACTORY.getControlIfVec())
	{
		//it->postInit();
		FACTORY.getLog()->INFOCMDNONEWLINE(LOG ".");
	}
	std::cout << " [DONE]" << '\n';

	// 2] CAMERAs
	FACTORY.getLog()->INFOCMDNONEWLINE(LOG "    Cameras: ");
	for (auto it : FACTORY.getCameraIfVec())
	{
		//it->postInit();
		FACTORY.getLog()->INFOCMDNONEWLINE(LOG ".");
	}
	std::cout << " [DONE]" << '\n';

	// 3] LIGHTs
	FACTORY.getLog()->INFOCMDNONEWLINE(LOG "    Lights: ");
	for (auto it : FACTORY.getLightIfVec())
	{
		//it->postInit();
		FACTORY.getLog()->INFOCMDNONEWLINE(LOG ".");
	}
	std::cout << " [DONE]" << '\n';

	// 4] LOADERs
	FACTORY.getLog()->INFOCMDNONEWLINE(LOG "    Loaders: ");
	for (auto it : FACTORY.getLoaderIfVec())
	{
		//it->postInit();
		FACTORY.getLog()->INFOCMDNONEWLINE(LOG ".");
	}
	std::cout << " [DONE]" << '\n';

	// 5] GPUObjects
	FACTORY.getLog()->INFOCMDNONEWLINE(LOG "    GPUObjects: ");
	for (auto it : FACTORY.getGPUObjectIfVec())
	{
		//it->postInit();
		FACTORY.getLog()->INFOCMDNONEWLINE(LOG ".");
	}
	std::cout << " [DONE]" << '\n';

	// 6] MODELs
	FACTORY.getLog()->INFOCMDNONEWLINE(LOG "    Models: ");
	for (auto it : FACTORY.getModelIfVec())
	{
		//it->postInit();
		FACTORY.getLog()->INFOCMDNONEWLINE(LOG ".");
	}
	std::cout << " [DONE]" << '\n';

	// 7] SHADERs
	FACTORY.getLog()->INFOCMDNONEWLINE(LOG "    Shaders: ");
	for (auto it : FACTORY.getShaderIfVec())
	{
		//it->postInit();
		FACTORY.getLog()->INFOCMDNONEWLINE(LOG ".");
	}
	std::cout << " [DONE]" << '\n';
	std::cout << "Time: " << '\n';


	// NEW HANDLING
	auto newControls = FACTORY.getControlIf("defaultControls");
	newControls->postInitialization();

	auto newCamera = FACTORY.getCameraIf("defaultCamera");
	newCamera->postInitialization();

	auto newModel = FACTORY.getModelIf("vanquish");
	newModel->postInitialization();
}
