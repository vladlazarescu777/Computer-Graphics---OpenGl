#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/Tema2/lab_camera.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        glm::mat4 projectionMatrix;
        implemented::Camera_tema* camera;

        bool poz = false, go = true;

        float x_capatana = 0, y_capatana = 0, z_capatana = 0;
        float x_trup = 0, y_trup = 0, z_trup = 0;
        float x_ms = 0, y_ms = 0, z_ms = 0;
        float x_md = 0, y_md = 0, z_md = 0;
        float x_ps = 0, y_ps = 0, z_ps = 0;
        float x_pd = 0, y_pd = 0, z_pd = 0;

        float i1 = 0, j1 = 0;

        int x, y, z, map_nr;

        int map[10][10];

        int map1[10][10] = { {1,1,1,1,1,1,0,1,1,1},
                            {1,0,0,0,0,0,0,0,0,1},
                            {1,0,1,1,1,1,1,1,0,1},
                            {1,0,1,0,2,0,0,0,0,1},
                            {1,0,1,0,1,1,1,1,1,1},
                            {0,0,1,0,1,0,0,2,0,0},
                            {1,0,2,0,1,1,0,1,1,1},
                            {1,0,1,0,0,0,0,1,0,1},
                            {1,0,1,1,2,1,0,2,0,1},
                            {1,1,1,1,1,1,0,1,1,1} };

        int map2[10][10] = { {1,1,1,1,0,1,1,1,1,1},
                             {1,0,0,0,0,0,0,0,0,1},
                             {1,0,1,1,1,1,1,1,0,1},
                             {1,0,1,0,0,0,2,0,0,1},
                             {0,0,1,0,1,1,1,1,0,0},
                             {1,0,1,0,1,0,0,0,0,1},
                             {1,0,2,0,1,1,0,1,1,1},
                             {1,0,1,0,2,0,0,1,0,1},
                             {1,0,1,0,0,1,0,2,0,1},
                             {1,1,1,0,1,1,1,1,1,1} };

        int map3[10][10] = {  {1,1,1,1,0,1,1,1,1,1},
                             {1,0,0,0,2,0,0,0,0,1},
                             {1,0,1,2,1,0,1,1,0,1},
                             {1,0,1,0,0,0,2,0,0,1},
                             {1,0,1,0,1,1,1,1,0,0},
                             {1,0,1,0,1,0,0,0,0,1},
                             {1,0,2,0,1,1,0,1,2,1},
                             {1,2,1,0,2,0,0,1,0,1},
                             {1,1,1,0,2,0,0,2,0,1},
                             {1,1,1,1,1,1,1,1,1,1} };

        int map4[10][10] = { {1,1,1,1,1,1,1,1,1,1},
                             {1,0,0,0,2,0,0,0,0,1},
                             {1,0,1,2,1,0,1,1,0,1},
                             {1,1,1,0,0,0,2,0,0,1},
                             {1,1,1,0,1,1,1,1,0,0},
                             {0,2,1,0,1,0,0,0,0,1},
                             {1,2,2,0,0,1,0,1,2,1},
                             {1,2,1,1,2,0,0,1,0,1},
                             {1,1,1,1,2,0,0,2,0,1},
                             {1,1,1,1,0,1,1,1,1,1} };

        int map5[10][10] = {  {1,0,1,1,1,1,1,1,1,1},
                             {1,0,0,0,2,0,0,0,0,1},
                             {1,1,1,2,1,1,1,1,0,1},
                             {1,1,1,0,0,2,2,0,0,1},
                             {1,1,1,0,1,1,1,1,2,1},
                             {1,1,1,0,1,0,0,0,2,1},
                             {1,1,2,0,0,0,0,1,2,1},
                             {1,2,1,1,2,0,0,1,0,1},
                             {1,1,1,1,2,0,0,2,0,1},
                             {1,1,1,1,1,1,1,1,0,1} };

        int map6[10][10] = {  {1,1,1,1,1,1,1,1,1,1},
                             {1,0,0,0,2,0,0,0,0,1},
                             {1,1,1,2,1,1,1,1,0,1},
                             {1,1,1,0,0,2,2,0,0,1},
                             {1,1,1,0,1,1,1,1,2,1},
                             {1,1,1,0,1,1,1,1,2,1},
                             {1,1,2,0,0,2,1,1,2,1},
                             {1,1,1,1,1,2,1,1,0,1},
                             {1,1,1,1,1,2,1,2,0,1},
                             {1,1,1,1,1,0,1,1,1,1} };

        int map7[10][10] = {  {1,1,1,1,1,1,1,1,1,1},
                             {1,2,0,0,0,0,0,0,2,1},
                             {1,0,1,2,1,1,1,0,0,1},
                             {1,0,1,0,0,2,2,0,0,1},
                             {1,0,1,0,1,1,1,0,0,1},
                             {1,0,1,0,1,1,1,0,0,1},
                             {1,0,2,1,1,2,1,0,0,1},
                             {1,0,1,1,0,0,0,0,0,1},
                             {1,2,0,0,0,0,0,0,2,1},
                             {1,0,1,1,1,1,1,1,1,1} };

        int map8[10][10] = { {1,1,1,1,1,1,1,1,1,1},
                             {1,0,0,0,0,0,0,0,0,1},
                             {1,2,2,2,2,2,2,2,2,1},
                             {1,2,2,2,2,2,2,2,2,1},
                             {1,2,2,2,2,2,2,2,2,0},
                             {0,2,2,2,2,2,2,2,2,1},
                             {1,2,2,2,2,2,2,2,2,1},
                             {1,2,2,2,2,2,2,2,2,1},
                             {1,0,0,0,0,0,0,0,0,1},
                             {1,1,1,1,1,1,1,1,1,1} };

        float health = 1.5f;
        float timeleft = 6;
                           
    };
}   // namespace m1
