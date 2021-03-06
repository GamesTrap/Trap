#ifndef _TRAP_VULKANINDEXBUFFER_H_
#define _TRAP_VULKANINDEXBUFFER_H_

#include "Graphics/Buffers/IndexBuffer.h"

namespace TRAP::Graphics::API
{
	class VulkanIndexBuffer final : public IndexBuffer
	{
	public:
		VulkanIndexBuffer(uint32_t* indices, uint32_t size);
		VulkanIndexBuffer(const VulkanIndexBuffer&) = default;
		VulkanIndexBuffer& operator=(const VulkanIndexBuffer&) = default;
		VulkanIndexBuffer(VulkanIndexBuffer&&) = default;
		VulkanIndexBuffer& operator=(VulkanIndexBuffer&&) = default;
		virtual ~VulkanIndexBuffer();

		VkBuffer& GetHandle();
		
		uint32_t GetCount() const override;

	private:
		static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags props);
		static void CreateBuffer(VkDeviceSize size,
			                     VkBufferUsageFlags usage,
			                     VkMemoryPropertyFlags properties,
			                     VkBuffer& buffer,
			                     VkDeviceMemory& bufferMemory);
		
		uint32_t m_count;

		//Internal
		VkBuffer m_indexBuffer;
		VkDeviceMemory m_indexBufferMemory;
	};
}

#endif /*_TRAP_VULKANINDEXBUFFER_H_*/