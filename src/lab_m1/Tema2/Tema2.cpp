#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    camera = new implemented::Camera_tema();
    camera->Set(glm::vec3(5, 12, 7), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera->RotateThirdPerson_OY(-0.615);
    camera->RotateThirdPerson_OX(-0.517);

    map_nr = rand() % 8 + 1;
    if (map_nr == 1) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map1[i][j];
            }
        }
    }
    if (map_nr == 2) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map2[i][j];
            }
        }
    }
    if (map_nr == 3) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map3[i][j];
            }
        }
    }
    if (map_nr == 4) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map4[i][j];
            }
        }
    }
    if (map_nr == 5) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map5[i][j];
            }
        }
    }
    if (map_nr == 6) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map6[i][j];
            }
        }
    }
    if (map_nr == 7) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map7[i][j];
            }
        }
    }
    if (map_nr == 8) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map8[i][j];
            }
        }
    }

    while (poz == false) {
        x = rand() % 10;
        z = rand() % 10;
        if (map[x][z] == 0) {
            poz = true;
        }
    }

    x_trup = x + 0.5;
    y_trup = 0.5;
    z_trup = z + 0.5;

    x_capatana = x + 0.5;
    y_capatana = 0.75;
    z_capatana = z + 0.5;

    x_ms = x + 0.8;
    y_ms = 0.5;
    z_ms = z + 0.5;

    x_md = x + 0.2;
    y_md = 0.5;
    z_md = z + 0.5;

    x_ps = x + 0.6;
    y_ps = 0.2;
    z_ps = z + 0.5;

    x_pd = x + 0.4;
    y_pd = 0.2;
    z_pd = z + 0.5;
    
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("teapot");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("archer");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/archer"), "archer.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        lightPosition = glm::vec3(5, 3, 5);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 100.0f);
}


void Tema2::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    if (x_trup > 9.9 || z_trup > 9.9 || x_trup < 0 || z_trup < 0) exit(0);

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x_capatana, y_capatana, z_capatana));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
        RenderSimpleMesh(meshes["teapot"], shaders["LabShader"], modelMatrix, glm::vec3(1, 1, 0));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x_trup, y_trup, z_trup));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.35f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0, 0));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x_ps, y_ps, z_ps));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f, 0.5f, 0.3f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.7f, 0.4f, 0.8f));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x_pd, y_pd, z_pd));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f, 0.5f, 0.3f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.7f, 0.4f, 0.8f));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x_ms, y_ms, z_ms));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 0.4f, 0.25f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.5f, 0.25f, 0));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x_md, y_md, z_md));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 0.4f, 0.25f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.5f, 0.25f, 0));
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (map[i][j] == 1) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f + i, 1, 0.5f + j));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 2, 1));
                RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.7f, 1, 0.7f));
            }
            if (map[i][j] == 2) {
                if (go == true)
                {
                    i1 += deltaTimeSeconds/5;
                    j1 += deltaTimeSeconds/5;
                    if (i1 > 0.3f)
                    {
                        go = false;
                        j1 = 0;
                    }
                }
                else
                {
                    i1 -= deltaTimeSeconds/5;
                    j1 -= deltaTimeSeconds/5ll;
                    if (i1 < 0)
                    {
                        go = true;
                        j1 = 0.3f;
                    }
                }

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0.4f + i + i1/2, 0, 0.4f + j + j1/2));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01f));
                RenderSimpleMesh(meshes["archer"], shaders["LabShader"], modelMatrix, glm::vec3(0.7, 0, 1));
            }
        }
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(5, 0.01f, 5));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(0, 1, 0));
    }

    {
        // bara timp
        timeleft -= 0.1f * deltaTimeSeconds;
        if (timeleft < 0) exit(0);
        projectionMatrix = glm::ortho(0.01f, 3.0f, -3.0f, 0.01f, 0.01f, 100.0f);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() + camera->forward);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(timeleft, 0.5, 0.1));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0.7f, 1));
    }

    {
        // bara viata
        projectionMatrix = glm::ortho(0.01f, 3.0f, -3.0f, 0.01f, 0.01f, 100.0f);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() + camera->forward);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.55f, -1.5f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(health, 0.5, 0.1));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0, 0));
        projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 100.0f);
    }
}


