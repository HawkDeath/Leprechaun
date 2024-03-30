/*
#include <BaseApplication.h>
#include <Log/Log.h>
#include <Renderer/Shader.h>


class Demo final : public Leprechaun::BaseApplication {
public:
  explicit Demo(int argc, char *argv[]) {
    Leprechaun::ApplicationConfig config;
    Leprechaun::BaseApplication(argc, argv, config);
  }
  virtual ~Demo() = default;

protected:
  void onInitialize() override {
    auto input = mWindow->getInput();

    Leprechaun::KeyEvent escapse;
    escapse.key = Leprechaun::InputUtils::Key::Escape;
    escapse.state = Leprechaun::InputUtils::KeyState::Down;
    escapse.name = "quit_program";
    escapse.fn = [&]() -> void {
      glfwSetWindowShouldClose(mWindow->glfwWindow(), GLFW_TRUE);
    };

    input->registerKeyEvent(escapse);

    Leprechaun::KeyEvent test;
    test.key = Leprechaun::InputUtils::Key::Enter;
    test.state = Leprechaun::InputUtils::KeyState::Down;
    test.name = "test_event";
    test.fn = [&]() -> void { LOG("Enter has been pressed") };

    input->registerKeyEvent(test);

    Leprechaun::KeyEvent test2;
    test2.key = Leprechaun::InputUtils::Key::W;
    test2.state = Leprechaun::InputUtils::KeyState::Hold;
    test2.name = "test2_event";
    test2.fn = [&]() -> void { LOG(" has been pressed") };

    input->registerKeyEvent(test2);

    Leprechaun::KeyEvent whatWinSize;
    whatWinSize.key = Leprechaun::InputUtils::Key::F11;
    whatWinSize.state = Leprechaun::InputUtils::KeyState::Down;
    whatWinSize.name = "whatWinSize_event";
    whatWinSize.fn = [this]() -> void { LOG("{}x{}", getConfig().windowSize.width, getConfig().windowSize.height) };

    input->registerKeyEvent(whatWinSize);

    Leprechaun::KeyEvent testMouse;
    testMouse.button = Leprechaun::InputUtils::MouseButton::Left;
    testMouse.state = Leprechaun::InputUtils::KeyState::Down;
    testMouse.name = "test_mouse_event";
    testMouse.fn = [&]() -> void { LOG("Left button has been pressd") };

    input->registerMouseEvent(testMouse);
    Leprechaun::Api::ShaderDescription pipelineDesc;
    pipelineDesc.name = "baseShader";
    pipelineDesc.vertexShaderSources = shader_test::baseVertexShader;
    pipelineDesc.fragmenShaderSources = shader_test::baseFragmentShader;
    baseShader = std::make_unique<Leprechaun::Api::Shader>(pipelineDesc);

    glfwSwapInterval(0);
  }

  void onUpdate(const float &delta) override { (void)delta; }

  void onDraw() override {
    baseShader->use();
    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!"
                                     // and append into it.

      ImGui::Text("This is some useful text."); // Display some text (you can
                                                // use a format strings too)
      ImGui::Checkbox(
          "Demo Window",
          &show_demo_window); // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f,
                         1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3(
          "clear color",
          (float *)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button")) // Buttons return true when clicked (most
                                   // widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window) {
      ImGui::Begin(
          "Another Window",
          &show_another_window); // Pass a pointer to our bool variable (the
                                 // window will have a closing button that will
                                 // clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
        show_another_window = false;
      ImGui::End();
    }
    baseShader->unUse();
  }

private:
  bool show_demo_window = true;
  bool show_another_window = false;
  std::unique_ptr<Leprechaun::Api::Shader> baseShader;

};

IMPLEMENT_DEMO(Demo)
*/
#include <volk/volk.h>
#include <vulkan/vulkan.h>
#include <spdlog/spdlog.h>

int main()
{
    VkResult result = volkInitialize();

    uint32_t api_version;
    vkEnumerateInstanceVersion(&api_version);

    spdlog::info("VulkanAPI version {}.{}.{}", VK_API_VERSION_MAJOR(api_version), VK_API_VERSION_MINOR(api_version),
                 VK_API_VERSION_PATCH(api_version));

    return 0;
}