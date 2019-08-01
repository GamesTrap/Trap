#ifndef _TRAP_SHADER_H_
#define _TRAP_SHADER_H_

#include "ShaderUniform.h"
#include "ShaderResource.h"

namespace TRAP::Graphics
{
	enum class ShaderType
	{
		Unknown = 0,
		Vertex,
		Fragment,
		Geometry,
		Tessellation_Control,
		Tessellation_Evaluation,
		Compute
	};

	class Shader
	{
	public:
		Shader() = default;
		Shader(const Shader&) = default;
		Shader& operator=(const Shader&) = default;
		Shader(Shader&&) = default;
		Shader& operator=(Shader&&) = default;
		virtual ~Shader() = default;

		static const Shader* s_CurrentlyBound;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVSUniformBuffer(uint8_t* data, unsigned int size) = 0;
		virtual void SetFSUniformBuffer(uint8_t* data, unsigned int size) = 0;
		virtual void SetGSUniformBuffer(uint8_t* data, unsigned int size) = 0;
		virtual void SetTCSUniformBuffer(uint8_t* data, unsigned int size) = 0;
		virtual void SetTESUniformBuffer(uint8_t* data, unsigned int size) = 0;
		virtual void SetCSUniformBuffer(uint8_t* data, unsigned int size) = 0;

		virtual const API::ShaderUniformBufferList& GetVSUniforms() const = 0;
		virtual const API::ShaderUniformBufferList& GetFSUniforms() const = 0;
		virtual const API::ShaderUniformBufferList& GetGSUniforms() const = 0;
		virtual const API::ShaderUniformBufferList& GetTCSUniforms() const = 0;
		virtual const API::ShaderUniformBufferList& GetTESUniforms() const = 0;
		virtual const API::ShaderUniformBufferList& GetCSUniforms() const = 0;
		virtual const API::ShaderUniformBufferDeclaration* GetVSUniformBuffer() const = 0;
		virtual const API::ShaderUniformBufferDeclaration* GetFSUniformBuffer() const = 0;
		virtual const API::ShaderUniformBufferDeclaration* GetGSUniformBuffer() const = 0;
		virtual const API::ShaderUniformBufferDeclaration* GetTCSUniformBuffer() const = 0;
		virtual const API::ShaderUniformBufferDeclaration* GetTESUniformBuffer() const = 0;
		virtual const API::ShaderUniformBufferDeclaration* GetCSUniformBuffer() const = 0;

		virtual const API::ShaderResourceList& GetResource() const = 0;

		virtual const std::string& GetName() const = 0;

		virtual const std::string& GetFilePath() const = 0;

		virtual const std::string& GetVSSource() const = 0;
		virtual const std::string& GetFSSource() const = 0;
		virtual const std::string& GetGSSource() const = 0;
		virtual const std::string& GetTCSSource() const = 0;
		virtual const std::string& GetTESSource() const = 0;
		virtual const std::string& GetCSSource() const = 0;

		static std::unique_ptr<Shader> CreateFromFile(const std::string& name, const std::string& filePath, Shader* address = nullptr);
		static std::unique_ptr<Shader> CreateFromSource(const std::string& name, const std::string& VSSource, const std::string& FSSource, const std::string& GSSource, const std::string& TCSSource, const std::string& TESSource, const std::string& CSSource);;
	};
}

#endif /*_TRAP_SHADER_H_*/