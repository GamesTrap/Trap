#ifndef _TRAP_VERTEXBUFFER_H_
#define _TRAP_VERTEXBUFFER_H_

#include "BufferLayout.h"

namespace TRAP::Graphics
{
	enum class BufferUsage
	{
		Static,
		Dynamic
	};

	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(const VertexBuffer&) = default;
		VertexBuffer& operator=(const VertexBuffer&) = default;
		VertexBuffer(VertexBuffer&&) = default;
		VertexBuffer& operator=(VertexBuffer&&) = default;
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static std::unique_ptr<VertexBuffer> Create(float* vertices, uint32_t size, BufferUsage usage = BufferUsage::Static);
	};
}

#endif /*_TRAP_VERTEXBUFFER_H_*/