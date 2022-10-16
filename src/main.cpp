#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "toolbox/Camera.h"
#include "toolbox/UserOptions.h"

//#include "models/City.h"
#include "models/LoadedModel.h"
#include "models/Model.h"
#include "models/Plane.h"

#include "models/City.h"

#include "models/Texture.h"
#include "models/Shader.h"
#include "models/Skybox.h"

#include "scene/scene_graph_node.h"

#include <filesystem>
#include <iostream>
#include <cstdio>

#define _USE_MATH_DEFINES
#include <math.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void setUpImGui(GLFWwindow* window);
void renderImGui(UserOptions& userOptions);

GLFWwindow* createWindow();

const unsigned int SCR_WIDTH = 1800;
const unsigned int SCR_HEIGHT = 900;

Camera camera(glm::vec3(-40.0f, 10.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true,kameraTramwajowa=false;

int speed = 1,timer1,timer2,timer3;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool forward=false, backward=false, open=false,firstDoor=false, secondDoor = false, thirdDoor = false, opening1=false ,opening2=false,opening3=false,close1 = false,close2 = false,close3=false ;
bool ImGuiKeyPressed = false;

int main()
{
	GLFWwindow* window = createWindow();

	if (window == NULL)
		return -1;

	UserOptions options;

	Shader basicShader("res/shaders/basic.vert", "res/shaders/basic.frag");
	Shader instancedShader("res/shaders/instanced.vert", "res/shaders/instanced.frag");
	
	Shader skyboxShader("res/shaders/skybox.vert", "res/shaders/skybox.frag");
	Shader reflectShader("res/shaders/reflect.vert", "res/shaders/reflect.frag");
	Shader refractShader("res/shaders/reflect.vert", "res/shaders/refract.frag");

	static const std::vector<std::string> faces
	{
		"res/textures/skybox/right.jpg",
		"res/textures/skybox/left.jpg",
		"res/textures/skybox/top.jpg",
		"res/textures/skybox/bottom.jpg",
		"res/textures/skybox/front.jpg",
		"res/textures/skybox/back.jpg"
	};
	Skybox skybox(faces);

	std::shared_ptr<SceneGraphNode> root(new SceneGraphNode(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	LoadedModel walls("res/models/house/house2.obj");
	LoadedModel roof("res/models/roof/roof.obj");
	
	
	// plane
	Plane groundPlane;
	std::shared_ptr<SceneGraphNode> groundNode(new SceneGraphNode);
	root->add_child(groundNode);
	groundPlane.setParentNode(groundNode);
	std::shared_ptr<SceneGraphNode> cityNode(new SceneGraphNode);
	root->add_child(cityNode);
	City city(cityNode, walls, roof);
	cityNode->set_position(-1000.0f, 0.0f, -250.0f);
	cityNode->set_scale(0.99f);
	LoadedModel tram("res/models/tram/untitled2.obj");
	std::shared_ptr<SceneGraphNode> tramNode(new SceneGraphNode);
	root->add_child(tramNode);
	tram.setParentNode(tramNode);
	tramNode->set_position(20.0f, 1.0f, 20.0f);
	tramNode->set_scale(4.0f);


	LoadedModel door1("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door1Node(new SceneGraphNode);
	tramNode->add_child(door1Node);
	door1.setParentNode(door1Node);
	door1Node->set_position(7.65f,0.0f,-0.1f);
	//door1Node->set_scale(0.9f);

	LoadedModel door2("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door2Node(new SceneGraphNode);
	tramNode->add_child(door2Node);
	door2.setParentNode(door2Node);
	door2Node->set_position(1.6f+5.35f, 0.0f, -0.1f);
	//door2Node->set_scale(0.9f);

	LoadedModel door3("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door3Node(new SceneGraphNode);
	tramNode->add_child(door3Node);
	door3.setParentNode(door3Node);
	door3Node->set_position(0.9f + 5.35f, 0.0f, -0.1f);
	door3Node->set_scale(1.0f);

	LoadedModel door4("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door4Node(new SceneGraphNode);
	tramNode->add_child(door4Node);
	door4.setParentNode(door4Node);
	door4Node->set_position(0.2f + 5.35f, 0.0f, -0.1f);
	door4Node->set_scale(1.0f);

	LoadedModel door5("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door5Node(new SceneGraphNode);
	tramNode->add_child(door5Node);
	door5.setParentNode(door5Node);
	door5Node->set_position(-5.85f + 5.35f, 0.0f, -0.1f);
	door5Node->set_scale(1.0f);

	LoadedModel door6("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door6Node(new SceneGraphNode);
	tramNode->add_child(door6Node);
	door6.setParentNode(door6Node);
	door6Node->set_position(-6.55f + 5.35f, 0.0f, -0.1f);
	door6Node->set_scale(1.0f);

	LoadedModel door7("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door7Node(new SceneGraphNode);
	tramNode->add_child(door7Node);
	door7.setParentNode(door7Node);
	door7Node->set_position(-7.25f + 5.35f, 0.0f, -0.1f);
	door7Node->set_scale(1.0f);
	
	LoadedModel door8("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door8Node(new SceneGraphNode);
	tramNode->add_child(door8Node);
	door8.setParentNode(door8Node);
	door8Node->set_position(-7.95f + 5.35f, 0.0f, -0.1f);
	door8Node->set_scale(1.0f);

	LoadedModel door9("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door9Node(new SceneGraphNode);
	tramNode->add_child(door9Node);
	door9.setParentNode(door9Node);
	door9Node->set_position(-13.27f + 5.35f, 0.0f, -0.1f);
	door9Node->set_scale(1.0f);

	LoadedModel door10("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door10Node(new SceneGraphNode);
	tramNode->add_child(door10Node);
	door10.setParentNode(door10Node);
	door10Node->set_position(-13.97f + 5.35f, 0.0f, -0.1f);
	door10Node->set_scale(1.0f);

	LoadedModel door11("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door11Node(new SceneGraphNode);
	tramNode->add_child(door11Node);
	door11.setParentNode(door11Node);
	door11Node->set_position(-14.67f + 5.35f, 0.0f, -0.1f);
	door11Node->set_scale(1.0f);

	LoadedModel door12("res/models/tram/doorNew.obj");
	std::shared_ptr<SceneGraphNode> door12Node(new SceneGraphNode);
	tramNode->add_child(door12Node);
	door12.setParentNode(door12Node);
	door12Node->set_position(-15.37f + 5.35f, 0.0f, -0.1f);
	door12Node->set_scale(1.0f);

	LoadedModel linki("res/models/tram/linki.obj");
	std::shared_ptr<SceneGraphNode> linki1Node(new SceneGraphNode);
	tramNode->add_child(linki1Node);
	linki.setParentNode(linki1Node);
	linki1Node->set_position(0.0f,-0.5f,0.5f);
	

	setUpImGui(window);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		options.spotLightPosition[0]=tramNode->position()+glm::vec3(35,0,0);
		options.spotLightPosition[1] = tramNode->position() + glm::vec3(35, 0, 8.5);


		processInput(window);

		if (ImGuiKeyPressed == true)
		{
			glfwSetCursorPosCallback(window, NULL);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetCursorPosCallback(window, mouse_callback);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		if (forward) {
			glm::vec3 temp=tramNode->position();
			temp = temp + glm::vec3(16*deltaTime*speed, 0, 0);
			tramNode->set_position(temp);
		}

		if (backward) {
			glm::vec3 temp2 = tramNode->position();
			temp2 = temp2 + glm::vec3(-1* 16 * deltaTime * speed, 0, 0);
			tramNode->set_position(temp2);
		}

		if (kameraTramwajowa) {
			camera.Position = tramNode->position()+glm::vec3(15,20,5);
		}

		if (firstDoor) {
			//close1 = false;
			if (!opening1) {
				opening1 = true;
				timer1 = 200;
			}
			if (timer1 != 0) {
				timer1--;


				glm::vec3 temp2 = door1Node->position();
				temp2 = temp2 + glm::vec3(0.001, 0, 0);
				door1Node->set_position(temp2);
				float ftemp2= glm::eulerAngles(door1Node->orientation())[1];
				door1Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);


				temp2 = door2Node->position();
				temp2 = temp2 + glm::vec3(0.003, 0, 0);
				door2Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door2Node->orientation())[1];
				door2Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);

				temp2 = door3Node->position();
				temp2 = temp2 - glm::vec3(0.003, 0, 0);
				door3Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door3Node->orientation())[1];
				door3Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);

				temp2 = door4Node->position();
				temp2 = temp2 - glm::vec3(0.001, 0, 0);
				door4Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door4Node->orientation())[1];
				door4Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);

			}
	
		}

		if (close1) {
			//firstDoor = false;
			if (opening1) {
				opening1 = false;
				timer1 = 200; 

				}

			if(timer1 !=0){
				timer1--;

				glm::vec3 temp2 = door1Node->position();
				temp2 = temp2 - glm::vec3(0.001, 0, 0);
				door1Node->set_position(temp2);
				float ftemp2 = glm::eulerAngles(door1Node->orientation())[1];
				door1Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);


				temp2 = door2Node->position();
				temp2 = temp2 - glm::vec3(0.003, 0, 0);
				door2Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door2Node->orientation())[1];
				door2Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);

				temp2 = door3Node->position();
				temp2 = temp2 + glm::vec3(0.003, 0, 0);
				door3Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door3Node->orientation())[1];
				door3Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);

				temp2 = door4Node->position();
				temp2 = temp2 + glm::vec3(0.001, 0, 0);
				door4Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door4Node->orientation())[1];
				door4Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);
			}
		}

		if (secondDoor) {
			//close1 = false;
			if (!opening2) {
				opening2 = true;
				timer2 = 200;
			}
			if (timer2 != 0) {
				timer2--;


				glm::vec3 temp2 = door5Node->position();
				temp2 = temp2 + glm::vec3(0.001, 0, 0);
				door5Node->set_position(temp2);
				float ftemp2 = glm::eulerAngles(door5Node->orientation())[1];
				door5Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);


				temp2 = door6Node->position();
				temp2 = temp2 + glm::vec3(0.003, 0, 0);
				door6Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door6Node->orientation())[1];
				door6Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);

				temp2 = door7Node->position();
				temp2 = temp2 - glm::vec3(0.003, 0, 0);
				door7Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door7Node->orientation())[1];
				door7Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);

				temp2 = door8Node->position();
				temp2 = temp2 - glm::vec3(0.001, 0, 0);
				door8Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door8Node->orientation())[1];
				door8Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);

			}

		}

		if (close2) {
			//firstDoor = false;
			if (opening2) {
				opening2 = false;
				timer2 = 200;

			}

			if (timer2 != 0) {
				timer2--;

				glm::vec3 temp2 = door5Node->position();
				temp2 = temp2 - glm::vec3(0.001, 0, 0);
				door5Node->set_position(temp2);
				float ftemp2 = glm::eulerAngles(door5Node->orientation())[1];
				door5Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);


				temp2 = door6Node->position();
				temp2 = temp2 - glm::vec3(0.003, 0, 0);
				door6Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door6Node->orientation())[1];
				door6Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);

				temp2 = door7Node->position();
				temp2 = temp2 + glm::vec3(0.003, 0, 0);
				door7Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door7Node->orientation())[1];
				door7Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);

				temp2 = door8Node->position();
				temp2 = temp2 + glm::vec3(0.001, 0, 0);
				door8Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door8Node->orientation())[1];
				door8Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);
			}
		}

		if (thirdDoor) {
			
			if (!opening3) {
				opening3 = true;
				timer3 = 200;
			}
			if (timer3 != 0) {
				timer3--;


				glm::vec3 temp2 = door9Node->position();
				temp2 = temp2 + glm::vec3(0.001, 0, 0);
				door9Node->set_position(temp2);
				float ftemp2 = glm::eulerAngles(door9Node->orientation())[1];
				door9Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);


				temp2 = door10Node->position();
				temp2 = temp2 + glm::vec3(0.003, 0, 0);
				door10Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door10Node->orientation())[1];
				door10Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);

				temp2 = door11Node->position();
				temp2 = temp2 - glm::vec3(0.003, 0, 0);
				door11Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door11Node->orientation())[1];
				door11Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);

				temp2 = door12Node->position();
				temp2 = temp2 - glm::vec3(0.001, 0, 0);
				door12Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door12Node->orientation())[1];
				door12Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);

			}
			
		}

		if (close3) {
			//firstDoor = false;
			
			if (opening3) {
				opening3 = false;
				timer3 = 200;

			}

			if (timer3 != 0) {
				timer3--;

				glm::vec3 temp2 = door9Node->position();
				temp2 = temp2 - glm::vec3(0.001, 0, 0);
				door9Node->set_position(temp2);
				float ftemp2 = glm::eulerAngles(door9Node->orientation())[1];
				door9Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);


				temp2 = door10Node->position();
				temp2 = temp2 - glm::vec3(0.003, 0, 0);
				door10Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door10Node->orientation())[1];
				door10Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);

				temp2 = door11Node->position();
				temp2 = temp2 + glm::vec3(0.003, 0, 0);
				door11Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door11Node->orientation())[1];
				door11Node->set_orienatation(0, glm::degrees(ftemp2 + 0.006), 0);

				temp2 = door12Node->position();
				temp2 = temp2 + glm::vec3(0.001, 0, 0);
				door12Node->set_position(temp2);
				ftemp2 = glm::eulerAngles(door12Node->orientation())[1];
				door12Node->set_orienatation(0, glm::degrees(ftemp2 - 0.006), 0);
			}
		}









			renderImGui(options);

		// render
		glClearColor(0.8f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// configure transformation matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		options.view = view;
		options.projection = projection;
		options.cameraPosition = camera.Position;

		skyboxShader.use();
		skyboxShader.setMat4("projection", projection);
		skyboxShader.setMat4("view", view);
		skybox.Draw(skyboxShader);

		tram.Draw(basicShader);

		options.updateShader(basicShader);
		groundPlane.Draw(basicShader);

		options.updateShader(instancedShader);

		city.Draw(instancedShader);


		reflectShader.use();
		reflectShader.setMat4("projection", projection);
		reflectShader.setMat4("view", view);
		reflectShader.setVec3("cameraPos", camera.Position);

		door1.Draw(reflectShader);
		door2.Draw(reflectShader);
		door3.Draw(reflectShader);
		door4.Draw(reflectShader);
		door5.Draw(reflectShader);
		door6.Draw(reflectShader);
		door7.Draw(reflectShader);
		door8.Draw(reflectShader);
		door9.Draw(reflectShader);
		door10.Draw(reflectShader);
		door11.Draw(reflectShader);
		door12.Draw(reflectShader);

		refractShader.use();
		refractShader.setMat4("projection", projection);
		refractShader.setMat4("view", view);
		refractShader.setVec3("cameraPos", camera.Position);
		linki.Draw(refractShader);

		root->update(glm::mat4(1.0f), false);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		firstDoor = true;
		close1 = false;
		
	}
		
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		secondDoor = true;
		close2 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		thirdDoor = true;
		close3 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		close1 = true;
		firstDoor = false;
	}
		
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		close2 = true;
		secondDoor = false;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		close3 = true;
		thirdDoor = false;
	}
	if (!kameraTramwajowa) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, 8 * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, 8 * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, 8 * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, 8 * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			camera.ProcessKeyboard(UPWARD, 8 * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(DOWNWARD, 8 * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	

	
	
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		forward = true;
	}
	else {
		forward = false;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		backward = true;
	}
	else {
		backward = false;
	}

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		ImGuiKeyPressed = !ImGuiKeyPressed;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
	//if (!kameraTramwajowa) {
		camera.ProcessMouseMovement(xoffset, yoffset);
	//}
	

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

GLFWwindow* createWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tramwaj w Night City", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	glEnable(GL_DEPTH_TEST);
	return window;
}

