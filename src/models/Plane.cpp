#include "Plane.h"
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"

Plane::Plane()
{
    float planeVertices[] = {
         20000.0f, -0.0f,  20000.0f,  0.0f, 1.0f, 0.0f,  6000.0f,  0.0f,
        -20000.0f, -0.0f,  20000.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -20000.0f, -0.0f, -20000.0f,  0.0f, 1.0f, 0.0f,   0.0f, 6000.0f,

         20000.0f, -0.0f,  20000.0f,  0.0f, 1.0f, 0.0f,  6000.0f,  0.0f,
        -20000.0f, -0.0f, -20000.0f,  0.0f, 1.0f, 0.0f,   0.0f, 6000.0f,
         20000.0f, -0.0f, -20000.0f,  0.0f, 1.0f, 0.0f,  6000.0f, 6000.0f
    };

    glGenVertexArrays(1, &planeVAO);    //generowanie bufora planeVAO
    glGenBuffers(1, &planeVBO);         //generowanie bufora planeVBO
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);        //ustalamy typ bufora planeVBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);    //kopiowanie danych wierzcholkowych do pamieci bufora
    glEnableVertexAttribArray(0);       //ustawienia pierwszego atrybutu wierzcholka - pozycji 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);   //ktory atrybut wierzcholka, rozmiar atrybutu, ..., ..., skok (stride), gdzie dane pozycji zaczynaja sie w buforze
    glEnableVertexAttribArray(1);       //ustawienia drugiego atrybutu wierzcholka - wektorow normalnych
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);       //ustawienia trzeciego atrybutu wierzcholka - texCoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);   //You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens.

    groundDiffuseMap = loadTexture("res/textures/grass.jpg").id;
}

void Plane::DrawShape(Shader& shader)
{
    glBindVertexArray(planeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, groundDiffuseMap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // opcje zawijania tekstury, na os s i t - odpowiadajace x i y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // opcje filtrowania tesktury, GL_NEAREST- OpenGL wybiera piksel, ktorego srodek znajduje się najblizej danej wspolrzednej tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // GL_LINEAR- interpoluje (usrednia) wartosc tekseli, które są najblizej wspolrzednej tekstury
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
