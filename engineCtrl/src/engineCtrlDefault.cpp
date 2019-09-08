#include "engineCtrlDefault.h"

#include "factory.h"


EngineCtrl::EngineCtrlDefault::EngineCtrlDefault(const std::string& name) : 
	m_name(name), 
	m_deltaTime(0.0f), 
	m_lastFrame(0.0f)
{
	std::cout << "EngineCtrlDefault " << m_name << " created." << '\n';

	// Database initialization because of second main parameter from main.cpp
}


EngineCtrl::EngineCtrlDefault::~EngineCtrlDefault()
{
}


void EngineCtrl::EngineCtrlDefault::preInit()
{
	// Create defaultInit 
	m_defaultInit0 = std::make_unique <Init::InitDefault>("DefaultInit0");
	// Init All Objects
	m_defaultInit0->preInit();

	// Create cmdPrompt
	m_cmdPrompt0 = std::make_unique<Common::CmdPrompt>("CmdPrompt0");
}


void EngineCtrl::EngineCtrlDefault::postInit()
{
	m_defaultInit0->postInit();

	// START CMD PROMPT
	// TODO: thread 1
	m_cmdPrompt0->runCmdPrompt();

	// START RENDERing
	// TODO: thread 2
	render();
}


void EngineCtrl::EngineCtrlDefault::databaseInit(const std::string& dbName)
{
	Common::Error err;

	// Create DB and store it in Factory
	std::unique_ptr<Common::Database> database = std::make_unique<Common::Database>(err, dbName);
	Common::Factory::getInstance().setDatabase(database);
}


void EngineCtrl::EngineCtrlDefault::glfwInitialization()
{
	if (!glfwInit())
	{
		// Print error or something
	}

	// TODO: Get this window information from Database!
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		// Print error or something
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);
	glfwSetKeyCallback(m_window, Control::ControlDefault::keyCallback);
	glfwSetCursorPosCallback(m_window, Control::ControlDefault::mouseCallback);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		// std::cout << "Failed to initialize GLEW" << std::endl;
	}



	// Set some vaules
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}


void EngineCtrl::EngineCtrlDefault::gameLoop()
{

}

void EngineCtrl::EngineCtrlDefault::render()
{
	std::shared_ptr<Control::ControlIf> control = FACTORY.getControlIf("smartControl_0");
	control->postInit();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_window))
	{
		// Calculate Time Frame
		// ----
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;
		// ----

		/* Render here */
		/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CLIP_DISTANCE0);*/
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);


		// Camera movement
		control->updateCameraPosition(m_deltaTime);

		Common::Factory::getInstance().getModelIf("vanquishModel")->render();
		Common::Factory::getInstance().getModelIf("terrainModel_0")->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}