void setUpImGui(GLFWwindow* window) {

	const char* glsl_version = "#version 430";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGui::StyleColorsDark();

}

void renderImGui(UserOptions& userOptions) {

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Ustawienia");
	ImGui::Checkbox("Kamera Tramwajowa", &kameraTramwajowa);
	ImGui::Text("Swiatlo kierunkowe");
	ImGui::Checkbox("Wylacz", &userOptions.showDirLight);
	ImGui::Checkbox("Pokaz kierunek", &userOptions.showDirLightPosition);
	ImGui::ColorEdit3("Kolor ambient", (float*)&userOptions.directionalLightAmbientColor);
	ImGui::ColorEdit3("Kolor diffuse", (float*)&userOptions.directionalLightDiffuseColor);
	ImGui::ColorEdit3("Kolor specular", (float*)&userOptions.directionalLightSpecularColor);
	ImGui::SliderFloat("Zmien kierunek x", &userOptions.dirLightDirection.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Zmien kierunek y", &userOptions.dirLightDirection.y, -1.0f, 1.0f);
	ImGui::SliderFloat("Zmien kierunek  z", &userOptions.dirLightDirection.z, -1.0f, 1.0f);

	ImGui::Text("Pierwszy reflektor");
	ImGui::Checkbox("Wylacz prawy reflektor", &userOptions.showRefLight[0]);
	ImGui::Checkbox("Pokaz kierunek prawego reflektora", &userOptions.showRefLightPosition[0]);
	ImGui::ColorEdit3("Kolor ambient prawego reflektora", (float*)&userOptions.spotLightAmbientColor[0]);
	ImGui::ColorEdit3("Kolor diffuse prawego reflektora", (float*)&userOptions.spotLightDiffuseColor[0]);
	ImGui::ColorEdit3("Kolor specular prawego reflektora", (float*)&userOptions.spotLightSpecularColor[0]);
	ImGui::SliderFloat("Zmien kierunek swiatla relektora prawego x", &userOptions.spotLightDirection[0].x, -1.0f, 1.0f);
	ImGui::SliderFloat("Zmien kierunek swiatla relektora prawego y", &userOptions.spotLightDirection[0].y, -1.0f, 1.0f);
	ImGui::SliderFloat("Zmien kierunek swiatla relektora prawego z", &userOptions.spotLightDirection[0].z, -1.0f, 1.0f);
	ImGui::Text(" ");
	ImGui::SliderFloat("Zmien pozycje x pierwszego reflektora", &userOptions.spotLightPosition[0].x, -100.0f, 100.0f);
	ImGui::SliderFloat("Zmien pozycje y pierwszego reflektora", &userOptions.spotLightPosition[0].y, 0.0f, 100.0f);
	ImGui::SliderFloat("Zmien pozycje z pierwszego reflektora", &userOptions.spotLightPosition[0].z, -100.0f, 100.0f);

	ImGui::Text("Drugi reflektor");
	ImGui::Checkbox("Wylacz lewy reflektor", &userOptions.showRefLight[1]);
	ImGui::Checkbox("Pokaz kierunek lewego reflektora", &userOptions.showRefLightPosition[1]);
	ImGui::ColorEdit3("Kolor ambient lewego reflektora", (float*)&userOptions.spotLightAmbientColor[1]);
	ImGui::ColorEdit3("Kolor diffuse lewego reflektora", (float*)&userOptions.spotLightDiffuseColor[1]);
	ImGui::ColorEdit3("Kolor specular lewego reflektora", (float*)&userOptions.spotLightSpecularColor[1]);
	ImGui::SliderFloat("Zmien kierunek swiatla relektora lewego x", &userOptions.spotLightDirection[1].x, -1.0f, 1.0f);
	ImGui::SliderFloat("Zmien kierunek swiatla relektora lewego y", &userOptions.spotLightDirection[1].y, -1.0f, 1.0f);
	ImGui::SliderFloat("Zmien kierunek swiatla relektora lewego z", &userOptions.spotLightDirection[1].z, -1.0f, 1.0f);
	ImGui::Text(" ");
	ImGui::SliderFloat("Zmien pozycje x drugiego reflektora", &userOptions.spotLightPosition[1].x, -100.0f, 100.0f);
	ImGui::SliderFloat("Zmien pozycje y drugiego reflektora", &userOptions.spotLightPosition[1].y, 0.0f, 100.0f);
	ImGui::SliderFloat("Zmien pozycje z drugiego reflektora", &userOptions.spotLightPosition[1].z, -100.0f, 100.0f);


	ImGui::End();
	ImGui::Render();
}

