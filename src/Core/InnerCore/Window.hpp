#pragma once
#include <OpenGL.hpp>
#include <string>

struct Window {
   float Width;
   float Height;

   Window(int width, int height, const std::string &name);

   ~Window();

   bool ShouldClose();

   void SwapBuffers();

   void PollEvents();

   void SetTitle(const std::string &name);

   void Close();

   GLFWwindow *GetGlfwWindow();

   Window(const Window &) = delete;

   Window &operator=(const Window &) = delete;

private:
   GLFWwindow *GlfwWindow;
};
