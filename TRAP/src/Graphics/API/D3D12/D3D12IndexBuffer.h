#ifndef _TRAP_D3D12INDEXBUFFER_H_
#define _TRAP_D3D12INDEXBUFFER_H_

namespace TRAP::Graphics::API
{
	class D3D12IndexBuffer : public IndexBuffer
	{
	public:
		D3D12IndexBuffer(uint32_t* indices, uint32_t size, BufferUsage usage);
		D3D12IndexBuffer(const D3D12IndexBuffer&) = default;
		D3D12IndexBuffer& operator=(const D3D12IndexBuffer&) = default;
		D3D12IndexBuffer(D3D12IndexBuffer&&) = default;
		D3D12IndexBuffer& operator=(D3D12IndexBuffer&&) = default;
		virtual ~D3D12IndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override;

	private:
		uint32_t m_count;
	};
}

#endif