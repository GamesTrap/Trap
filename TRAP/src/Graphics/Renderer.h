#ifndef _TRAP_RENDERER_H_
#define _TRAP_RENDERER_H_

#include "API/RendererAPI.h"
#include "Buffers/UniformBuffer.h"

namespace TRAP::Graphics
{
	namespace API 
	{
		class Shader;
	}

	class OrthographicCamera;

	class Renderer
	{
	public:
		static std::string_view GetTitle();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const API::Shader* shader, const std::unique_ptr<VertexArray>& vertexArray);

		static void Cleanup();

	private:
		struct SceneData
		{
			SceneData()
				: m_projectionMatrix(0.0f), m_viewMatrix(0.0f)
			{
			}

			Maths::Mat4 m_projectionMatrix;
			Maths::Mat4 m_viewMatrix;
		};

		static std::unique_ptr<SceneData> m_sceneData;
		static std::unique_ptr<UniformBuffer> m_uniformBuffer;
	};
}

//-------------------------------------------------------------------------------------------------------------------//

inline std::string_view TRAP::Graphics::Renderer::GetTitle()
{
	return API::RendererAPI::GetRenderer()->GetTitle();
}

#endif /*_TRAP_RENDERER_H_*/