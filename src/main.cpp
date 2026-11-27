#include <iostream>
#include <vector>
#include <cmath> 

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "implot.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


int w, h, x;
int current_read = 5;

std::vector<float> ys;
std::vector<float> xs;
float t = static_cast<float>(glfwGetTime()); 


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main()

{
    if (!glfwInit())
    {
        std::cout << "failed to load\n";
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "My GUI", NULL, NULL);
    if (!window)
    {
        std::cout << "Window or OpenGL context creation failed\n";
        glfwTerminate();
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);   // vor ImGui-Init

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    while (!glfwWindowShouldClose(window))
    {               
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0,0,w,h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);  

        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        float t = static_cast<float>(glfwGetTime());   // Sekunden seit Programmstart
        xs.push_back(t);
        ys.push_back(std::sin(t));  
        ImGui::Begin("My first plot");
        if (ImPlot::BeginPlot("Squares")) {
            ImPlot::SetupAxisLimits(ImAxis_X1, t - 10.00, t + 10.00, ImPlotCond_Always);
            ImPlot::PlotLine("sin", xs.data(), ys.data(), static_cast<int>(xs.size()));
            ImPlot::EndPlot();
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}