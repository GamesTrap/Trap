#ifndef _TRAP_VULKANVERTEXBUFFER_H_
#define _TRAP_VULKANVERTEXBUFFER_H_

namespace TRAP::Graphics::API
{
	class VulkanVertexBuffer final : public VertexBuffer
	{
	public:
		VulkanVertexBuffer(float* vertices, uint32_t size, BufferUsage usage);
		VulkanVertexBuffer(const VulkanVertexBuffer&) = default;
		VulkanVertexBuffer& operator=(const VulkanVertexBuffer&) = default;
		VulkanVertexBuffer(VulkanVertexBuffer&&) = default;
		VulkanVertexBuffer& operator=(VulkanVertexBuffer&&) = default;
		~VulkanVertexBuffer();

		void Bind() override;
		void Unbind() override;

		const BufferLayout& GetLayout() const override;
		void SetLayout(const BufferLayout& layout) override;

	private:
		BufferLayout m_layout;
	};
}

#endif /*_TRAP_VULKANVERTEXBUFFER_H_*/