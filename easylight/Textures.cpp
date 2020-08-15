#include"Textures.h"



const std::string strs[] = {
	"./res/container.jpg",
	"./res/liuhua.jpg"
};

Texture::Texture(int i)
{
	nums = i;
	m_textures = new GLuint[i]; 
	for (int j = 0; j < i; j++) {
		if(j==0) Load1(strs[j], j);
		else Load2(strs[j], j);
	}
	 
}

Texture::Texture() {
	// Load and create a texture 

	// ====================
	// Texture 1
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
	int width, height, n;
	unsigned char* image = stbi_load(strs[0].c_str(), &width, &height, &n, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	// ===================
	// Texture 2
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
	image = stbi_load(strs[1].c_str(), &width, &height, &n, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Load1(const std::string str, GLuint index)
{
	glGenTextures(1, &m_textures[index]);
	//生成纹理的数量1，存储在第二个参数数组中（GLuint数组）
	glBindTexture(GL_TEXTURE_2D, m_textures[index]);
	std::cout << "here";
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //  GL_CLAMP_TO_EDGE
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//第一个参数指定了纹理目标；
	//我们使用的是2D纹理，因此纹理目标是GL_TEXTURE_2D。
	//第二个参数需要我们指定设置的选项与应用的纹理轴。
	//我们打算配置的是WRAP选项，并且指定S和T轴。
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, n;
	unsigned char* image = stbi_load(str.c_str(), &width, &height, &n, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
	//第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
	//第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
	//第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
	//下个参数应该总是被设为0（历史遗留问题）。
	//第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组，我们将会传入对应值。
	//最后一个参数是真正的图像数据。
	glGenerateMipmap(GL_TEXTURE_2D);
	//为当前绑定的纹理自动生成所有需要的多级渐远纹理。
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Load2(const std::string str,GLuint index) 
{ 
	glGenTextures(1, &m_textures[index]);
	//生成纹理的数量1，存储在第二个参数数组中（GLuint数组）
	glBindTexture(GL_TEXTURE_2D, m_textures[index]);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//第一个参数指定了纹理目标；
	//我们使用的是2D纹理，因此纹理目标是GL_TEXTURE_2D。
	//第二个参数需要我们指定设置的选项与应用的纹理轴。
	//我们打算配置的是WRAP选项，并且指定S和T轴。
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, n;
	unsigned char* image = stbi_load(str.c_str(), &width, &height, &n, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
	//第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
	//第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
	//第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
	//下个参数应该总是被设为0（历史遗留问题）。
	//第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组，我们将会传入对应值。
	//最后一个参数是真正的图像数据。
	glGenerateMipmap(GL_TEXTURE_2D);
	//为当前绑定的纹理自动生成所有需要的多级渐远纹理。
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(GLuint& program)
{
	std::string str2[] = { "ourTexture1" ,"ourTexture2" };
	for (int i = 0; i < nums; i++) {
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		glUniform1i(glGetUniformLocation(program, str2[i].c_str()), i);
	}
}

void Texture::Bind2(GLuint& program){

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(program, "ourTexture1"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(program, "ourTexture2"), 1);
}

Texture::Texture(std::string str[], int num)
{
	m_textures = new GLuint[num];
	for (int i = 0; i < num; i++) {
		glGenTextures(1, &m_textures[i]);
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		int width, height, n;
		unsigned char* image;
		image = stbi_load(str[i].c_str(), &width, &height, &n, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // We want to repeat this pattern so we set kept it at GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   // We want to repeat this pattern so we set kept it at GL_REPEAT
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(std::string names[], int num) {
	for (int i = 0; i < num; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D,m_textures[i]);
	}
}


