#pragma once
#include<iostream>
#include<GL/glew.h>
#include<vector>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include"Shader.h"
#include"MyMesh.h"



class Model
{
public:
	/*  ��Ա����   */
	Model(char* path)
	{
		this->loadModel(path);
	}
	void Draw(Shader shader);
private:
	/*  ģ������  */
	std::vector<myMesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;

	/*  ˽�г�Ա����   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	myMesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};