#ifndef LEPRECHAUN_WINDOW_H
#define LEPRECHAUN_WINDOW_H

#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
#include "glfw/include/GLFW/glfw3.h"
#include "ApplicationConfig.h"
#include "Input/Input.h"

#include <memory>
#include <vector>

namespace Leprechaun {

    class Window final {
    public:
        Window(ApplicationConfig &appConfig);

        ~Window();

        static ApplicationConfig default_window_config() { return ApplicationConfig(); }

        void update();

        [[nodiscard]] GLFWwindow *glfwWindow() const noexcept { return mWindow; }

        std::shared_ptr<Input> getInput() const noexcept { return mInput; }

        void createVkSurface(VkInstance &instance, VkSurfaceKHR &surface);

        std::vector<const char *> get_vk_extensions() const;

        bool shouldClose() const { return glfwWindowShouldClose(mWindow); }

        void swapBuffer() const { glfwSwapBuffers(mWindow); }

    private:
        static void handleFramebufferResize(GLFWwindow *window_, int w, int h);

        static void handleWindowResize(GLFWwindow *window_, int w, int h);

        static void handleMinimalize(GLFWwindow *window_, int status);

        // input
        static void handleKeyInput(GLFWwindow *window_, int key, int scancode,
                                   int action, int mods);

        static void handleMousePosition(GLFWwindow *window_, double xPos,
                                        double yPos);

        static void handleMouseButton(GLFWwindow *window_, int mouseButton,
                                      int action, int mods);

    private:
        GLFWwindow *mWindow;
        std::shared_ptr<Input> mInput;
        ApplicationConfig &mAppConfig;
        bool mMinimalized;
    };

} // namespace Leprechaun

#endif // LEPRECHAUN_WINDOW_H