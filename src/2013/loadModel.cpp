// ����GLEW�� ���徲̬����
#define GLEW_STATIC
#include <GLEW/glew.h>
// ����GLFW��
#include <GLFW/glfw3.h>
// ����SOIL��
#include <SOIL/SOIL.h>
// ����GLM��
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include <stdio.h>
#include <iostream>

#include <vector>
#include <cstdlib>
// ������ɫ�����ؿ�
#include "shader.h"
// ����������Ƹ�����
#include "camera.h"
// �������������
#include "texture.h"
// ����ģ�͵���
#include "model.h"
using namespace std;

// ���̻ص�����ԭ������
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// ����ƶ��ص�����ԭ������
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
// �����ֻص�����ԭ������
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// �������ƶ�
void do_movement();

// ���������
const int WINDOW_WIDTH = 1600, WINDOW_HEIGHT = 800;
// ���������������
GLfloat lastX = WINDOW_WIDTH / 2.0f, lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouseMove = true;
bool keyPressedStatus[1024]; // ���������¼
GLfloat deltaTime = 1.0f; // ��ǰ֡����һ֡��ʱ���
GLfloat lastFrame = 0.0f; // ��һ֡ʱ��
Camera camera(glm::vec3(25.0f, -20.0f, 200.0f));

glm::vec3 plane_pos(0.0f, 0.0f, 0.0f);
glm::vec3 plane1_pos(0.0f, 0.0f, 0.0f);
glm::vec3 plane_angle(0.0f, 0.0f, 0.0f);
glm::vec3 plane_axis(0.0f, 0.0f, 0.0f);

GLfloat weizhi[5900];

