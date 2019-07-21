#ifndef _TRAP_D3D12VERTEXARRAY_H_
#define _TRAP_D3D12VERTEXARRAY_H_

#ifdef TRAP_PLATFORM_WINDOWS

namespace TRAP::Graphics::API
{
	class D3D12VertexArray final : public VertexArray
	{
	public:
		D3D12VertexArray();
		D3D12VertexArray(const D3D12VertexArray&) = default;
		D3D12VertexArray& operator=(const D3D12VertexArray&) = default;
		D3D12VertexArray(D3D12VertexArray&&) = default;
		D3D12VertexArray& operator=(D3D12VertexArray&&) = default;
		~D3D12VertexArray();

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

#endif

#endif /*_TRAP_D3D12VERTEXARRAY_H_*/