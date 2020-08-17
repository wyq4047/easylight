#include"Textures.h"
#include<SOIL/SOIL.h>


const std::string strs[] = {
	"./res/container.jpg",
	"./res/liuhua.jpg"
};

myTexture::myTexture(int i)
{
	nums = i;
	m_textures = new GLuint[i]; 
	for (int j = 0; j < i; j++) {
		if(j==0) Load1(strs[j], j);
		else Load2(strs[j], j);
	}
	 
}



myTexture::myTexture() {
	// Load and create a texture 

	// ====================
	// myTexture 1
	// ====================
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // Note that we set our container wrapping method to GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);    // Note that we set our container wrapping method to GL_CLAMP_TO_EDGE
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	/*
	int width, height, n;
	unsigned char* image = stbi_load(strs[0].c_str(), &width, &height, &n, 0);
	*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	// ===================
	// myTexture 2
	// ===================
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // We want to repeat this pattern so we set kept it at GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   // We want to repeat this pattern so we set kept it at GL_REPEAT
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	//image = stbi_load(strs[1].c_str(), &width, &height, &n, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void myTexture::Load1(const std::string str, GLuint index)
{
	glGenTextures(1, &m_textures[index]);
	//�������������1���洢�ڵڶ������������У�GLuint���飩
	glBindTexture(GL_TEXTURE_2D, m_textures[index]);
	std::cout << "here";
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //  GL_CLAMP_TO_EDGE
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//��һ������ָ��������Ŀ�ꣻ
	//����ʹ�õ���2D�����������Ŀ����GL_TEXTURE_2D��
	//�ڶ���������Ҫ����ָ�����õ�ѡ����Ӧ�õ������ᡣ
	//���Ǵ������õ���WRAPѡ�����ָ��S��T�ᡣ
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//��һ������ָ��������Ŀ��(Target)������ΪGL_TEXTURE_2D��ζ�Ż������뵱ǰ�󶨵����������ͬһ��Ŀ���ϵ������κΰ󶨵�GL_TEXTURE_1D��GL_TEXTURE_3D���������ܵ�Ӱ�죩��
	//�ڶ�������Ϊ����ָ���༶��Զ����ļ��������ϣ�������ֶ�����ÿ���༶��Զ����ļ���Ļ�������������0��Ҳ���ǻ�������
	//��������������OpenGL����ϣ����������Ϊ���ָ�ʽ�����ǵ�ͼ��ֻ��RGBֵ���������Ҳ��������ΪRGBֵ��
	//���ĸ��͵���������������յ�����Ŀ�Ⱥ͸߶ȡ�����֮ǰ����ͼ���ʱ�򴢴������ǣ���������ʹ�ö�Ӧ�ı�����
	//�¸�����Ӧ�����Ǳ���Ϊ0����ʷ�������⣩��
	//���ߵڰ˸�����������Դͼ�ĸ�ʽ���������͡�����ʹ��RGBֵ�������ͼ�񣬲������Ǵ���Ϊchar(byte)���飬���ǽ��ᴫ���Ӧֵ��
	//���һ��������������ͼ�����ݡ�
	glGenerateMipmap(GL_TEXTURE_2D);
	//Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void myTexture::Load2(const std::string str,GLuint index) 
{ 
	glGenTextures(1, &m_textures[index]);
	//�������������1���洢�ڵڶ������������У�GLuint���飩
	glBindTexture(GL_TEXTURE_2D, m_textures[index]);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//��һ������ָ��������Ŀ�ꣻ
	//����ʹ�õ���2D�����������Ŀ����GL_TEXTURE_2D��
	//�ڶ���������Ҫ����ָ�����õ�ѡ����Ӧ�õ������ᡣ
	//���Ǵ������õ���WRAPѡ�����ָ��S��T�ᡣ
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//��һ������ָ��������Ŀ��(Target)������ΪGL_TEXTURE_2D��ζ�Ż������뵱ǰ�󶨵����������ͬһ��Ŀ���ϵ������κΰ󶨵�GL_TEXTURE_1D��GL_TEXTURE_3D���������ܵ�Ӱ�죩��
	//�ڶ�������Ϊ����ָ���༶��Զ����ļ��������ϣ�������ֶ�����ÿ���༶��Զ����ļ���Ļ�������������0��Ҳ���ǻ�������
	//��������������OpenGL����ϣ����������Ϊ���ָ�ʽ�����ǵ�ͼ��ֻ��RGBֵ���������Ҳ��������ΪRGBֵ��
	//���ĸ��͵���������������յ�����Ŀ�Ⱥ͸߶ȡ�����֮ǰ����ͼ���ʱ�򴢴������ǣ���������ʹ�ö�Ӧ�ı�����
	//�¸�����Ӧ�����Ǳ���Ϊ0����ʷ�������⣩��
	//���ߵڰ˸�����������Դͼ�ĸ�ʽ���������͡�����ʹ��RGBֵ�������ͼ�񣬲������Ǵ���Ϊchar(byte)���飬���ǽ��ᴫ���Ӧֵ��
	//���һ��������������ͼ�����ݡ�
	glGenerateMipmap(GL_TEXTURE_2D);
	//Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void myTexture::Bind(GLuint& program)
{
	std::string str2[] = { "ourTexture1" ,"ourTexture2" };
	for (int i = 0; i < nums; i++) {
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		glUniform1i(glGetUniformLocation(program, str2[i].c_str()), i);
	}
}

void myTexture::Bind2(GLuint& program,int num){
	for (int i = 0; i < num; i++) {
		glActiveTexture(GL_TEXTURE0+i); //�����Ȼ������
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
	}
}

myTexture::myTexture(std::string str[], int num)
{
	m_textures = new GLuint[num];
	for (int i = 0; i < num; i++) {
		glGenTextures(1, &m_textures[i]);
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		int width, height;
		unsigned char* image;
		image = SOIL_load_image(str[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // We want to repeat this pattern so we set kept it at GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   // We want to repeat this pattern so we set kept it at GL_REPEAT
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void myTexture::Bind(std::string names[], int num) {
	for (int i = 0; i < num; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D,m_textures[i]);
	}
}


