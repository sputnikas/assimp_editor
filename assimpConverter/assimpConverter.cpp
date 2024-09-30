#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Exporter.hpp>
#include <assimp/Importer.hpp>
#include <cstdio>
#include <map>
#include <vector>

void printNodeTreeA(aiNode* node, const std::string& tab = "") {
    printf("%s%s%s\n", tab.c_str(), node->mName.C_Str(), (node->mNumChildren > 0) ? ":" : ";");
    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        printNodeTreeA(node->mChildren[i], tab + "    ");
    }
}

void printAnimMeshes(aiAnimMesh** animMeshes, unsigned int numAnimMeshes) {
    for (unsigned int i = 0; i < numAnimMeshes; ++i) {
        printf(
            "----------------------------------------------------------------------"
            "---\n");
        printf("AnimMeshes %d information:\n", i);
        printf("Num of Vertices = %d\n", animMeshes[i][0].mNumVertices);
        printf("Name = %s\n", animMeshes[i][0].mName.C_Str());
        printf("Weight = %f\n", animMeshes[i][0].mWeight);
        // Данные на замену данных из aiMesh верхнего уровня
        // animMeshes[i][0].mVertices : aiVector3D*;
        // animMeshes[i][0].mNormals : aiVector3D*;
        // animMeshes[i][0].mTangents : aiVector3D*;
        // animMeshes[i][0].mBitangents : aiVector3D*;
        // animMeshes[i][0].mColors : aiColor4D*;
        // animMeshes[i][0].mTextureCoords : aiVector3D[8] *;
    }
}

void printBones(aiBone** bones, unsigned int numBones) {
    for (unsigned int i = 0; i < numBones; ++i) {
        printf(
            "----------------------------------------------------------------------"
            "---\n");
        printf("Bones %d information:\n", i);
        printf("Num of Weights = %d\n", bones[i][0].mNumWeights);
        printf("Name = %s\n", bones[i][0].mName.C_Str());
    }
    std::map<long long int, aiNode*> armatures;
    for (unsigned int i = 0; i < numBones; ++i) {
        if (bones[i][0].mArmature != nullptr) {
            long long int adress = (long long int)bones[i][0].mArmature;
            if (armatures.find(adress) == armatures.end()) {
                armatures.insert({adress, bones[i][0].mArmature});
            }
        }
    }
    int ind = 0;
    for (const auto& i : armatures) {
        printf(
            "----------------------------------------------------------------------"
            "---\n");
        printf("Armature %d information in adress %llx:\n", ind, i.first);
        printNodeTreeA(i.second, "    ");
    }
}

void printSkeletonBones(aiSkeletonBone** bones, unsigned int numBones) {
    for (unsigned int i = 0; i < numBones; ++i) {
        printf(
            "----------------------------------------------------------------------"
            "---\n");
        printf("Bones %d information:\n", i);
        printf("Num of Weights = %d\n", bones[i][0].mNumnWeights);
    }
    std::map<long long int, aiNode*> armatures;
    for (unsigned int i = 0; i < numBones; ++i) {
        if (bones[i][0].mArmature != nullptr) {
            long long int adress = (long long int)bones[i][0].mArmature;
            if (armatures.find(adress) == armatures.end()) {
                armatures.insert({adress, bones[i][0].mArmature});
            }
        }
    }
    int ind = 0;
    for (const auto& i : armatures) {
        printf(
            "----------------------------------------------------------------------"
            "---\n");
        printf("Armature %d information in adress %llx:\n", ind, i.first);
        printNodeTreeA(i.second, "    ");
    }
}

void printFloatArray(const char* name, char* array, unsigned int size) {
    float* f = (float*)&array[0];
    printf("%s = { ", name);
    for (unsigned int i = 0; i < size / sizeof(float) - 1; ++i) {
        printf("%f, ", *f);
        f++;
    }
    printf("%f }\n", *f);
}

void printDoubleArray(const char* name, char* array, unsigned int size) {
    double* f = (double*)&array[0];
    printf("%s = { ", name);
    for (unsigned int i = 0; i < size / sizeof(double) - 1; ++i) {
        printf("%f, ", *f);
        f++;
    }
    printf("%f }\n", *f);
}