int main(int argc, char** argv)
{
	//string sline,str;//ÿһ��
	//string out;
	//string s1, s2, s3, s4;


	//while (getline(inf, sline))
	//{   
	//	int i = 0;
	//	istringstream sin(sline);
	//	while (sin >> str)
	//	{
	//		weizhi = str;
	//	}
	//		weizhi[i] = sline;
	//}
	//��ȡ����
	ifstream inf;
	inf.open("d://out.txt");
	
	GLfloat x, y, z;
	
	int i = 0;
	while (inf >> x >> y >> z)
	{
		weizhi[i] = x;
		weizhi[i + 1] = y;
		weizhi[i + 2] = z;
		i += 3;
	}

	int zong = i;
	i = 0;
	cout << zong << endl;
	for (i = 0;i<=zong;i++)
	{
		cout << GLfloat(weizhi[i]) << endl;
	}

	if (!glfwInit())	// ��ʼ��glfw��
	{
		std::cout << "Error::GLFW could not initialize GLFW!" << std::endl;
		return -1;
	}

	// ����OpenGL 3.3 core profile
	std::cout << "Start OpenGL core profile version 3.3" << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// ��������
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
		"OPENGL-H6", NULL, NULL);
	if (!window)
	{
		std::cout << "Error::GLFW could not create winddow!" << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	// �����Ĵ��ڵ�contextָ��Ϊ��ǰcontext
	glfwMakeContextCurrent(window);

	// ע�ᴰ�ڼ����¼��ص�����
	glfwSetKeyCallback(window, key_callback);
	// ע������¼��ص�����
	glfwSetCursorPosCallback(window, mouse_move_callback);
	// ע���������¼��ص�����
	glfwSetScrollCallback(window, mouse_scroll_callback);
	// ��겶�� ͣ���ڳ�����
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// ��ʼ��GLEW ��ȡOpenGL����
	glewExperimental = GL_TRUE; // ��glew��ȡ������չ����
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cout << "Error::GLEW glew version:" << glewGetString(GLEW_VERSION)
			<< " error string:" << glewGetErrorString(status) << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}

	// �����ӿڲ���
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//Section1 ����ģ������ Ϊ�˷������ģ�� ���Ǵ��ļ���ȡģ���ļ�·��
	//��һ��ģ��
	Model objModel1;
	std::ifstream modelPath("modelPath1.txt");
	if (!modelPath)
	{
		std::cerr << "Error::could not read model path file." << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	std::string modelFilePath;
	std::getline(modelPath, modelFilePath);
	if (modelFilePath.empty())
	{
		std::cerr << "Error::model path empty." << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	if (!objModel1.loadModel(modelFilePath))
	{
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	//�ڶ���ģ��
	Model objModel2;
	std::ifstream modelPath2("modelPath2.txt");
	if (!modelPath)
	{
		std::cerr << "Error::could not read model path file." << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	std::string modelFilePath2;
	std::getline(modelPath2, modelFilePath2);
	if (modelFilePath.empty())
	{
		std::cerr << "Error::model path empty." << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	if (!objModel2.loadModel(modelFilePath2))
	{
		glfwTerminate();
		std::system("pause");
		return -1;
	}

	// ָ����Χ�еĶ������� λ��
	GLfloat skyboxVertices[] = {
		// ����
		-1.0f, 1.0f, -1.0f,		// A
		-1.0f, -1.0f, -1.0f,	// B
		1.0f, -1.0f, -1.0f,		// C
		1.0f, -1.0f, -1.0f,		// C
		1.0f, 1.0f, -1.0f,		// D
		-1.0f, 1.0f, -1.0f,		// A

		// �����
		-1.0f, -1.0f, 1.0f,		// E
		-1.0f, -1.0f, -1.0f,	// B
		-1.0f, 1.0f, -1.0f,		// A
		-1.0f, 1.0f, -1.0f,		// A
		-1.0f, 1.0f, 1.0f,		// F
		-1.0f, -1.0f, 1.0f,		// E

		// �Ҳ���
		1.0f, -1.0f, -1.0f,		// C
		1.0f, -1.0f, 1.0f,		// G
		1.0f, 1.0f, 1.0f,		// H
		1.0f, 1.0f, 1.0f,		// H
		1.0f, 1.0f, -1.0f,		// D
		1.0f, -1.0f, -1.0f,		// C

		// ����
		-1.0f, -1.0f, 1.0f,  // E
		-1.0f, 1.0f, 1.0f,  // F
		1.0f, 1.0f, 1.0f,  // H
		1.0f, 1.0f, 1.0f,  // H
		1.0f, -1.0f, 1.0f,  // G
		-1.0f, -1.0f, 1.0f,  // E

		// ����
		-1.0f, 1.0f, -1.0f,  // A
		1.0f, 1.0f, -1.0f,  // D
		1.0f, 1.0f, 1.0f,  // H
		1.0f, 1.0f, 1.0f,  // H
		-1.0f, 1.0f, 1.0f,  // F
		-1.0f, 1.0f, -1.0f,  // A

		// ����
		-1.0f, -1.0f, -1.0f,  // B
		-1.0f, -1.0f, 1.0f,   // E
		1.0f, -1.0f, 1.0f,    // G
		1.0f, -1.0f, 1.0f,    // G
		1.0f, -1.0f, -1.0f,   // C
		-1.0f, -1.0f, -1.0f,  // B
	};


	// Section2 ׼���������
	GLuint cubeVAOId, cubeVBOId;
	glGenVertexArrays(1, &cubeVAOId);
	glGenBuffers(1, &cubeVBOId);
	glBindVertexArray(cubeVAOId);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBOId);

	// ����λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// ������������
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	GLuint skyBoxVAOId, skyBoxVBOId;
	glGenVertexArrays(1, &skyBoxVAOId);
	glGenBuffers(1, &skyBoxVBOId);
	glBindVertexArray(skyBoxVAOId);
	glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	// ����λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Section3 ��������

	std::vector<const char*> faces;
	faces.push_back("../../resources/skyboxes/sky/sky_rt.jpg");
	faces.push_back("../../resources/skyboxes/sky/sky_lf.jpg");
	faces.push_back("../../resources/skyboxes/sky/sky_up.jpg");
	faces.push_back("../../resources/skyboxes/sky/sky_dn.jpg");
	faces.push_back("../../resources/skyboxes/sky/sky_bk.jpg");
	faces.push_back("../../resources/skyboxes/sky/sky_ft.jpg");
	// 
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_rt.tga");
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_lf.tga");
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_up.tga");
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_dn.tga");
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_bk.tga");
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_ft.tga");
	GLuint skyBoxTextId = TextureHelper::loadCubeMapTexture(faces);

	// Section2 ׼����ɫ������
	Shader shadermodel1("model1.vertex", "model1.frag");
	Shader shadermodel2("model2.vertex", "model2.frag");

	Shader shader("scene.vertex", "scene.frag");
	Shader skyBoxShader("skybox.vertex", "skybox.frag");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	i = 2;
	// ��ʼ��Ⱦ������ѭ��
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents(); // ����������� ���̵��¼�
		do_movement(); // �����û�������� �����������

		// �����ɫ������ ����Ϊָ����ɫ
		glClearColor(0.18f, 0.04f, 0.14f, 1.0f);
		// ���colorBuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ����model
		shadermodel1.use();
		//shadermodel2.use();
		//��һ���д������÷�   //��һ������




		//��������ߵ�����
		glViewport(0, 0, 800, 800);//ע�⣬���������������Ǹ߶ȺͿ�ȣ�����������

		// ���Ƴ���
		shader.use();
		glm::mat4 projection = glm::perspective(camera.mouse_zoom,
			(GLfloat)(WINDOW_WIDTH) / WINDOW_HEIGHT, 1.0f, 100000.0f); // ͶӰ����
		glm::mat4 view = camera.getViewMatrix(); // �ӱ任����
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "projection"),
			1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "view"),
			1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // �ʵ�����λ��
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // �ʵ���Сģ��


		// Ȼ����ư�Χ��  ʹ��Χ��ԭ��λ�ڹ۲���λ�ò�ʹ������
		glDepthFunc(GL_LEQUAL); // ��Ȳ������� С�ڵ���
		skyBoxShader.use();
		glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "projection"),
			1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "view"),
			1, GL_FALSE, glm::value_ptr(view));

		glBindVertexArray(skyBoxVAOId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTextId); // ע��󶨵�CUBE_MAP
		glUniform1i(glGetUniformLocation(skyBoxShader.programId, "skybox"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);//���������ͼ



		// ������д�������ƴ���
		model = glm::translate(glm::mat4(), camera.position);
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "model"),
			1, GL_FALSE, glm::value_ptr(model));

		glm::mat4 view_mat = glm::translate(glm::mat4(), -camera.position);

		shader.use();
		model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); // �ʵ��������е�λ��
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // �ʵ���Сģ��2
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"),
			1, GL_FALSE, glm::value_ptr(model));
		objModel2.draw(shader); // ��������2

		plane_pos.x = weizhi[i];
		plane_pos.y = weizhi[i + 1];
		plane_pos.z = weizhi[i + 2];
		if (i == zong - 1){ i = 0; }
		else { i += 3; }

	//	model = glm::translate(glm::mat4(), glm::vec3(plane_pos.x - weizhi[i - 3], plane_pos.y - weizhi[i - 2], plane_pos.z - weizhi[i - 1])); // �ɻ��ƶ�

		model = glm::translate(glm::mat4(), glm::vec3(plane_pos.x, plane_pos.y, plane_pos.z)); // �ɻ��ƶ�
		

		//    model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f + plane_pos.y, 0.0f + plane_pos.z)); // �ɻ��ƶ�����

		//model = glm::rotate(model, plane_pos.y/100, glm::vec3(0.0f, 1.0f, 0.0f)); // ��ת

	//	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // �ʵ���Сģ��1

		//view = glm::lookAt(glm::vec3(plane_pos.x, plane_pos.y, plane_pos.z), glm::vec3(plane_pos.x+0., plane_pos.y, plane_pos.z), glm::vec3(0,0,1));

		shader.use();
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"),
			1, GL_FALSE, glm::value_ptr(model));

		objModel1.draw(shader); // ��������1


		
		//camera.position = plane_pos;   //�������ɻ�ͬ��
		// camera.yawAngle = plane_angle.x;

		glEnable(GL_BLEND);

		glBindVertexArray(0);
		glUseProgram(0);




		//�������ұߵ�����
		glViewport(800, 0, 800, 800);//ע�⣬���������������Ǹ߶ȺͿ�ȣ�����������
		// ���Ƴ���
		shader.use();
		glm::mat4 projection1 = glm::perspective(camera.mouse_zoom,
			(GLfloat)(WINDOW_WIDTH) / WINDOW_HEIGHT, 1.0f, 10000.0f); // ͶӰ����
		glm::mat4 view1 = camera.getViewMatrix(); // �ӱ任����
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "projection1"),
			1, GL_FALSE, glm::value_ptr(projection1));
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "view1"),
			1, GL_FALSE, glm::value_ptr(view1));
		glm::mat4 model1;
		//model1 = glm::translate(model1, glm::vec3(0.0f, 0.0f, 0.0f)); // �ʵ�����λ��
		//model1 = glm::scale(model1, glm::vec3(0.2f, 0.2f, 0.2f)); // �ʵ���Сģ��


		// Ȼ����ư�Χ��  ʹ��Χ��ԭ��λ�ڹ۲���λ�ò�ʹ������
		glDepthFunc(GL_LEQUAL); // ��Ȳ������� С�ڵ���
		skyBoxShader.use();
		glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "projection1"),
			1, GL_FALSE, glm::value_ptr(projection1));
		glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "view1"),
			1, GL_FALSE, glm::value_ptr(view1));

		glBindVertexArray(skyBoxVAOId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTextId); // ע��󶨵�CUBE_MAP
		glUniform1i(glGetUniformLocation(skyBoxShader.programId, "skybox"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);//���������ͼ



		// ������д�������ƴ���
		//model1 = glm::translate(glm::mat4(), camera.position);
		//model1 = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		//glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "model1"),
		//	1, GL_FALSE, glm::value_ptr(model1));

		//glm::mat4 view1_mat = glm::translate(glm::mat4(), -camera.position);


		shader.use();
		model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); // �ʵ��������е�λ��
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // �ʵ���Сģ��2
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"),
			1, GL_FALSE, glm::value_ptr(model));
		objModel2.draw(shader); // ��������2



		shader.use();
		model = glm::translate(glm::mat4(), glm::vec3(plane1_pos.x, plane1_pos.y, plane1_pos.z)); // �ɻ��ƶ�

		//model = glm::rotate(model, plane1_pos.y/100, glm::vec3(0.0f, 1.0f, 0.0f)); // ��ת

		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // �ʵ���Сģ��1

		//view = glm::lookAt(glm::vec3(plane_pos.x, plane_pos.y, plane_pos.z), glm::vec3(plane_pos.x+0., plane_pos.y, plane_pos.z), glm::vec3(0,0,1));

		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"),
			1, GL_FALSE, glm::value_ptr(model));

		plane1_pos.z += 0.5;
		plane1_pos.y += 0.3;
		cout << plane1_pos.z << " " << plane1_pos.y << "xxxxxx" 
			<< plane_pos.x << " " << plane_pos.y << " " << plane_pos.z << endl;
		//camera.position = plane_pos;   //�������ɻ�ͬ��
		// camera.yawAngle = plane_angle.x;
		objModel1.draw(shader); // ��������1


		//glEnable(GL_BLEND);

		//	glBindVertexArray(0);
		//	glUseProgram(0);
		
		glfwSwapBuffers(window); // ��������
		
	}


	//���������Ͻǵ�����
	//glViewport(400, 400, 400, 400);//ע�⣬���������������Ǹ߶ȺͿ�ȣ�����������

	//���������½ǵ�����
	//glViewport(0, 0, 400, 400);//ע�⣬���������������Ǹ߶ȺͿ�ȣ�����������

	//���������Ͻǵ�����
	//glViewport(0, 400, 400, 400);//ע�⣬���������������Ǹ߶ȺͿ�ȣ�����������	

	//���������½ǵ�����
	//glViewport(400, 0, 400, 400);//ע�⣬���������������Ǹ߶ȺͿ�ȣ�����������

	// �ͷ���Դ
	glfwTerminate();
	inf.close();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keyPressedStatus[key] = true;
		else if (action == GLFW_RELEASE)
			keyPressedStatus[key] = false;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE); // �رմ���
	}
}
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouseMove) // �״�����ƶ�
	{
		lastX = xpos;
		lastY = ypos;
		firstMouseMove = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.handleMouseMove(xoffset, yoffset);
}
// ����������ദ�������ֿ���
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.handleMouseScroll(yoffset);
}
// ����������ദ����̿���
void do_movement()
{

	if (keyPressedStatus[GLFW_KEY_W])
		camera.handleKeyPress(FORWARD, deltaTime);
	if (keyPressedStatus[GLFW_KEY_S])
		camera.handleKeyPress(BACKWARD, deltaTime);
	if (keyPressedStatus[GLFW_KEY_A])
		camera.handleKeyPress(LEFT, deltaTime);
	if (keyPressedStatus[GLFW_KEY_D])
		camera.handleKeyPress(RIGHT, deltaTime);
}