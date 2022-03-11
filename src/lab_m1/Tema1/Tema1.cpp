#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <math.h>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;



Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    x = 0;
    y = 0;
   glm::vec3 corner = glm::vec3(x, y, 0);
   squareSide = 150;
   std::cout << "========= EASY MODE ON ============== \n\n";
   std::cout << scor << "  PUNCTE \n ========================= \n \n \n";

   Mesh* obstacol = object2D::CreateSquare("obstacol", corner, squareSide, glm::vec3(0.2f, 0.7f, 0.3f), true);
   AddMeshToList(obstacol);

   x_o1 = rand() % 1200 + 100;
   y_o1 = rand() % 1200 + 100;
   x_o2 = rand() % 1200 + 100;
   y_o2 = rand() % 1200 + 100;
   x_o3 = rand() % 1200 + 100;
   y_o3 = rand() % 1200 + 100;
   x_o4 = rand() % 1200 + 100;
   y_o4 = rand() % 1200 + 100;
   x_o5 = rand() % 1200 + 100;
   y_o5 = rand() % 1200 + 100;
   x_o6 = rand() % 1200 + 100;
   y_o6 = rand() % 1200 + 100;

   mapSide = 1500;
   Mesh* map = object2D::CreateSquare("map", corner, mapSide, glm::vec3(0.3f, 0.3f, 0.3f), true);
   AddMeshToList(map);

    translateX = 0;
    translateY = 0;
    angularStep = 0;
    translateBulletX = 0;
    translateBulletY = 0;
    fill = true;
    xj = resolution.x / 2;
    yj = resolution.y / 2;
    glm::vec3 center = glm::vec3(xj, yj, 0);
    radius = 30;
    r = 0.9f;
    g = 0.8f;
    b = 0.2f;
    color = glm::vec3(r, g, b);
    Mesh* jucator = object2D::CreateCircle("jucator", center, radius, color, fill, true);
    AddMeshToList(jucator);

    xo = xj - 15;
    yo = yj - 15;
    glm::vec3 center_ochi = glm::vec3(xo, yo, 0);
    float radius_ochi = 18;
    r = 0.9f;
    g = 0.5f;
    b = 0.1f;
    color = glm::vec3(r, g, b);
    Mesh* ochi= object2D::CreateCircle("ochi", center_ochi, radius_ochi, color, fill, true);
    AddMeshToList(ochi);

    sqSide_projectile = 25;
    glm::vec3 corner_projectile = glm::vec3(x_projectile - sqSide_projectile / 2, y_projectile - sqSide_projectile / 2, 0);
    r = 0;
    g = 0;
    b = 0;
    color = glm::vec3(r, g, b);
    Mesh* projectile = object2D::CreateSquare("projectile", corner_projectile, sqSide_projectile, color, fill);
    AddMeshToList(projectile);

    /*x_range = xj;
    y_range = yj;
    glm::vec3 center_range = glm::vec3(x_range, y_range, 0);
    float radius_range = 300;
    r = 1;
    g = 0;
    b = 0;
    color = glm::vec3(r, g, b);
    fill = false;
    Mesh* range = object2D::CreateCircle("range", center_range, radius_range, color, fill);
    AddMeshToList(range);*/

    xe = rand() % 1200 + 100;
    ye = rand() % 1200 + 100;
    glm::vec3 corner_inamic = glm::vec3(0, 0, 0);
    inamic_side = 100;
    Mesh* inamic = object2D::CreateSquare("inamic", corner_inamic, inamic_side, glm::vec3(1, 0.1f, 0), true);
    AddMeshToList(inamic);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(xcamera, ycamera, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    glm::ivec2 resolution = window->GetResolution();
    GetCameraInput()->SetActive(false);

    dx = xe + inamic_side/2 - xj;
    dy = ye + inamic_side/2 - yj;
    ang_enem = glm::atan(dy, dx) + pi/2;

    //helth
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(903, 633);
    if (2.20f - damage / 2 >= 0)
    {
        modelMatrix *= transform2D::Scale(2.20f - damage / 2, 0.30f);
    }
    else
    {
        std::cout << "======GAME OVER====== \n" << "SCOR FINAL: " << scor << "\n";
        exit(0);
    }
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    //cadran healthbar
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(900, 630);
    modelMatrix *= transform2D::Scale(2.25f, 0.35f);
    RenderMesh2D(meshes["obstacol"], shaders["Simple"], modelMatrix);


    //inamic
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(xe + inamic_side / 2, ye + inamic_side / 2);
    modelMatrix *= transform2D::Rotate(ang_enem);
    modelMatrix *= transform2D::Translate(-xe -inamic_side/2, -ye -inamic_side/ 2);
    modelMatrix *= transform2D::Translate(xe, ye);
    RenderMesh2D(meshes["inamic"], shaders["VertexColor"], modelMatrix);

    //ochi1-ianmic
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(xe + inamic_side / 2, ye + inamic_side / 2);
    modelMatrix *= transform2D::Rotate(ang_enem);
    modelMatrix *= transform2D::Translate(-xe - inamic_side / 2, -ye - inamic_side / 2);
    modelMatrix *= transform2D::Translate(xe + inamic_side * 0.7, ye + inamic_side * 0.8);
    modelMatrix *= transform2D::Scale(0.3, 0.3);
    RenderMesh2D(meshes["inamic"], shaders["Simple"], modelMatrix);

    //ochi2-inamic
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(xe + inamic_side / 2, ye + inamic_side / 2);
    modelMatrix *= transform2D::Rotate(ang_enem);
    modelMatrix *= transform2D::Translate(-xe - inamic_side / 2, -ye - inamic_side / 2);
    modelMatrix *= transform2D::Translate(xe , ye + inamic_side * 0.8);
    modelMatrix *= transform2D::Scale(0.3, 0.3);
    RenderMesh2D(meshes["inamic"], shaders["Simple"], modelMatrix);

    //ochi1
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(xj , yj);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-xj, -yj);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    RenderMesh2D(meshes["ochi"], shaders["VertexColor"], modelMatrix);
    
    //ochi2
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(xj, yj);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-xj, -yj);
    modelMatrix *= transform2D::Translate(translateX+30, translateY);
    RenderMesh2D(meshes["ochi"], shaders["VertexColor"], modelMatrix);

    //jucator
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    RenderMesh2D(meshes["jucator"], shaders["VertexColor"], modelMatrix);

    //obstacole
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x_o1, y_o1);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x_o2, y_o2);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x_o3, y_o3);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x_o4, y_o4);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x_o5, y_o5);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x_o6, y_o6);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);


    //proiectil
    modelMatrix = glm::mat3(1);

    if (shooting == true)
    {
        interval = raza / 15;
        interval_x = d1 / 15;
        time_first_shoot = time_second_shoot;

        translateBulletX += interval_x * 30 * deltaTimeSeconds;
        raza_inter += interval * 30 * deltaTimeSeconds;
        translateBulletY = sqrt(raza_inter * raza_inter - translateBulletX * translateBulletX);

        if (mouy >= coord_y && moux >= coord_x)
        {
            modelMatrix *= transform2D::Translate(translateBulletX, translateBulletY);
            x_projectile += interval_x * 30 * deltaTimeSeconds;
            y_projectile = translateBulletY;
        }
        else if (mouy >= coord_y && moux <= coord_x)
        {
            modelMatrix *= transform2D::Translate(-translateBulletX, translateBulletY);
            x_projectile -= interval_x * 30 * deltaTimeSeconds;
            y_projectile = translateBulletY;
        }
        else if (mouy <= coord_y && moux <= coord_x)
        {
            modelMatrix *= transform2D::Translate(-translateBulletX, -translateBulletY);
            x_projectile -= interval_x * 30 * deltaTimeSeconds;
            y_projectile = -translateBulletY;
        }
        else if (mouy <= coord_y && moux >= coord_x)
        {
            modelMatrix *= transform2D::Translate(translateBulletX, -translateBulletY);
            x_projectile += interval_x * 30 * deltaTimeSeconds;
            y_projectile = -translateBulletY;
        }

        if (sqrt(x_projectile * x_projectile + y_projectile * y_projectile) >= max_range ||  // fire distance + colturi mapa
            x_projectile + coord_x - sqSide_projectile < 0 || y_projectile + coord_y - sqSide_projectile < 0 ||
            x_projectile + coord_x + sqSide_projectile > mapSide || y_projectile + coord_y + sqSide_projectile > mapSide)
        {
            x_projectile = 0;
            y_projectile = 0;
            translateBulletX = 0;
            translateBulletY = 0;
            raza_inter = 0;
            shooting = false;
        }

        //coliziune glont inamic
        if (sqrt(pow((coord_x + x_projectile - (xe + inamic_side / 2)), 2) + pow((coord_y + y_projectile - (ye + inamic_side / 2)), 2)) < sqSide_projectile / 2 + inamic_side / 2)
        {
            x_projectile = 0;
            y_projectile = 0;
            translateBulletX = 0;
            translateBulletY = 0;
            raza_inter = 0;
            shooting = false;
            //respawn
            xe = rand() % 1200;
            ye = rand() % 1200;
            scor++;
            
            std::cout << scor << "  PUNCTE \n";
            if (scor == 10)
            {
                std::cout <<  "Felicitari!";
                exit(0);
            }
        }
        modelMatrix *= transform2D::Translate(coord_x, coord_y);
        modelMatrix *= transform2D::Rotate(angularStep_p);
        modelMatrix *= transform2D::Translate(-coord_x,-coord_y);
        modelMatrix *= transform2D::Translate(coord_x, coord_y);
        RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);
    }

    //mapa
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["map"], shaders["VertexColor"], modelMatrix);
}


