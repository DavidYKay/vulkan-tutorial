VULKAN_SDK_PATH = /home/dk/Tools/vr/c/vulkan/1.1.82.1/x86_64

CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

VulkanTest: hello_vulkan.cpp
		g++ $(CFLAGS) -o VulkanTest hello_vulkan.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
		LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/explicit_layer.d ./VulkanTest

clean:
		rm -f VulkanTest