void Tema2::FrameEnd()
{
 
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    GLint lightPos = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(lightPos, 1, glm::value_ptr(lightPosition));
    glm::vec3 eyePosition = camera->position;

    GLint eyePos = glGetUniformLocation(shader->program, "eye_position");
    glUniform3fv(eyePos, 1, glm::value_ptr(eyePosition));

    GLint shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(shininess, materialShininess);
    GLint kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(kd, materialKd);
    GLint ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(ks, materialKs);
    GLint object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(object_color, 1, glm::value_ptr(color));

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat4 viewMatrix = camera -> GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
        if (window->KeyHold(GLFW_KEY_I)) {
            z_trup -= deltaTime;
            z_capatana -= deltaTime;
            z_ms -= deltaTime;
            z_md -= deltaTime;
            z_ps -= deltaTime;
            z_pd -= deltaTime;
            if (map[(int)(x_trup)][(int)(z_trup)] == 2)
            {
                health -= 0.002f;
            }
            if (map[(int) (x_trup)][(int) (z_trup)] == 1)
            {
                z_trup += 5 * deltaTime;
                z_capatana += 5 * deltaTime;
                z_ms += 5 * deltaTime;
                z_md += 5 * deltaTime;
                z_ps += 5 * deltaTime;
                z_pd += 5 * deltaTime;
            }
        }

        if (window->KeyHold(GLFW_KEY_J)) {
            x_capatana -= deltaTime;
            x_trup -= deltaTime;
            x_ms -= deltaTime;
            x_md -= deltaTime;
            x_ps -= deltaTime;
            x_pd -= deltaTime;
            if (map[(int)(x_trup)][(int)(z_trup)] == 2)
            {
                health -= 0.002f;
            }
            if (map[(int)(x_trup)][(int)(z_trup)] == 1)
            {
                x_capatana += 5 * deltaTime;
                x_trup += 5 * deltaTime;
                x_ms += 5 * deltaTime;
                x_md += 5 * deltaTime;
                x_ps += 5 * deltaTime;
                x_pd += 5 * deltaTime;
            }
        }

        if (window->KeyHold(GLFW_KEY_K)) {
            z_capatana += deltaTime;
            z_trup += deltaTime;
            z_ms += deltaTime;
            z_md += deltaTime;
            z_ps += deltaTime;
            z_pd += deltaTime;
            if (map[(int)(x_trup)][(int)(z_trup)] == 2)
            {
                health -= 0.002f;
            }
            if (map[(int)(x_trup)][(int)(z_trup)] == 1)
            {
                z_capatana -= 5 * deltaTime;
                z_trup -= 5 * deltaTime;
                z_ms -= 5 * deltaTime;
                z_md -= 5 * deltaTime;
                z_ps -= 5 * deltaTime;
                z_pd -= 5 * deltaTime;
            }
        }

        if (window->KeyHold(GLFW_KEY_L)) {
            x_capatana += deltaTime;
            x_trup += deltaTime;
            x_ms += deltaTime;
            x_md += deltaTime;
            x_ps += deltaTime;
            x_pd += deltaTime;
            if (map[(int)(x_trup)][(int)(z_trup)] == 2)
            {
                health -= 0.002f;
            }
            if (map[(int)(x_trup)][(int)(z_trup)] == 1)
            {
                x_capatana -= 5 * deltaTime;
                x_trup -= 5 * deltaTime;
                x_ms -= 5 * deltaTime;
                x_md -= 5 * deltaTime;
                x_ps -= 5 * deltaTime;
                x_pd -= 5 * deltaTime;
            }
        }

        if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
        {
            float cameraSpeed = 10;
            if (window->KeyHold(GLFW_KEY_W)) {
                camera->MoveForward(cameraSpeed * deltaTime);
            }

            if (window->KeyHold(GLFW_KEY_A)) {
                camera->TranslateRight(-cameraSpeed * deltaTime);

            }

            if (window->KeyHold(GLFW_KEY_S)) {
                camera->MoveForward(-cameraSpeed * deltaTime);

            }

            if (window->KeyHold(GLFW_KEY_D)) {
                camera->TranslateRight(cameraSpeed * deltaTime);

            }

            if (window->KeyHold(GLFW_KEY_E)) {
                camera->TranslateUpward(cameraSpeed * deltaTime);
            }

            if (window->KeyHold(GLFW_KEY_Q)) {
                camera->TranslateUpward(-cameraSpeed * deltaTime);
            }
        }
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
