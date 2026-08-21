#include "engine/vulkan/VulkanContext.hpp"
#include "vulkan/vulkan_core.h"
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace {
VkShaderModule createShaderModule(VkDevice device, std::vector<char> &buffer);
}

void VulkanContext::createGraphicsPipeline() {
  auto vertShaderCode = readFile("shader.vert.spv");
  auto fragShaderCode = readFile("shader.frag.spv");

  if (vertShaderCode.empty() || fragShaderCode.empty())
    throw std::runtime_error("Shader not loaded!");

  auto vertShaderModule = createShaderModule(_device, vertShaderCode);
  auto fragShaderModule = createShaderModule(_device, fragShaderCode);

  VkPipelineShaderStageCreateInfo vertShaderStageInfo{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_VERTEX_BIT,
      .module = vertShaderModule,
      .pName = "main"};

  VkPipelineShaderStageCreateInfo fragShaderStageInfo{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
      .module = fragShaderModule,
      .pName = "main"};

  VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo,
                                                    fragShaderStageInfo};

  vkDestroyShaderModule(_device, vertShaderModule, nullptr);
  vkDestroyShaderModule(_device, fragShaderModule, nullptr);
}

namespace {
VkShaderModule createShaderModule(VkDevice device, std::vector<char> &buffer) {
  VkShaderModuleCreateInfo createInfo{
      .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
      .codeSize = buffer.size(),
      .pCode = reinterpret_cast<const uint32_t *>(buffer.data())};

  VkShaderModule shaderModule;

  if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) !=
      VK_SUCCESS)
    throw std::runtime_error("Failed to create shader module!");

  return shaderModule;
}
} // namespace
