#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

const int WIDTH = 800;
const int HEIGHT = 600;

class HelloTriangleApplication {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

private:

  GLFWwindow * window;
  VkInstance instance;

  void initWindow() {

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
  }

  void initVulkan() {
    createInstance();
  }

  void createInstance() {
    VkApplicationInfo appInfo = {};
    // Very common in Vulkan
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char ** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(& glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    switch (result) {
    case VK_SUCCESS:
      std::cout << "Instance Created";
      break;
    case VK_ERROR_OUT_OF_HOST_MEMORY:
      throw std::runtime_error("Out of host memory");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
      throw std::runtime_error("Out of device memory");
    case VK_ERROR_INITIALIZATION_FAILED:
      throw std::runtime_error("Init failed!");
    case VK_ERROR_LAYER_NOT_PRESENT:
      throw std::runtime_error("Layer not present!");
    case VK_ERROR_EXTENSION_NOT_PRESENT:
      throw std::runtime_error("Extension not present!");
    case VK_ERROR_INCOMPATIBLE_DRIVER:
      throw std::runtime_error("Incompatible Driver!");
    }
  }

  void mainLoop() {

    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
  }
};

int main() {
  HelloTriangleApplication app;

  try{
    app.run();
  } catch(const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