void printIntArray(const char* name, char* array, unsigned int size) {
    int* f = (int*)&array[0];
    printf("%s = { ", name);
    for (unsigned int i = 0; i < size / sizeof(int) - 1; ++i) {
        printf("%d, ", *f);
        f++;
    }
    printf("%d }\n", *f);
}

int main(int argc, char* argv[]) {
    Assimp::Importer importer;
    printf("Assimp import information:\n");
    printf("-------------------------------------------------------------------------\n");
    std::string import_types;
    importer.GetExtensionList(import_types);
    printf("Import types = %s\n", import_types.c_str());
    printf("-------------------------------------------------------------------------\n");
    printf("Assimp export information:\n");
    printf("-------------------------------------------------------------------------\n");
    size_t numExportTypes = aiGetExportFormatCount();
    for (size_t i = 0; i < numExportTypes; ++i) {
        printf("Export type %2lld extension = %7s id = %s\n", i, aiGetExportFormatDescription(i)->fileExtension, aiGetExportFormatDescription(i)->id);
    }
    printf("-------------------------------------------------------------------------\n");
    std::string filename = (argc > 1) ? argv[1] : "./data/archer.gltf";
    std::string export_type = (argc > 2) ? argv[2] : "gltf2";
    std::string filename2 = (argc > 3) ? argv[3] : "./data/export.gltf";
    try {
        const aiScene* scene = importer.ReadFile(
            filename, 
            aiProcess_CalcTangentSpace | 
            aiProcess_Triangulate | 
            aiProcess_GenSmoothNormals | 
            aiProcess_FixInfacingNormals | 
            aiProcess_PopulateArmatureData);
        if (scene == nullptr) {
            printf("Model %s cannot be loaded and explored!\n", filename.c_str());
            return 1;
        }
        printf("Model %s information:\n", filename.c_str());
        printf("-------------------------------------------------------------------------\n");
        printf("Num of Meshes     = %d\n", scene->mNumMeshes);
        printf("Num of Animations = %d\n", scene->mNumAnimations);
        printf("Num of Cameras    = %d\n", scene->mNumCameras);
        printf("Num of Lights     = %d\n", scene->mNumLights);
        printf("Num of Materials  = %d\n", scene->mNumMaterials);
        printf("Num of Textures   = %d\n", scene->mNumTextures);
        printf("Num of Skeletons  = %d\n", scene->mNumSkeletons);
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            printf("-------------------------------------------------------------------------\n");
            printf("Mesh %d Info:\n", i);
            printf("    Name  = %s\n", scene->mMeshes[i]->mName.C_Str());
            printf("    Num of AnimMeshes      = %d\n", scene->mMeshes[i]->mNumAnimMeshes);
            printf("    Num of Bones           = %d\n", scene->mMeshes[i]->mNumBones);
            printf("    Num of Faces           = %d\n", scene->mMeshes[i]->mNumFaces);
            printf("    Num of UVComponents[0] = %d\n", scene->mMeshes[i]->mNumUVComponents[0]);
            printf("    Num of UVComponents[1] = %d\n", scene->mMeshes[i]->mNumUVComponents[1]);
            printf("    Num of UVComponents[2] = %d\n", scene->mMeshes[i]->mNumUVComponents[2]);
            printf("    Num of UVComponents[3] = %d\n", scene->mMeshes[i]->mNumUVComponents[3]);
            printf("    Num of UVComponents[4] = %d\n", scene->mMeshes[i]->mNumUVComponents[4]);
            printf("    Num of UVComponents[5] = %d\n", scene->mMeshes[i]->mNumUVComponents[5]);
            printf("    Num of UVComponents[6] = %d\n", scene->mMeshes[i]->mNumUVComponents[6]);
            printf("    Num of UVComponents[7] = %d\n", scene->mMeshes[i]->mNumUVComponents[7]);
            printf("    Num of Vertices        = %d\n", scene->mMeshes[i]->mNumVertices);
            printf("    Num of Color Channels  = %d\n", scene->mMeshes[i]->GetNumColorChannels());
            printf("    Num of UV Channels     = %d\n", scene->mMeshes[i]->GetNumUVChannels());
            printf("    PrimitiveTypes  = %d\n", scene->mMeshes[i]->mPrimitiveTypes);
            printf("    Bounding box = (%f, %f, %f) -> (%f, %f, %f)\n", scene->mMeshes[i]->mAABB.mMin.x, scene->mMeshes[i]->mAABB.mMin.y, scene->mMeshes[i]->mAABB.mMin.z, scene->mMeshes[i]->mAABB.mMax.x, scene->mMeshes[i]->mAABB.mMax.y,
                   scene->mMeshes[i]->mAABB.mMax.z);
            printf("    Index of method of morphing = %d\n", scene->mMeshes[i]->mMethod);
            printf("    Has tangents and bitangents = %d\n", scene->mMeshes[i]->HasTangentsAndBitangents());
            printf("    Index of material = %d\n", scene->mMeshes[i]->mMaterialIndex);
            printAnimMeshes(scene->mMeshes[i]->mAnimMeshes, scene->mMeshes[i]->mNumAnimMeshes);
            printBones(scene->mMeshes[i]->mBones, scene->mMeshes[i]->mNumBones);
            // Данные вертексов aiMesh
            // scene->mMeshes[i]->mVertices : aiVector3D*;
            // scene->mMeshes[i]->mNormals : aiVector3D*;
            // scene->mMeshes[i]->mTangents : aiVector3D*;
            // scene->mMeshes[i]->mBitangents : aiVector3D*;
            // scene->mMeshes[i]->mColors : aiColor4D[8]*;
            // scene->mMeshes[i]->mTextureCoords : aiVector3D[8] *;
            // scene->mMeshes[i]->mTextureCoordsNames : aiString[8];
            // scene->mMeshes[i]->mFaces : aiFace;
        }
        for (unsigned int i = 0; i < scene->mNumAnimations; ++i) {
            printf("-------------------------------------------------------------------------\n");
            printf("Animation %d Info:\n", i);
            printf("    Name  = %s\n", scene->mAnimations[i]->mName.C_Str());
            printf("    Num of NumChannels          = %d\n", scene->mAnimations[i]->mNumChannels);
            printf("    Num of NumMeshChannels      = %d\n", scene->mAnimations[i]->mNumMeshChannels);
            printf("    Num of NumMorphMeshChannels = %d\n", scene->mAnimations[i]->mNumMorphMeshChannels);
            printf("    Duration                    = %f\n", scene->mAnimations[i]->mDuration);
            printf("    TicksPerSecond              = %f\n", scene->mAnimations[i]->mTicksPerSecond);
            for (unsigned int j = 0; j < scene->mAnimations[i]->mNumChannels; ++j) {
                printf("-------------------------------------------------------------------------\n");
                printf("    %d Animation %d Channel Info\n", i, j);
                printf("    Name of affect node: mNodeName = %s\n", scene->mAnimations[i]->mChannels[j]->mNodeName.C_Str());
                printf("    NumPositionKeys = %d\n", scene->mAnimations[i]->mChannels[j]->mNumPositionKeys);
                printf("    NumRotationKeys = %d\n", scene->mAnimations[i]->mChannels[j]->mNumRotationKeys);
                printf("    NumScalingKeys  = %d\n", scene->mAnimations[i]->mChannels[j]->mNumScalingKeys);
            }
            for (unsigned int j = 0; j < scene->mAnimations[i]->mNumMeshChannels; ++j) {
                printf("-------------------------------------------------------------------------\n");
                printf("    %d Animation %d Mesh Channel Info\n", i, j);
                printf("    Name of mesh = %s\n", scene->mAnimations[i]->mMeshChannels[j]->mName.C_Str());
                printf("    Num of keys = %d\n", scene->mAnimations[i]->mMeshChannels[j]->mNumKeys);
                for (unsigned int k = 0; k < scene->mAnimations[i]->mMeshChannels[j]->mNumKeys; ++k) {
                    printf("-------------------------------------------------------------------------\n");
                    printf("        Key %d Time of this keyframe: mTime = %e\n", k, scene->mAnimations[i]->mMeshChannels[j]->mKeys[k].mTime);
                    printf("        Key %d Index of mesh in mAnimMeshes: mValue = %d\n", k, scene->mAnimations[i]->mMeshChannels[j]->mKeys[k].mValue);
                }
            }
            for (unsigned int j = 0; j < scene->mAnimations[i]->mNumMorphMeshChannels; ++j) {
                printf("-------------------------------------------------------------------------\n");
                printf("    %d Animation %d Morph Mesh Channel Info\n", i, j);
                printf("    Name of mesh = %s\n", scene->mAnimations[i]->mMorphMeshChannels[j]->mName.C_Str());
                printf("    Num of keys = %d\n", scene->mAnimations[i]->mMorphMeshChannels[j]->mNumKeys);
                for (unsigned int k = 0; k < scene->mAnimations[i]->mMorphMeshChannels[j]->mNumKeys; ++k) {
                    printf("-------------------------------------------------------------------------\n");
                    printf("        Key %d Time of this keyframe: mTime = %e\n", k, scene->mAnimations[i]->mMorphMeshChannels[j]->mKeys[k].mTime);
                    printf("        Key %d Num of values and weights: mValue = %d\n", k, scene->mAnimations[i]->mMorphMeshChannels[j]->mKeys[k].mNumValuesAndWeights);
                    for (unsigned int l = 0; l < scene->mAnimations[i]->mMorphMeshChannels[j]->mKeys[k].mNumValuesAndWeights; ++l) {
                        printf("       Index of mesh in mAnimMeshes: mValue[%d] = %d\n", l, scene->mAnimations[i]->mMorphMeshChannels[j]->mKeys[k].mValues[l]);
                        printf("       Weight of key: mWeight[%d] = %e\n", l, scene->mAnimations[i]->mMorphMeshChannels[j]->mKeys[k].mWeights[l]);
                    }
                }
            }
        }
        for (unsigned int i = 0; i < scene->mNumCameras; ++i) {
            printf("-------------------------------------------------------------------------\n");
            printf("Camera %d Info:\n", i);
            printf("    Name  = %s\n", scene->mCameras[i]->mName.C_Str());
            printf("    Aspect Ratio     = %f [typycal 4/3, 1/2, 1/1]\n", scene->mCameras[i]->mAspect);
            printf("    ClipPlaneFar     = %f [default 1000.0f]\n", scene->mCameras[i]->mClipPlaneFar);
            printf("    ClipPlaneNear    = %f [default 0.1f]\n", scene->mCameras[i]->mClipPlaneNear);
            printf("    HorizontalFOV    = %f [default M_PI/4]\n", scene->mCameras[i]->mHorizontalFOV);
            printf("    LookAt           = (%f, %f, %f) [default = (0, 0, 1)]\n", scene->mCameras[i]->mLookAt.x, scene->mCameras[i]->mLookAt.y, scene->mCameras[i]->mLookAt.z);
            printf("    OrthographicWidth= %f [default = 0]\n", scene->mCameras[i]->mOrthographicWidth);
            printf("    Position         = (%f, %f, %f) [default = (0, 0, 0)]\n", scene->mCameras[i]->mPosition.x, scene->mCameras[i]->mPosition.y, scene->mCameras[i]->mPosition.z);
            printf("    Up               = (%f, %f, %f) [default = (0, 0, 0)]\n", scene->mCameras[i]->mUp.x, scene->mCameras[i]->mUp.y, scene->mCameras[i]->mUp.z);
        }
        for (unsigned int i = 0; i < scene->mNumLights; ++i) {
            printf("-------------------------------------------------------------------------\n");
            printf("Light %d Info:\n", i);
            printf("    Name  = %s\n", scene->mLights[i]->mName.C_Str());
            switch (scene->mLights[i]->mType) {
                case aiLightSource_UNDEFINED:
                    printf("    Type     = %d = UNDEFINED\n", scene->mLights[i]->mType);
                    break;
                case aiLightSource_DIRECTIONAL:  // Направенный свет
                    printf("    Type      = %d = DIRECTIONAL\n", scene->mLights[i]->mType);
                    printf("    UpDirection = (%f, %f, %f)\n", scene->mLights[i]->mUp.x, scene->mLights[i]->mUp.y, scene->mLights[i]->mUp.z);
                    printf("    Direction   = (%f, %f, %f)\n", scene->mLights[i]->mDirection.x, scene->mLights[i]->mDirection.y, scene->mLights[i]->mDirection.z);
                    break;
                case aiLightSource_POINT:  // Точечный источник света с интенсивностью
                                           // 1/(att0 + att1*d + att2*d^2)
                    printf("    Type     = %d = POINT\n", scene->mLights[i]->mType);
                    printf("    Position = (%f, %f, %f)\n", scene->mLights[i]->mPosition.x, scene->mLights[i]->mPosition.y, scene->mLights[i]->mPosition.z);
                    printf("    AttenuationConstant  = %f\n", scene->mLights[i]->mAttenuationConstant);
                    printf("    AttenuationLinear    = %f\n", scene->mLights[i]->mAttenuationLinear);
                    printf("    AttenuationQuadratic = %f\n", scene->mLights[i]->mAttenuationQuadratic);
                    break;
                case aiLightSource_SPOT:  // Коническая лампочка, максимум в InnerCone,
                                          // за пределами OuterCone интенсивность 0,
                                          // внутри - гладкая интерполяция
                    printf("    Type     = %d = SPOT\n", scene->mLights[i]->mType);
                    printf("    Position = (%f, %f, %f)\n", scene->mLights[i]->mPosition.x, scene->mLights[i]->mPosition.y, scene->mLights[i]->mPosition.z);
                    printf("    UpDirection = (%f, %f, %f)\n", scene->mLights[i]->mUp.x, scene->mLights[i]->mUp.y, scene->mLights[i]->mUp.z);
                    printf("    Direction   = (%f, %f, %f)\n", scene->mLights[i]->mDirection.x, scene->mLights[i]->mDirection.y, scene->mLights[i]->mDirection.z);
                    printf("    AngleInnerCone = %f\n", scene->mLights[i]->mAngleInnerCone);
                    printf("    AngleOuterCone = %f\n", scene->mLights[i]->mAngleOuterCone);
                    break;
                case aiLightSource_AMBIENT:  // Только цвет (светится всё пространство!)
                    printf("    Type     = %d = AMBIENT\n", scene->mLights[i]->mType);
                    break;
                case aiLightSource_AREA:  // Светящийся прямоугольник
                    printf("    Type     = %d = AREA\n", scene->mLights[i]->mType);
                    printf("    Position = (%f, %f, %f)\n", scene->mLights[i]->mPosition.x, scene->mLights[i]->mPosition.y, scene->mLights[i]->mPosition.z);
                    printf("    Direction = (%f, %f, %f)\n", scene->mLights[i]->mDirection.x, scene->mLights[i]->mDirection.y, scene->mLights[i]->mDirection.z);
                    printf("    UpDirection = (%f, %f, %f)\n", scene->mLights[i]->mUp.x, scene->mLights[i]->mUp.y, scene->mLights[i]->mUp.z);
                    printf("    Size = (%f, %f)\n", scene->mLights[i]->mSize.x, scene->mLights[i]->mSize.y);
                    break;
            }
            printf("    ColorAmbient  = (%f, %f, %f)\n", scene->mLights[i]->mColorAmbient.r, scene->mLights[i]->mColorAmbient.g, scene->mLights[i]->mColorAmbient.b);
            printf("    ColorDiffuse  = (%f, %f, %f)\n", scene->mLights[i]->mColorDiffuse.r, scene->mLights[i]->mColorDiffuse.g, scene->mLights[i]->mColorDiffuse.b);
            printf("    ColorSpecular = (%f, %f, %f)\n", scene->mLights[i]->mColorSpecular.r, scene->mLights[i]->mColorSpecular.g, scene->mLights[i]->mColorSpecular.b);
        }
        std::vector<std::string> typesOfProperties = {"undefined", "aiPTI_Float", "aiPTI_Double", "aiPTI_String", "aiPTI_Integer", "aiPTI_Buffer"};
        for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
            printf("-------------------------------------------------------------------------\n");
            printf("Material %d Info:\n", i);
            printf("    Name  = %s\n", scene->mMaterials[i]->GetName().C_Str());
            printf("    Num of properties  = %d\n", scene->mMaterials[i]->mNumProperties);
            printf("    Num allocated  = %d\n", scene->mMaterials[i]->mNumAllocated);
            for (unsigned int j = 0; j < scene->mMaterials[i]->mNumProperties; ++j) {
                printf("-------------------------------------------------------------------------\n");
                printf("    Property %d Info:\n", j);
                if (scene->mMaterials[i]->mProperties[j][0].mType < 6) {
                    printf("        Type of property         = %s\n", typesOfProperties[scene->mMaterials[i]->mProperties[j][0].mType].c_str());
                } else {
                    printf("        Unknown type of property = %d\n", scene->mMaterials[i]->mProperties[j][0].mType);
                }
                printf("        Name of property         = %s\n", scene->mMaterials[i]->mProperties[j][0].mKey.C_Str());
                printf("        Data length buffer       = %d\n", scene->mMaterials[i]->mProperties[j][0].mDataLength);
                printf("        Index of texture         = %d\n", scene->mMaterials[i]->mProperties[j][0].mIndex);
                printf("        Semantic of use texture  = %d\n", scene->mMaterials[i]->mProperties[j][0].mSemantic);
                switch (scene->mMaterials[i]->mProperties[j][0].mType) {
                    case (aiPTI_Float):
                        printFloatArray("        Data", scene->mMaterials[i]->mProperties[j][0].mData, scene->mMaterials[i]->mProperties[j][0].mDataLength);
                        break;
                    case (aiPTI_Double):
                        printDoubleArray("        Data", scene->mMaterials[i]->mProperties[j][0].mData, scene->mMaterials[i]->mProperties[j][0].mDataLength);
                        break;
                    case (aiPTI_Integer):
                        printIntArray("        Data", scene->mMaterials[i]->mProperties[j][0].mData, scene->mMaterials[i]->mProperties[j][0].mDataLength);
                        break;
                    case (aiPTI_String):
                        printf(
                            "        Strange Data (Device Control Symbols in ASCII) = %d "
                            "%d\n",
                            scene->mMaterials[i]->mProperties[j][0].mData[0], scene->mMaterials[i]->mProperties[j][0].mData[1]);
                        printf("        Data = \"");
                        for (unsigned int k = 2; k < scene->mMaterials[i]->mProperties[j][0].mDataLength; ++k) {
                            printf("%c", scene->mMaterials[i]->mProperties[j][0].mData[k]);
                        }
                        printf("\"\n");
                        break;
                    case (aiPTI_Buffer):
                        printf("        Data = 0x");
                        for (unsigned int k = 0; k < scene->mMaterials[i]->mProperties[j][0].mDataLength; ++k) {
                            printf("%02x", scene->mMaterials[i]->mProperties[j][0].mData[k]);
                        }
                        printf("\n");
                        break;
                    default:
                        break;
                }
            }
        }
        for (unsigned int i = 0; i < scene->mNumTextures; ++i) {
            printf("-------------------------------------------------------------------------\n");
            printf("Texture %d Info:\n", i);
            printf("    Filename      = %s\n", scene->mTextures[i]->mFilename.C_Str());
            printf("    Color Format  = %8s\n", scene->mTextures[i]->achFormatHint);
            printf("    Width         = %d\n", scene->mTextures[i]->mWidth);
            printf("    Height        = %d\n", scene->mTextures[i]->mHeight);
            // Данные пикселей в текстуре ARGB8888:
            // scene->mTextures[i]->pcData
        }
        for (unsigned int i = 0; i < scene->mNumSkeletons; ++i) {
            printf("-------------------------------------------------------------------------\n");
            printf("Skeleton %d Info:\n", i);
            printf("    Name  = %s\n", scene->mSkeletons[i]->mName.C_Str());
            printSkeletonBones(scene->mSkeletons[i]->mBones, scene->mMeshes[i]->mNumBones);
        }

        size_t slash = filename.find_last_of("/\\");
        std::string path = filename.substr(0, slash);
        std::string fname = filename.substr(slash + 1);
        size_t point = fname.find_last_of(".");
        std::string fname_wo_ext = fname.substr(0, point);
        std::string fname_ext = fname.substr(point + 1);
        Assimp::Exporter exporter;
        printf("Export file to %s!\n", filename2.c_str());
        exporter.Export(scene, export_type, filename2.c_str());
    } catch (std::exception& e) {
        printf("%s", e.what());
    }
    return 0;
}