#pragma once

namespace TRAP::Graphics
{
	class D3D12Renderer final : public Renderer
	{
	public:
		D3D12Renderer();
		~D3D12Renderer();
		D3D12Renderer(const D3D12Renderer&) = default;
		D3D12Renderer& operator=(const D3D12Renderer&) = default;
		D3D12Renderer(D3D12Renderer&&) = default;
		D3D12Renderer& operator=(D3D12Renderer&&) = default;

		void InitInternal() override;

		void ClearInternal(unsigned int buffer) override;
		void PresentInternal(Window* window) override;

		void SetDepthTestingInternal(bool enabled) override;
		void SetBlendInternal(bool enabled) override;
		void SetViewportInternal(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;

		void SetBlendFunctionInternal(RendererBlendFunction source, RendererBlendFunction destination) override;
		void SetBlendEquationInternal(RendererBlendEquation blendEquation) override;

		std::string_view GetTitleInternal() const override;

		static D3D12Renderer* Get() { return reinterpret_cast<D3D12Renderer*>(s_Instance.get()); }

	private:
		API::D3D12Context* m_context;
		std::string m_rendererTitle;
	};
}
