#ifndef _TRAP_OPENGLSHADER_H_
#define _TRAP_OPENGLSHADER_H_

#include "Graphics/Shaders/Shader.h"
#include "Graphics/Shaders/ShaderManager.h"

namespace TRAP::Graphics::API
{
	class OpenGLShader final : public Shader
	{
	public:
		OpenGLShader(std::string name, std::string_view source);
		OpenGLShader(std::string name, const std::vector<uint32_t>& source);
		OpenGLShader(std::string name, std::string_view VSSource, std::string_view FSSource, std::string_view GSSource, std::string_view TCSSource, std::string_view TESSource, std::string_view CSSource);
		OpenGLShader(const OpenGLShader&) = delete;
		OpenGLShader& operator=(const OpenGLShader&) = delete;
		OpenGLShader(OpenGLShader&&) = default;
		OpenGLShader& operator=(OpenGLShader&&) = default;
		~OpenGLShader();
		
		void Shutdown() const;
		void Bind() const override;
		void Unbind() const override;

		uint32_t GetHandle() const;;

	private:
		void InitGLSL(std::string_view source);
		void InitGLSL(std::string_view VSSource, std::string_view FSSource, std::string_view GSSource, std::string_view TCSSource, std::string_view TESSource, std::string_view CSSource);
		void InitSPIRV(const std::vector<uint32_t>& source);
		
		static uint32_t CompileGLSL(const std::array<std::string_view, 6>& shaders);
		
		static bool CompileGLSLShader(ShaderType type, const char* source, uint32_t& handle);
		static bool CreateGLSLProgram(const std::array<std::string_view, 6>& shaders,
		                          uint32_t& vertex,
		                          uint32_t& fragment,
		                          uint32_t& geometry,
		                          uint32_t& tessControl,
		                          uint32_t& tessEval,
		                          uint32_t& compute,
		                          uint32_t& handle);
		static void LinkGLSLProgram(int32_t& linkResult, int32_t& validateResult, const uint32_t& handle);
		static void DeleteGLSLShaders(const std::array<std::string_view, 6>& shaders,
		                          const uint32_t& vertex,
		                          const uint32_t& fragment,
		                          const uint32_t& geometry,
		                          const uint32_t& tessControl,
		                          const uint32_t& tessEval,
		                          const uint32_t& compute,
								  const uint32_t& handle);

		static std::array<std::string, 6> ConvertSPIRVToGLSL(const std::array<std::vector<uint32_t>, 6>& SPIRVShaders);
		
		static GLenum ShaderTypeToOpenGL(ShaderType type);

		static bool IsTypeOpaque(GLenum type);

		void CheckForUniforms();

		static bool PreProcess(std::string_view source, std::array<std::string, 6>& shaders);

		uint32_t m_handle;
	};
}

#endif /*_TRAP_OPENGLSHADER_H_*/