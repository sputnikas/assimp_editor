#include <cstdio>
#include <map>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////

class GLMesh {
public:
    GLMesh(const aiMesh* mesh);
    void render(const aiMatrix4x4 &mvp);

    GLint mvp_location;
    GLint n_indices;
    GLuint vao;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;
};

GLMesh::GLMesh(const aiMesh* mesh) {
    n_indices = 0;
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Создаём шейдер
    ///////////////////////////////////////////////////////////////////////////////////////////////
    const char* vertex_shader_text =
        "#version 330\n"
        "out vec4 gl_FragColor;"
        "layout (location =  0) in mat4 MVP;\n"
        "layout (location =  1) in vec3 positions;\n"
        "layout (location =  2) in vec3 normals;\n"
        "layout (location =  3) in vec3 tangents;\n"
        "layout (location =  4) in vec3 bitangents;\n"
        "layout (location =  5) in vec3 uvs0;\n"
        "layout (location =  6) in vec3 uvs1;\n"
        "layout (location =  7) in vec3 uvs2;\n"
        "layout (location =  8) in vec3 uvs3;\n"
        "layout (location =  9) in vec3 uvs4;\n"
        "layout (location = 10) in vec3 uvs5;\n"
        "layout (location = 11) in vec3 uvs6;\n"
        "layout (location = 12) in vec3 uvs7;\n"
        "layout (location = 13) in vec3 colors0;\n"
        "layout (location = 14) in vec3 colors1;\n"
        "layout (location = 15) in vec3 colors2;\n"
        "layout (location = 16) in vec3 colors3;\n"
        "layout (location = 17) in vec3 colors4;\n"
        "layout (location = 18) in vec3 colors5;\n"
        "layout (location = 19) in vec3 colors6;\n"
        "layout (location = 20) in vec3 colors7;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(positions, 1.0);\n"
        "}\n";

    const char* fragment_shader_text =
        "#version 330\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(0.2, 0.2, 0.2, 1.0);\n"
        "}\n";
    //GLint length[] = { 1 };
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Забираем из шейдера индексы для glVertexAttribPointer
    ///////////////////////////////////////////////////////////////////////////////////////////////
    mvp_location = 0; // glGetUniformLocation(program, "MVP");
    GLint positions_location  = 1; // glGetAttribLocation(program, "positions");
    GLint normals_location    = 2; // glGetAttribLocation(program, "normals");
    GLint tangents_location   = 3; // glGetAttribLocation(program, "tangents");
    GLint bitangents_location = 4; // glGetAttribLocation(program, "bitangents");
    GLint uvs_location[8];
    uvs_location[0]    = 5; // glGetAttribLocation(program, "uvs0_location");
    uvs_location[1]    = 6; // glGetAttribLocation(program, "uvs1_location");
    uvs_location[2]    = 7; // glGetAttribLocation(program, "uvs2_location");
    uvs_location[3]    = 8; // glGetAttribLocation(program, "uvs3_location");
    uvs_location[4]    = 9; // glGetAttribLocation(program, "uvs4_location");
    uvs_location[5]    = 10; // glGetAttribLocation(program, "uvs5_location");
    uvs_location[6]    = 11; // glGetAttribLocation(program, "uvs6_location");
    uvs_location[7]    = 12; // glGetAttribLocation(program, "uvs7_location");
    GLint colors_location[8];
    colors_location[0] = 13; // glGetAttribLocation(program, "colors0");
    colors_location[1] = 14; // glGetAttribLocation(program, "colors1");
    colors_location[2] = 15; // glGetAttribLocation(program, "colors2");
    colors_location[3] = 16; // glGetAttribLocation(program, "colors3");
    colors_location[4] = 17; // glGetAttribLocation(program, "colors4");
    colors_location[5] = 18; // glGetAttribLocation(program, "colors5");
    colors_location[6] = 19; // glGetAttribLocation(program, "colors6");
    colors_location[7] = 20; // glGetAttribLocation(program, "colors7");
    printf("%d\n", mvp_location);
    printf("%d\n", positions_location);
    printf("%d\n", normals_location);
    printf("%d\n", tangents_location);
    printf("%d\n", bitangents_location);
    printf("%d\n", uvs_location[0]);
    printf("%d\n", uvs_location[1]);
    printf("%d\n", uvs_location[2]);
    printf("%d\n", uvs_location[3]);
    printf("%d\n", uvs_location[4]);
    printf("%d\n", uvs_location[5]);
    printf("%d\n", uvs_location[6]);
    printf("%d\n", uvs_location[7]);
    printf("%d\n", colors_location[0]);
    printf("%d\n", colors_location[1]);
    printf("%d\n", colors_location[2]);
    printf("%d\n", colors_location[3]);
    printf("%d\n", colors_location[4]);
    printf("%d\n", colors_location[5]);
    printf("%d\n", colors_location[6]);
    printf("%d\n", colors_location[7]);
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Создаём VAO объект и привязываем его для последующей связи с буферами
    ///////////////////////////////////////////////////////////////////////////////////////////////
    vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Выделяем буферы в видеопамяти и заполняем их данными
    // Для каждого буфера создаём glVertexAttributePointer (пока они активны)
    // Все glVertexAttributePointer будут привязаны к активному vao
    ///////////////////////////////////////////////////////////////////////////////////////////////
    GLuint buffer_positions = 0;
    GLuint buffer_normals = 0;
    GLuint buffer_tangents = 0;
    GLuint buffer_bitangents = 0;
    GLuint buffer_uvs[8];
    buffer_uvs[0] = 0;
    buffer_uvs[1] = 0;
    buffer_uvs[2] = 0;
    buffer_uvs[3] = 0;
    buffer_uvs[4] = 0;
    buffer_uvs[5] = 0;
    buffer_uvs[6] = 0;
    buffer_uvs[7] = 0;
    GLuint buffer_colors[8];
    buffer_colors[0] = 0;
    buffer_colors[1] = 0;
    buffer_colors[2] = 0;
    buffer_colors[3] = 0;
    buffer_colors[4] = 0;
    buffer_colors[5] = 0;
    buffer_colors[6] = 0;
    buffer_colors[7] = 0;
    GLuint buffer_faces = 0;
    if (mesh->HasPositions()) {
        glGenBuffers(1, &buffer_positions);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_positions);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(positions_location, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }
    if (mesh->HasNormals()) {
        glGenBuffers(1, &buffer_normals);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_normals);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
        glVertexAttribPointer(normals_location, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }
    if (mesh->HasTangentsAndBitangents()) {
        glGenBuffers(1, &buffer_tangents);
        glGenBuffers(1, &buffer_bitangents);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_tangents);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, mesh->mTangents, GL_STATIC_DRAW);
        glVertexAttribPointer(tangents_location, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_bitangents);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, mesh->mBitangents, GL_STATIC_DRAW);
        glVertexAttribPointer(bitangents_location, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }
    if (mesh->GetNumUVChannels() > 0) {
        for (unsigned int i = 0; i < mesh->GetNumUVChannels(); ++i) {
            buffer_uvs[i] = 0;
            glGenBuffers(1, &buffer_uvs[i]);
            glBindBuffer(GL_ARRAY_BUFFER, buffer_uvs[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, mesh->mTextureCoords[i], GL_STATIC_DRAW);
            glVertexAttribPointer(uvs_location[i], 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }
    }
    if (mesh->GetNumColorChannels() > 0) {
        for (unsigned int i = 0; i < mesh->GetNumColorChannels(); ++i) {
            buffer_colors[i] = 0;
            glGenBuffers(1, &buffer_colors[i]);
            glBindBuffer(GL_ARRAY_BUFFER, buffer_colors[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(aiColor4D) * mesh->mNumVertices, mesh->mColors[i], GL_STATIC_DRAW);
            glVertexAttribPointer(colors_location[i], 4, GL_FLOAT, GL_FALSE, 0, NULL);
        }
    }
    if (mesh->HasFaces()) {
        glGenBuffers(1, &buffer_faces);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_faces);
        n_indices = mesh->mNumFaces * 3;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->mNumFaces * 3, mesh->mFaces, GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
    printf("%d\n", buffer_positions);
    printf("%d\n", buffer_normals);
    printf("%d\n", buffer_tangents);
    printf("%d\n", buffer_bitangents);
    printf("%d\n", buffer_uvs[0]);
    printf("%d\n", buffer_uvs[1]);
    printf("%d\n", buffer_uvs[2]);
    printf("%d\n", buffer_uvs[3]);
    printf("%d\n", buffer_uvs[4]);
    printf("%d\n", buffer_uvs[5]);
    printf("%d\n", buffer_uvs[6]);
    printf("%d\n", buffer_uvs[7]);
    printf("%d\n", buffer_colors[0]);
    printf("%d\n", buffer_colors[1]);
    printf("%d\n", buffer_colors[2]);
    printf("%d\n", buffer_colors[3]);
    printf("%d\n", buffer_colors[4]);
    printf("%d\n", buffer_colors[5]);
    printf("%d\n", buffer_colors[6]);
    printf("%d\n", buffer_colors[7]);
    printf("%d\n", buffer_faces);
}

void GLMesh::render(const aiMatrix4x4& mvp)
{
    glUseProgram(program);
    glBindVertexArray(vao);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp[0][0]);
    glDrawElements(GL_TRIANGLES, n_indices, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    glUseProgram(0);
}

class GLScene {
public:
    std::vector<GLMesh*> meshes;
    aiVector3D rmin, rmax;

    GLScene(const std::string& filename);
    ~GLScene();
    void render(const aiMatrix4x4& mvp);
};

GLScene::GLScene(const std::string& filename) {
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Импорт ресурсов в сцену assimp
    ///////////////////////////////////////////////////////////////////////////////////////////////
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
        printf(
            "Export type %2lld extension = %7s id = %s\n", i,
            aiGetExportFormatDescription(i)->fileExtension,
            aiGetExportFormatDescription(i)->id
        );
    }
    printf("-------------------------------------------------------------------------\n");
    const aiScene* scene = importer.ReadFile(
        filename,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_FixInfacingNormals |
        aiProcess_PopulateArmatureData
    );
    if (scene == nullptr) {
        printf("Model %s cannot be loaded and explored!\n", filename.c_str());
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
        meshes.push_back(new GLMesh(scene->mMeshes[i]));
        if (scene->mMeshes[i]->HasPositions()) {
            if (i == 0) {
                rmin = scene->mMeshes[i]->mVertices[0];
                rmax = rmin;
            }
            for (unsigned int j = 1; j < scene->mMeshes[i]->mNumVertices; ++j) {
                if (rmin.x > scene->mMeshes[i]->mVertices[j].x) {
                    rmin.x = scene->mMeshes[i]->mVertices[j].x;
                }
                if (rmin.y > scene->mMeshes[i]->mVertices[j].y) {
                    rmin.y = scene->mMeshes[i]->mVertices[j].y;
                }
                if (rmin.z > scene->mMeshes[i]->mVertices[j].z) {
                    rmin.z = scene->mMeshes[i]->mVertices[j].z;
                }
                if (rmax.x < scene->mMeshes[i]->mVertices[j].x) {
                    rmax.x = scene->mMeshes[i]->mVertices[j].x;
                }
                if (rmax.y < scene->mMeshes[i]->mVertices[j].y) {
                    rmax.y = scene->mMeshes[i]->mVertices[j].y;
                }
                if (rmax.z < scene->mMeshes[i]->mVertices[j].z) {
                    rmax.z = scene->mMeshes[i]->mVertices[j].z;
                }
            }
        }
    }
    printf("Scene Box: (%f, %f, %f) - (%f, %f, %f)\n", rmin.x, rmin.y, rmin.z, rmax.x, rmax.y, rmax.z);
}

GLScene::~GLScene() {
    for (auto i = meshes.begin(); i != meshes.end(); i++) {
        delete *i;
    }
    meshes.clear();
}

void GLScene::render(const aiMatrix4x4& mvp) {
    for (auto i = meshes.begin(); i != meshes.end(); i++) {
        (*i)->render(mvp);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

aiVector3D position = aiVector3D();

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        position.x += 0.1f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        position.x -= 0.1f;
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        position.y += 0.1f;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        position.y -= 0.1f;
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        position.z += 0.1f;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        position.z -= 0.1f;
    }
    printf("Position (%f, %f, %f)\n", position.x, position.y, position.z);
}

aiMatrix4x4 perspective(float fovy, float aspect, float zmin, float zmax) {
    return aiMatrix4x4(
        1 / aspect/tanf(fovy/2), 0, 0, 0,
        0, 1 / tanf(fovy / 2), 0, 0,
        0, 0, - (zmax + zmin)/(zmax - zmin), -1,
        0, 0, -2*zmax*zmin/(zmax - zmin), 0
    );
}

aiMatrix4x4 ortho(float x0, float x1, float y0, float y1) {
    return aiMatrix4x4(
        2 / (x1 - x0), 0, 0, -(x0 + x1) / (x1 - x0),
        0, 2 / (y1 - y0), 0, -(y0 + y1) / (y1 - y0),
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

aiMatrix4x4 ortho(float x0, float x1, float y0, float y1, float z0, float z1) {
    return aiMatrix4x4(
        2 / (x1 - x0), 0, 0, -(x0 + x1) / (x1 - x0),
        0, 2 / (y1 - y0), 0, -(y0 + y1) / (y1 - y0),
        0, 0, 1 / (z1 - z0), -z0 / (z1 - z0),
        0, 0, 0, 1
    );
}

int main(int argc, char* argv[])
{
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Инициализация окна в glfw3 и opengl
    // Важно: загрузка графики использует создание буферов opengl и шейдеров
    // Нельзя создавать шейдеры до инициализации opengl!
    ///////////////////////////////////////////////////////////////////////////////////////////////
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Импорт ресурсов в сцену GLScene и инициализация буферов для графики
    ///////////////////////////////////////////////////////////////////////////////////////////////
    std::string filename = (argc > 1) ? argv[1] : "../data/test.gltf";
    GLScene scene = GLScene(filename);
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Основной цикл
    ///////////////////////////////////////////////////////////////////////////////////////////////
    float ratio;
    int width, height;
    aiMatrix4x4 m, p, mvp;

    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height * 10;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        m = aiMatrix4x4(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        float time = (float) glfwGetTime();
        //m.RotationZ(4.0f * time, m);
        m.Translation(position, m);
        p = ortho(-ratio, ratio, -10.f, 10.f, 10.f, -10.f);
        mvp = p * m;

        scene.render(mvp);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}