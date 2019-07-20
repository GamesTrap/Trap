#include "TRAPPCH.h"
#include "VulkanShader.h"

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Graphics::API::VulkanShader::s_glslangInitialized = false;

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::API::VulkanShader::VulkanShader(std::string name, std::string source)
	: m_name(std::move(name)),
	m_source(std::move(source)),
	m_VShaderModule(nullptr),
	m_FShaderModule(nullptr),
	m_GShaderModule(nullptr),
	m_TCShaderModule(nullptr),
	m_TEShaderModule(nullptr),
	m_CShaderModule(nullptr)/*,
	m_VSUserUniformBuffer(nullptr),
	m_FSUserUniformBuffer(nullptr)*/
{
	Init();
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::API::VulkanShader::VulkanShader(std::string name, std::string VSSource, std::string FSSource, std::string GSSource, std::string TCSSource, std::string TESSource, std::string CSSource)
	: m_name(std::move(name)),
	  m_VSSource(std::move(VSSource)),
	  m_FSSource(std::move(FSSource)),
	  m_GSSource(std::move(GSSource)),
	  m_TCSSource(std::move(TCSSource)),
	  m_TESSource(std::move(TESSource)),
	  m_CSSource(std::move(CSSource)),
	  m_VShaderModule(nullptr),
	  m_FShaderModule(nullptr),
	  m_GShaderModule(nullptr),
	  m_TCShaderModule(nullptr),
	  m_TEShaderModule(nullptr),
	  m_CShaderModule(nullptr)/*, 
	  m_VSUserUniformBuffer(nullptr),
      m_FSUserUniformBuffer(nullptr)*/
{
	Init();
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::API::VulkanShader::~VulkanShader()
{
	TP_DEBUG("[Shader][Vulkan] Destroying Shader: \"", m_name, "\"");
	Shutdown();
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::Init()
{
	std::array<std::string*, 6> shaders{ &m_VSSource, &m_FSSource, &m_GSSource, &m_TCSSource, &m_TESSource, &m_CSSource };
	if (!m_source.empty())
		PreProcessGLSL(m_source, shaders);
	VulkanShaderErrorInfo error;
	TP_DEBUG("[Shader][Vulkan] Compiling: \"", m_name, "\"");
	Compile(shaders, error);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::Shutdown() const
{
	if (m_VShaderModule)
		vkDestroyShaderModule(VulkanRenderer::Get()->GetDevice(), m_VShaderModule, nullptr);
	if (m_FShaderModule)
		vkDestroyShaderModule(VulkanRenderer::Get()->GetDevice(), m_FShaderModule, nullptr);
	if (m_GShaderModule)
		vkDestroyShaderModule(VulkanRenderer::Get()->GetDevice(), m_GShaderModule, nullptr);
	if (m_TCShaderModule)
		vkDestroyShaderModule(VulkanRenderer::Get()->GetDevice(), m_TCShaderModule, nullptr);
	if (m_TEShaderModule)
		vkDestroyShaderModule(VulkanRenderer::Get()->GetDevice(), m_TEShaderModule, nullptr);
	if (m_CShaderModule)
		vkDestroyShaderModule(VulkanRenderer::Get()->GetDevice(), m_CShaderModule, nullptr);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::Compile(std::array<std::string*, 6> & shaders, VulkanShaderErrorInfo& info)
{
	if (!s_glslangInitialized)
	{
		glslang::InitializeProcess();
		s_glslangInitialized = true;
	}

	glslang::TProgram program;
	std::unique_ptr<glslang::TShader> VShader = nullptr;
	std::unique_ptr<glslang::TShader> FShader = nullptr;
	std::unique_ptr<glslang::TShader> GShader = nullptr;
	std::unique_ptr<glslang::TShader> TCShader = nullptr;
	std::unique_ptr<glslang::TShader> TEShader = nullptr;
	std::unique_ptr<glslang::TShader> CShader = nullptr;

	if (!shaders[0]->empty())
	{
		const char* VSSource = shaders[0]->c_str();
		TP_DEBUG("[Shader][Vulkan][GLSL] Pre-Processing Vertex Shader");
		std::string preProcessedSource;
		VShader = PreProcess(VSSource, 0, preProcessedSource);
		if (preProcessedSource.empty() || !VShader)
			return;
		const char* preProcessedCStr = preProcessedSource.c_str();
		VShader->setStrings(&preProcessedCStr, 1);

		TP_DEBUG("[Shader][Vulkan][GLSL] Parsing Vertex Shader");
		if (!Parse(VShader.get()))
			return;
	}

	if (!shaders[1]->empty())
	{
		const char* FSSource = shaders[1]->c_str();
		TP_DEBUG("[Shader][Vulkan][GLSL] Pre-Processing Fragment Shader");
		std::string preProcessedSource;
		FShader = PreProcess(FSSource, 1, preProcessedSource);
		if (preProcessedSource.empty())
			return;
		const char* preProcessedCStr = preProcessedSource.c_str();
		FShader->setStrings(&preProcessedCStr, 1);

		TP_DEBUG("[Shader][Vulkan][GLSL] Parsing Fragment Shader");
		if (!Parse(FShader.get()))
			return;
	}

	if (!shaders[2]->empty())
	{
		const char* GSSource = shaders[2]->c_str();
		TP_DEBUG("[Shader][Vulkan][GLSL] Pre-Processing Geometry Shader");
		std::string preProcessedSource;
		GShader = PreProcess(GSSource, 2, preProcessedSource);
		if (preProcessedSource.empty())
			return;
		const char* preProcessedCStr = preProcessedSource.c_str();
		GShader->setStrings(&preProcessedCStr, 1);

		TP_DEBUG("[Shader][Vulkan][GLSL] Parsing Geometry Shader");
		if (!Parse(GShader.get()))
			return;
	}

	if (!shaders[3]->empty())
	{
		const char* TCSSource = shaders[3]->c_str();
		TP_DEBUG("[Shader][Vulkan][GLSL] Pre-Processing Tessellation Control Shader");
		std::string preProcessedSource;
		TCShader = PreProcess(TCSSource, 3, preProcessedSource);
		if (preProcessedSource.empty())
			return;
		const char* preProcessedCStr = preProcessedSource.c_str();
		TCShader->setStrings(&preProcessedCStr, 1);

		TP_DEBUG("[Shader][Vulkan][GLSL] Parsing Tessellation Control Shader");
		if (!Parse(TCShader.get()))
			return;
	}

	if (!shaders[4]->empty())
	{
		const char* TESSource = shaders[4]->c_str();
		TP_DEBUG("[Shader][Vulkan][GLSL] Pre-Processing Tessellation Evaluation Shader");
		std::string preProcessedSource;
		TEShader = PreProcess(TESSource, 4, preProcessedSource);
		if (preProcessedSource.empty())
			return;
		const char* preProcessedCStr = preProcessedSource.c_str();
		TEShader->setStrings(&preProcessedCStr, 1);

		TP_DEBUG("[Shader][Vulkan][GLSL] Parsing Tessellation Evaluation Shader");
		if (!Parse(TEShader.get()))
			return;
	}

	if (!shaders[5]->empty())
	{
		const char* CSSource = shaders[5]->c_str();
		TP_DEBUG("[Shader][Vulkan][GLSL] Pre-Processing Compute Shader");
		std::string preProcessedSource;
		CShader = PreProcess(CSSource, 5, preProcessedSource);
		if (preProcessedSource.empty())
			return;
		const char* preProcessedCStr = preProcessedSource.c_str();
		CShader->setStrings(&preProcessedCStr, 1);

		TP_DEBUG("[Shader][Vulkan][GLSL] Parsing Compute Shader");
		if (!Parse(CShader.get()))
			return;
	}

	TP_DEBUG("[Shader][Vulkan][GLSL] Linking Shaders");
	if (!Link(VShader.get(), FShader.get(), GShader.get(), TCShader.get(), TEShader.get(), CShader.get(), program))
		return;

	TP_DEBUG("[Shader][Vulkan][SPIRV] Converting Shaders to SPIRV");
	std::vector<std::vector<unsigned int>> SPIRV = ConvertToSPIRV(VShader.get(), FShader.get(), GShader.get(), TCShader.get(), TEShader.get(), CShader.get(), program);

	if (!SPIRV[0].empty())
	{
		if (!CreateShaderModule(m_VShaderModule, SPIRV[0]))
			return;

		VkPipelineShaderStageCreateInfo shaderStageInfo
		{
			VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			nullptr,
			0,
			VK_SHADER_STAGE_VERTEX_BIT,
			m_VShaderModule,
			"main",
			nullptr
		};
		m_shaderStages.push_back(shaderStageInfo);
	}
	if(!SPIRV[1].empty())
	{
		if (!CreateShaderModule(m_FShaderModule, SPIRV[1]))
			return;

		VkPipelineShaderStageCreateInfo shaderStageInfo
		{
			VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			nullptr,
			0,
			VK_SHADER_STAGE_FRAGMENT_BIT,
			m_FShaderModule,
			"main",
			nullptr
		};
		m_shaderStages.push_back(shaderStageInfo);
	}
	if(!SPIRV[2].empty())
	{
		if (!CreateShaderModule(m_GShaderModule, SPIRV[2]))
			return;

		VkPipelineShaderStageCreateInfo shaderStageInfo
		{
			VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			nullptr,
			0,
			VK_SHADER_STAGE_GEOMETRY_BIT,
			m_GShaderModule,
			"main",
			nullptr
		};
		m_shaderStages.push_back(shaderStageInfo);
	}
	if(!SPIRV[3].empty())
	{
		if (!CreateShaderModule(m_TCShaderModule, SPIRV[3]))
			return;

		VkPipelineShaderStageCreateInfo shaderStageInfo
		{
			VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			nullptr,
			0,
			VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
			m_TCShaderModule,
			"main",
			nullptr
		};
		m_shaderStages.push_back(shaderStageInfo);
	}
	if(!SPIRV[4].empty())
	{
		if (!CreateShaderModule(m_TEShaderModule, SPIRV[4]))
			return;

		VkPipelineShaderStageCreateInfo shaderStageInfo
		{
			VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			nullptr,
			0,
			VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
			m_TEShaderModule,
			"main",
			nullptr
		};
		m_shaderStages.push_back(shaderStageInfo);
	}
	if (!SPIRV[5].empty())
	{
		if (!CreateShaderModule(m_CShaderModule, SPIRV[5]))
			return;

		VkPipelineShaderStageCreateInfo shaderStageInfo
		{
			VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			nullptr,
			0,
			VK_SHADER_STAGE_COMPUTE_BIT,
			m_CShaderModule,
			"main",
			nullptr
		};
		m_shaderStages.push_back(shaderStageInfo);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

std::unique_ptr<glslang::TShader> TRAP::Graphics::API::VulkanShader::PreProcess(const char* source, const unsigned int shaderType, std::string& preProcessedSource)
{
	std::unique_ptr<glslang::TShader> shader;
	if (shaderType == 0)
	{
		shader = std::make_unique<glslang::TShader>(EShLangVertex);
		shader->setStrings(&source, 1);
		shader->setEnvInput(glslang::EShSourceGlsl, EShLangVertex, glslang::EShClientVulkan, 460);
	}
	else if (shaderType == 1)
	{
		shader = std::make_unique<glslang::TShader>(EShLangFragment);
		shader->setStrings(&source, 1);
		shader->setEnvInput(glslang::EShSourceGlsl, EShLangFragment, glslang::EShClientVulkan, 460);
	}
	else if (shaderType == 2)
	{
		shader = std::make_unique<glslang::TShader>(EShLangGeometry);
		shader->setStrings(&source, 1);
		shader->setEnvInput(glslang::EShSourceGlsl, EShLangGeometry, glslang::EShClientVulkan, 460);
	}
	else if (shaderType == 3)
	{
		shader = std::make_unique<glslang::TShader>(EShLangTessControl);
		shader->setStrings(&source, 1);
		shader->setEnvInput(glslang::EShSourceGlsl, EShLangTessControl, glslang::EShClientVulkan, 460);
	}
	else if (shaderType == 4)
	{
		shader = std::make_unique<glslang::TShader>(EShLangTessEvaluation);
		shader->setStrings(&source, 1);
		shader->setEnvInput(glslang::EShSourceGlsl, EShLangTessEvaluation, glslang::EShClientVulkan, 460);
	}
	else if (shaderType == 5)
	{
		shader = std::make_unique<glslang::TShader>(EShLangCompute);
		shader->setStrings(&source, 1);
		shader->setEnvInput(glslang::EShSourceGlsl, EShLangCompute, glslang::EShClientVulkan, 460);
	}

	shader->setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_1);
	shader->setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_3); //TODO Update to SPIRV 1.4
	DirStackFileIncluder includer;
	if (!shader->preprocess(&glslang::DefaultTBuiltInResource,
	                        460,
	                        ECoreProfile,
	                        true,
	                        true,
	                        static_cast<EShMessages>(EShMsgDefault | EShMsgSpvRules | EShMsgVulkanRules),
	                        &preProcessedSource,
	                        includer))
	{
		TP_ERROR("[Shader}[Vulkan] GLSL Preprocessing failed!");
		TP_ERROR("[Shader][Vulkan] ", shader->getInfoLog());
		TP_ERROR("[Shader][Vulkan] ", shader->getInfoDebugLog());

		return nullptr;
	}

	return shader;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Graphics::API::VulkanShader::Parse(glslang::TShader* shader)
{
	if (!shader->parse(&glslang::DefaultTBuiltInResource, 460, true, static_cast<EShMessages>(EShMsgDefault | EShMsgSpvRules | EShMsgVulkanRules)))
	{
		TP_ERROR("[Shader][Vulkan] Parsing failed: ");
		TP_ERROR("[Shader][Vulkan] ", shader->getInfoLog());
		TP_ERROR("[Shader][Vulkan] ", shader->getInfoDebugLog());

		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Graphics::API::VulkanShader::Link(glslang::TShader* VShader,
                                             glslang::TShader* FShader,
                                             glslang::TShader* GShader,
                                             glslang::TShader* TCShader,
                                             glslang::TShader* TEShader,
                                             glslang::TShader* CShader,
                                             glslang::TProgram& program)
{
	if(VShader)
		program.addShader(VShader);
	if (FShader)
		program.addShader(FShader);
	if (GShader)
		program.addShader(GShader);
	if (TCShader)
		program.addShader(TCShader);
	if (TEShader)
		program.addShader(TEShader);
	if (CShader)
		program.addShader(CShader);

	if (!program.link(static_cast<EShMessages>(EShMsgDefault | EShMsgSpvRules | EShMsgVulkanRules)))
	{
		TP_ERROR("[Shader][Vulkan] Linking failed: ");
		TP_ERROR("[Shader][Context] ", program.getInfoLog());
		TP_ERROR("[Shader][Vulkan] ", program.getInfoDebugLog());

		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<std::vector<unsigned>> TRAP::Graphics::API::VulkanShader::ConvertToSPIRV(
										glslang::TShader* VShader,
										glslang::TShader* FShader,
										glslang::TShader* GShader,
										glslang::TShader* TCShader,
										glslang::TShader* TEShader,
										glslang::TShader* CShader,
										glslang::TProgram& program)
{
	std::vector<std::vector<unsigned int>> SPIRV(6);

	if(VShader)
	{
		spv::SpvBuildLogger logger;
		glslang::SpvOptions spvOptions;
		GlslangToSpv(*program.getIntermediate(EShLangVertex), SPIRV[0], &logger, &spvOptions);
		if (logger.getAllMessages().length() > 0)
			TP_ERROR("[Shader][Vulkan][SPIRV] Vertex Shader: ", logger.getAllMessages());
	}

	if (FShader)
	{
		spv::SpvBuildLogger logger;
		glslang::SpvOptions spvOptions;
		GlslangToSpv(*program.getIntermediate(EShLangFragment), SPIRV[1], &logger, &spvOptions);
		if (logger.getAllMessages().length() > 0)
			TP_ERROR("[Shader][Vulkan][SPIRV] Fragment Shader: ", logger.getAllMessages());
	}

	if (GShader)
	{
		spv::SpvBuildLogger logger;
		glslang::SpvOptions spvOptions;
		GlslangToSpv(*program.getIntermediate(EShLangGeometry), SPIRV[2], &logger, &spvOptions);
		if (logger.getAllMessages().length() > 0)
			TP_ERROR("[Shader][Vulkan][SPIRV] Geometry Shader: ", logger.getAllMessages());
	}

	if (TCShader)
	{
		spv::SpvBuildLogger logger;
		glslang::SpvOptions spvOptions;
		GlslangToSpv(*program.getIntermediate(EShLangTessControl), SPIRV[3], &logger, &spvOptions);
		if (logger.getAllMessages().length() > 0)
			TP_ERROR("[Shader][Vulkan][SPIRV] Tessellation Control Shader: ", logger.getAllMessages());
	}

	if (TEShader)
	{
		spv::SpvBuildLogger logger;
		glslang::SpvOptions spvOptions;
		GlslangToSpv(*program.getIntermediate(EShLangTessEvaluation), SPIRV[4], &logger, &spvOptions);
		if (logger.getAllMessages().length() > 0)
			TP_ERROR("[Shader][Vulkan][SPIRV] Tessellation Evaluation Shader: ", logger.getAllMessages());
	}

	if (CShader)
	{
		spv::SpvBuildLogger logger;
		glslang::SpvOptions spvOptions;
		GlslangToSpv(*program.getIntermediate(EShLangCompute), SPIRV[5], &logger, &spvOptions);
		if (logger.getAllMessages().length() > 0)
			TP_ERROR("[Shader][Vulkan][SPIRV] Compute Shader: ", logger.getAllMessages());
	}

	return SPIRV;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Graphics::API::VulkanShader::CreateShaderModule(VkShaderModule& shaderModule, std::vector<unsigned int>& SPIRVCode)
{
	VkShaderModuleCreateInfo shaderModuleCreateInfo
	{
		VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		nullptr,
		0,
		SPIRVCode.size() * sizeof(unsigned int),
		SPIRVCode.data()
	};

	VkResult success;
	VkCall(success = vkCreateShaderModule(Graphics::API::VulkanRenderer::Get()->GetDevice(), &shaderModuleCreateInfo, nullptr, &shaderModule));
	return success == VK_SUCCESS;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::Bind() const
{
	if (s_CurrentlyBound != this)
	{
		if(!m_shaderStages.empty())
			s_CurrentlyBound = this;			
		else
		{
			ShaderManager::Get("Passthrough")->Bind();
			s_CurrentlyBound = ShaderManager::Get("Passthrough");
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::Unbind() const
{
	s_CurrentlyBound = nullptr;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::SetVSUniformBuffer(uint8_t* data, unsigned int size)
{
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::SetFSUniformBuffer(uint8_t* data, unsigned int size)
{
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::SetGSUniformBuffer(uint8_t* data, unsigned int size)
{
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::SetTCSUniformBuffer(uint8_t* data, unsigned int size)
{
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::SetTESUniformBuffer(uint8_t* data, unsigned int size)
{
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::SetCSUniformBuffer(uint8_t* data, unsigned int size)
{
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanShader::PreProcessGLSL(const std::string& source, std::array<std::string*, 6>& shaders)
{
	ShaderType type = ShaderType::UNKNOWN;

	std::vector<std::string> lines = Utils::String::GetLines(source);
	//Get Shader Type
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		if (Utils::String::StartsWith(lines[i], "#shader"))
		{
			if (Utils::String::FindToken(lines[i], "vertex"))
				type = ShaderType::VERTEX;
			else if (Utils::String::FindToken(lines[i], "fragment"))
				type = ShaderType::FRAGMENT;
			else if (Utils::String::FindToken(lines[i], "geometry"))
				type = ShaderType::GEOMETRY;
			else if (Utils::String::FindToken(lines[i], "tessellationcontrol"))
				type = ShaderType::TESSELLATIONCONTROL;
			else if (Utils::String::FindToken(lines[i], "tessellationevaluation"))
				type = ShaderType::TESSELLATIONEVALUATION;
			else if (Utils::String::FindToken(lines[i], "compute"))
				type = ShaderType::COMPUTE;

			//Add version tag if doesnt exist
			if (!Utils::String::StartsWith(lines[i + 1], "#version ") && type != ShaderType::UNKNOWN)
				shaders[static_cast<int32_t>(type) - 1]->append("#version 460 core\n");
		}
		else if (type != ShaderType::UNKNOWN)
		{
			//Ignore comments
			if (!Utils::String::StartsWith(lines[i], "//"))
			{
				shaders[static_cast<int32_t>(type) - 1]->append(lines[i]);
				shaders[static_cast<int32_t>(type) - 1]->append("\n");
			}
		}
	}
}