void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{

    if (window->KeyHold(GLFW_KEY_W) && yj < 1500 - radius)
    {
        translateY += 200 * deltaTime;
        yj += 200 * deltaTime;
        yo += 200 * deltaTime;
        ycamera += 200 * deltaTime;
        if (sqrt(pow((xj - (x_o1 + squareSide / 2)), 2) + pow((yj - (y_o1 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o2 + squareSide / 2)), 2) + pow((yj - (y_o2 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o3 + squareSide / 2)), 2) + pow((yj - (y_o3 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o4 + squareSide / 2)), 2) + pow((yj - (y_o4 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o5 + squareSide / 2)), 2) + pow((yj - (y_o5 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o6 + squareSide / 2)), 2) + pow((yj - (y_o6 + squareSide / 2)), 2)) < radius + squareSide / 2)
        {
            //bounce
            damage += gamemode * deltaTime;
            translateY -= 200 * deltaTime;
            yj -= 200 * deltaTime;
            yo -= 200 * deltaTime;
            ycamera -= 200 * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_S) && yj > radius)
    {
        translateY -= 200 * deltaTime;
        yj -= 200 * deltaTime;
        yo -= 200 * deltaTime;
        ycamera -= 200 * deltaTime;
        if (sqrt(pow((xj - (x_o1 + squareSide / 2)), 2) + pow((yj - (y_o1 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o2 + squareSide / 2)), 2) + pow((yj - (y_o2 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o3 + squareSide / 2)), 2) + pow((yj - (y_o3 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o4 + squareSide / 2)), 2) + pow((yj - (y_o4 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o5 + squareSide / 2)), 2) + pow((yj - (y_o5 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o6 + squareSide / 2)), 2) + pow((yj - (y_o6 + squareSide / 2)), 2)) < radius + squareSide / 2 )
        {
           //bounce
           damage += gamemode * deltaTime;
           translateY += 200 * deltaTime;
           yj += 200 * deltaTime;
           yo += 200 * deltaTime;
           ycamera += 200 * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_A) && xj > radius )
    {
        translateX -= 200 * deltaTime;
        xj -= 200 * deltaTime;
        xo -= 200 * deltaTime;
        xcamera -= 200 * deltaTime;
        if (sqrt(pow((xj - (x_o1 + squareSide / 2)), 2) + pow((yj - (y_o1 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o2 + squareSide / 2)), 2) + pow((yj - (y_o2 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o3 + squareSide / 2)), 2) + pow((yj - (y_o3 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o4 + squareSide / 2)), 2) + pow((yj - (y_o4 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o5 + squareSide / 2)), 2) + pow((yj - (y_o5 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o6 + squareSide / 2)), 2) + pow((yj - (y_o6 + squareSide / 2)), 2)) < radius + squareSide / 2)
        {
            //bounce
            damage += gamemode * deltaTime;
            translateX += 200 * deltaTime;
            xj += 200 * deltaTime;
            xo += 200 * deltaTime;
            xcamera += 200 * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_D) && xj < 1500 - radius)
    {
        translateX += 200 * deltaTime;
        xj += 200 * deltaTime;
        xo += 200 * deltaTime;
        xcamera += 200 * deltaTime;
        if (sqrt(pow((xj - (x_o1 + squareSide / 2)), 2) + pow((yj - (y_o1 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o2 + squareSide / 2)), 2) + pow((yj - (y_o2 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o3 + squareSide / 2)), 2) + pow((yj - (y_o3 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o4 + squareSide / 2)), 2) + pow((yj - (y_o4 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o5 + squareSide / 2)), 2) + pow((yj - (y_o5 + squareSide / 2)), 2)) < radius + squareSide / 2 ||
            sqrt(pow((xj - (x_o6 + squareSide / 2)), 2) + pow((yj - (y_o6 + squareSide / 2)), 2)) < radius + squareSide / 2)
        {
            //bounce
            damage += gamemode * deltaTime;
            translateX -= 200 * deltaTime;
            xj -= 200 * deltaTime;
            xo -= 200 * deltaTime;
            xcamera -= 200 * deltaTime;
        }
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (window->KeyHold(GLFW_KEY_O)) // change gamemode (easy - hard)
    {
        if (gamemode == 1) {
            gamemode = 3; //creste dificultatea
            shoot_cooldown = 2;
            std::cout << "========= HARD MODE ON ============== \n\n";
        }
        else if (gamemode == 3) {
            gamemode = 1; //scade dificultatea
            shoot_cooldown = 1;
            std::cout << "========= EASY MODE ON ============== \n\n";
        }
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event

}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    glm::ivec2 resolution = window->GetResolution();
    dx = xcamera + mouseX - xj;
    dy = ycamera + resolution.y - mouseY - yj;
    angularStep = glm::atan(dy, dx) + pi/2;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    glm::ivec2 resolution = window->GetResolution();
    // cooldown tragere
    time_second_shoot = glfwGetTime();
    delta = time_second_shoot - time_first_shoot;
    if (delta >= shoot_cooldown)
    {
        mouy = (float)ycamera + resolution.y - mouseY;
        moux = (float)xcamera + mouseX;

        dx = xcamera + mouseX - xj;
        dy = ycamera + resolution.y - mouseY - yj;
        angularStep_p = glm::atan(dy, dx) + pi / 2;

        shooting = true;
        d1 = abs(xcamera + mouseX - xj);
        d2 = abs(ycamera + resolution.y - mouseY - yj);
        raza = sqrt(d1 * d1 + d2 * d2);
        coord_x = xj;
        coord_y = yj;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
