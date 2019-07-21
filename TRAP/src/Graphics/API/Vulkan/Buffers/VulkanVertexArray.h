#ifndef _TRAP_VULKANVERTEXARRAY_H_
#define _TRAP_VULKANVERTEXARRAY_H_

namespace TRAP::Graphics::API
{
	class VulkanVertexArray final : public VertexArray
	{
	public:
		VulkanVertexArray();
		VulkanVertexArray(const VulkanVertexArray&) = default;
		VulkanVertexArray& operator=(const VulkanVertexArray&) = default;
		VulkanVertexArray(VulkanVertexArray&&) = default;
		VulkanVertexArray& operator=(VulkanVertexArray&&) = default;
		~VulkanVertexArray();

		void AddVertexBuffer(std::unique_ptr<VertexBuffer>& buffer) override;
		void SetIndexBuffer(std::unique_ptr<IndexBuffer>& buffer) override;

		std::vector<std::unique_ptr<VertexBuffer>>& GetVertexBuffers() override;
		IndexBuffer* GetIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

	private:
		std::vector<std::unique_ptr<VertexBuffer>> m_vertexBuffers;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
	};
}

#endif /*_TRAP_VULKANVERTEXARRAY_H_*/