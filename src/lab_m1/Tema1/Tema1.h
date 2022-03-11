#pragma once
#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float translateBulletX = 0, translateBulletY = 0;
        float scaleX, scaleY;
        float angularStep;
        float angularStep_p;
        float pi = 3.1415;
        float x, y;
        float xcamera = 0;
        float ycamera = 0;
        float speedfactor = 0;
        float x_range, y_range = 0;
        float raza_inter = 0;
        float interval = 0;
        float interval_x = 0;
        bool fill;
        float coord_x;
        float coord_y;
        float time_first_shoot = 0;
        float time_second_shoot = 0;
        float delta;
        glm::vec3 color;
        float r;
        float g;
        float b;
        float dx, dy;
        float xj, yj, xo, yo;
        float moux;
        float mouy;
        float x_projectile = 0;
        float y_projectile = 0;
        bool shooting;
        float d1 = 0, d2 = 0, raza = 0;
        float squareSide;
        float mapSide;
        float radius;
        float x_o1, y_o1, x_o2, y_o2, x_o3, y_o3, x_o4, y_o4, x_o5, y_o5, x_o6, y_o6;
        float sqSide_projectile;
        float inamic_side;
        float xe, ye;
        float ang_enem;
        float scor = 0;
        float damage = 0;
        float gamemode = 1;
        float shoot_cooldown = 1;
        float max_range = 300;
    };
}
