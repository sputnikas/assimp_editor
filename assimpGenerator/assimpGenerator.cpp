#include <cstdio>
#include <map>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

aiScene* gen_triangle() {
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Создание меша
	///////////////////////////////////////////////////////////////////////////////////////////////
	aiMesh* mesh;
	mesh = new aiMesh;
	mesh->mName = "Triangle";
	mesh->mNumVertices = 3;
	mesh->mVertices = new aiVector3D[mesh->mNumVertices];
	mesh->mVertices[0] = aiVector3D(1, 0, 0);
	mesh->mVertices[1] = aiVector3D(0, 1, 0);
	mesh->mVertices[2] = aiVector3D(1, 1, 0);
	mesh->mNormals = new aiVector3D[mesh->mNumVertices];
	mesh->mNormals[0] = aiVector3D(0, 0, 1);
	mesh->mNormals[1] = aiVector3D(0, 0, 1);
	mesh->mNormals[2] = aiVector3D(0, 0, 1);
	mesh->mTangents = new aiVector3D[mesh->mNumVertices];
	mesh->mTangents[0] = aiVector3D(1, 0, 0);
	mesh->mTangents[1] = aiVector3D(0, 1, 0);
	mesh->mTangents[2] = aiVector3D(1, 1, 0);
	mesh->mBitangents = new aiVector3D[mesh->mNumVertices];
	mesh->mBitangents[0] = aiVector3D(1, 0, 0);
	mesh->mBitangents[1] = aiVector3D(0, 1, 0);
	mesh->mBitangents[2] = aiVector3D(1, 1, 0);
	mesh->mPrimitiveTypes = 4;
	mesh->mNumFaces = 1;
	mesh->mFaces = new aiFace[mesh->mNumFaces];
	mesh->mFaces->mNumIndices = 3;
	mesh->mFaces->mIndices = new unsigned int[mesh->mFaces->mNumIndices];
	mesh->mFaces->mIndices[0] = 0;
	mesh->mFaces->mIndices[1] = 1;
	mesh->mFaces->mIndices[2] = 2;
	mesh->mMaterialIndex = 0;
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Создание сцены
	// Минимальная сцена состоит из названия, одного меша, одного материала, одной ноды (скелета)!
	///////////////////////////////////////////////////////////////////////////////////////////////
	aiScene* scene;
	scene = new aiScene;
	scene->mName = "Triangle";
	///////////////////////////////////////////////////////////////////////////////////////////////
	scene->mNumMeshes = 1;
	scene->mMeshes = new aiMesh*[1];
	*(scene->mMeshes) = mesh;
	///////////////////////////////////////////////////////////////////////////////////////////////
	scene->mNumMaterials = 1;
	scene->mMaterials = new aiMaterial * [1];
	scene->mMaterials[0] = new aiMaterial;
	///////////////////////////////////////////////////////////////////////////////////////////////
	scene->mRootNode = new aiNode("Triangle");
	scene->mRootNode->mMeshes = new unsigned int[scene->mNumMeshes];
	scene->mRootNode->mNumMeshes = 1;
	scene->mRootNode->mMeshes[0] = 0;
	return scene;
}

int main(int argc, char* argv[]) {
	printf("Assimp export information:\n");
	printf("-------------------------------------------------------------------------\n");
	size_t numExportTypes = aiGetExportFormatCount();
	for (size_t i = 0; i < numExportTypes; ++i) {
		printf(
			"Export type %2lld extension = %7s id = %s\n", i,
			aiGetExportFormatDescription(i)->fileExtension,
			aiGetExportFormatDescription(i)->id
		);
	}
	printf("-------------------------------------------------------------------------\n");
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Имя выходного файла
	///////////////////////////////////////////////////////////////////////////////////////////////
	std::string filename = (argc > 1) ? argv[1] : "./test.gltf";
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Генерация сцены
	///////////////////////////////////////////////////////////////////////////////////////////////
	aiScene* scene;
	scene = gen_triangle();
	Assimp::Exporter exporter;
	exporter.Export(scene, "gltf2", filename.c_str());
	printf("All generated!\n");
	return 0;
}