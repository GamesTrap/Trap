#pragma once

#include <TRAP.h>

class SandboxLayer : public TRAP::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox"),
		  m_usePassthrough(false),
		  m_wireFrame(false),
		  m_showTriangle(true),
		  m_vertexArray(nullptr),
		  m_camera(-1.6f, 1.6f, -0.9f, 0.9f, -1.0f, 1.0f),
		  m_cameraPosition(0.0f),
		  m_cameraRotation(0.0f),
		  m_uniformBuffer(nullptr)
	{
	}

	//-------------------------------------------------------------------------------------------------------------------//

	void OnImGuiRender() override
	{
	}

	//-------------------------------------------------------------------------------------------------------------------//

	void OnAttach() override
	{
		TRAP::VFS::Get()->MountShaders("Assets/Shaders");
		TRAP::Graphics::ShaderManager::Add(TRAP::Graphics::API::Shader::CreateFromFile("Color", "/Shaders/Color.shader"));

		///////////////
		// Rectangle //
		///////////////
		m_vertexArray = TRAP::Graphics::VertexArray::Create();

		//XYZ RGBA
		/*std::array<float, 7 * 3> triangleVertices
		{
			-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f, 1.0f
		};*/
		std::array<float, 7 * 4> rectangleVertices{
			-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f, 1.0f};
		std::unique_ptr<TRAP::Graphics::VertexBuffer> vertexBuffer = TRAP::Graphics::VertexBuffer::Create(rectangleVertices.data(), static_cast<uint32_t>(rectangleVertices.size()), TRAP::Graphics::BufferUsage::STATIC);
		const TRAP::Graphics::BufferLayout triangleLayout =
			{
				{TRAP::Graphics::ShaderDataType::Float3, "Position"},
				{TRAP::Graphics::ShaderDataType::Float4, "Color"}
			};
		vertexBuffer->SetLayout(triangleLayout);
		m_vertexArray->AddVertexBuffer(vertexBuffer);

		/*std::array<uint32_t, 3> triangleIndices
		{
			0, 1, 2
		};*/
		std::array<uint32_t, 6> rectangleIndices{
			0, 1, 2, 2, 3, 0};
		std::unique_ptr<TRAP::Graphics::IndexBuffer> indexBuffer = TRAP::Graphics::IndexBuffer::Create(rectangleIndices.data(), static_cast<uint32_t>(rectangleIndices.size()), TRAP::Graphics::BufferUsage::STATIC);
		m_vertexArray->SetIndexBuffer(indexBuffer);

		//Matrices needs to be transposed because of the row-major order
		UBOData uboData{TRAP::Maths::Mat4::Transpose(m_camera.GetProjectionMatrix()), TRAP::Maths::Mat4::Transpose(m_camera.GetViewMatrix())};
		m_uniformBuffer = TRAP::Graphics::UniformBuffer::Create("matBuf", &uboData, sizeof(UBOData), TRAP::Graphics::BufferUsage::DYNAMIC);
	}

	//-------------------------------------------------------------------------------------------------------------------//

	void OnDetach() override
	{
		m_uniformBuffer->Unbind();
		m_uniformBuffer.reset();

		m_vertexArray->Unbind();
		m_vertexArray.reset();
	}

	//-------------------------------------------------------------------------------------------------------------------//

	void OnUpdate(const TRAP::Utils::TimeStep deltaTime) override
	{
		//Update camera every frame
		TRAP::Maths::Mat4 transposedViewMatrix = TRAP::Maths::Mat4::Transpose(m_camera.GetViewMatrix());
		m_uniformBuffer->UpdateSubData(&transposedViewMatrix, sizeof(TRAP::Maths::Mat4), sizeof(TRAP::Maths::Mat4));

		TRAP::Graphics::RenderCommand::SetClearColor();
		TRAP::Graphics::RenderCommand::Clear(TRAP::Graphics::RendererBufferType::RENDERER_BUFFER_COLOR | TRAP::Graphics::RendererBufferType::RENDERER_BUFFER_DEPTH);
		TRAP::Graphics::RenderCommand::SetCull(false); //Disables Culling

		m_camera.SetPosition(m_cameraPosition);
		m_camera.SetRotation(m_cameraRotation);

		TRAP::Graphics::Renderer::BeginScene();
		{
			if (m_showTriangle)
			{
				if (m_usePassthrough)
					TRAP::Graphics::ShaderManager::Get("Passthrough")->Bind();
				else
					TRAP::Graphics::ShaderManager::Get("Color")->Bind();

				TRAP::Graphics::Renderer::Submit(m_vertexArray);
			}
		}
		TRAP::Graphics::Renderer::EndScene();

		//FPS & FrameTime
		if (m_titleTimer.Elapsed() >= 0.05f) //Update Title
		{
			TRAP::Application::Get().GetWindow()->SetTitle("Sandbox - FPS: " + std::to_string(TRAP::Application::Get().GetFPS()) + " FrameTime: " + std::to_string(TRAP::Application::Get().GetFrameTime()));
			m_titleTimer.Reset();
		}
		if (m_fpsTimer.Elapsed() >= 5.0f) //Output Every 5 Seconds
		{
			TP_INFO("[Sandbox] FPS: ", TRAP::Application::Get().GetFPS());
			TP_INFO("[Sandbox] FrameTime: ", TRAP::Application::Get().GetFrameTime(), "ms");
			m_fpsTimer.Reset();
		}

		///////////////////
		//Camera Controls//
		///////////////////
		if (TRAP::Input::IsKeyPressed(TP_KEY_A))
			m_cameraPosition.x -= m_cameraMovementSpeed * deltaTime;
		if (TRAP::Input::IsKeyPressed(TP_KEY_D))
			m_cameraPosition.x += m_cameraMovementSpeed * deltaTime;
		if (TRAP::Input::IsKeyPressed(TP_KEY_W))
			m_cameraPosition.y += m_cameraMovementSpeed * deltaTime;
		if (TRAP::Input::IsKeyPressed(TP_KEY_S))
			m_cameraPosition.y -= m_cameraMovementSpeed * deltaTime;

		if (TRAP::Input::IsKeyPressed(TP_KEY_KP_4))
			m_cameraRotation.z += m_cameraRotationSpeed * deltaTime;
		if (TRAP::Input::IsKeyPressed(TP_KEY_KP_6))
			m_cameraRotation.z -= m_cameraRotationSpeed * deltaTime;
		if (TRAP::Input::IsKeyPressed(TP_KEY_KP_8))
			m_cameraRotation.x += m_cameraRotationSpeed * deltaTime;
		if (TRAP::Input::IsKeyPressed(TP_KEY_KP_2))
			m_cameraRotation.x -= m_cameraRotationSpeed * deltaTime;
		if (TRAP::Input::IsKeyPressed(TP_KEY_KP_7))
			m_cameraRotation.y += m_cameraRotationSpeed * deltaTime;
		if (TRAP::Input::IsKeyPressed(TP_KEY_KP_9))
			m_cameraRotation.y -= m_cameraRotationSpeed * deltaTime;
	}

	//-------------------------------------------------------------------------------------------------------------------//

	bool OnKeyPressed(TRAP::KeyPressedEvent &event)
	{
		if (event.GetKeyCode() == TP_KEY_ESCAPE)
			TRAP::Application::Get().Shutdown();

		if (event.GetKeyCode() == TP_KEY_F1 && event.GetRepeatCount() < 1) //Switch to D3D12
			TRAP::Graphics::API::Context::SwitchRenderAPI(TRAP::Graphics::API::RenderAPI::D3D12);
		if (event.GetKeyCode() == TP_KEY_F2 && event.GetRepeatCount() < 1) //Switch to Vulkan
			TRAP::Graphics::API::Context::SwitchRenderAPI(TRAP::Graphics::API::RenderAPI::VULKAN);
		if (event.GetKeyCode() == TP_KEY_F3 && event.GetRepeatCount() < 1) //Switch to OpenGL
			TRAP::Graphics::API::Context::SwitchRenderAPI(TRAP::Graphics::API::RenderAPI::OPENGL);

		if (event.GetKeyCode() == TP_KEY_F4 && event.GetRepeatCount() < 1) //Use Default/Passthrough Shader
			m_usePassthrough = !m_usePassthrough;

		if (event.GetKeyCode() == TP_KEY_F5 && event.GetRepeatCount() < 1) //Make Window windowed
			TRAP::Application::Get().GetWindow()->SetWindowMode(TRAP::DisplayMode::WINDOWED);
		if (event.GetKeyCode() == TP_KEY_F6 && event.GetRepeatCount() < 1) //Make Window Borderless Fullscreen
			TRAP::Application::Get().GetWindow()->SetWindowMode(TRAP::DisplayMode::BORDERLESS);
		if (event.GetKeyCode() == TP_KEY_F7 && event.GetRepeatCount() < 1) //Make Window Exclusive Fullscreen
			TRAP::Application::Get().GetWindow()->SetWindowMode(TRAP::DisplayMode::FULLSCREEN);

		if (event.GetKeyCode() == TP_KEY_F9 && event.GetRepeatCount() < 1) //Enable/Disable Triangle
			m_showTriangle = !m_showTriangle;
		if (event.GetKeyCode() == TP_KEY_F10 && event.GetRepeatCount() < 1) //Enable/Disable WireFrame Mode
		{
			m_wireFrame = !m_wireFrame;
			TRAP::Graphics::RenderCommand::SetWireFrame(m_wireFrame);
		}

		if (event.GetKeyCode() == TP_KEY_F11 && event.GetRepeatCount() < 1)
			TRAP::Utils::MsgBox::Show("Testing MsgBox System", "Test MsgBox");

		return true;
	}

	//-------------------------------------------------------------------------------------------------------------------//

	void OnEvent(TRAP::Event &event) override
	{
		TRAP::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<TRAP::KeyPressedEvent>(TP_BIND_EVENT_FN(SandboxLayer::OnKeyPressed));

		dispatcher.Dispatch<TRAP::WindowResizeEvent>(TP_BIND_EVENT_FN(SandboxLayer::OnResize));
	}

	//-------------------------------------------------------------------------------------------------------------------//

	bool OnResize(TRAP::WindowResizeEvent &event) const
	{
		TRAP::Graphics::RenderCommand::SetViewport(0, 0, event.GetWidth(), event.GetHeight());

		return true;
	}

private:
	TRAP::Utils::Timer m_fpsTimer;
	TRAP::Utils::Timer m_titleTimer;
	bool m_usePassthrough;
	bool m_wireFrame;
	bool m_showTriangle;

	std::unique_ptr<TRAP::Graphics::VertexArray> m_vertexArray;

	TRAP::Graphics::OrthographicCamera m_camera;
	TRAP::Maths::Vec3 m_cameraPosition;
	TRAP::Maths::Vec3 m_cameraRotation;
	float m_cameraMovementSpeed = 5.0f;
	float m_cameraRotationSpeed = 180.0f;

	std::unique_ptr<TRAP::Graphics::UniformBuffer> m_uniformBuffer;
	struct UBOData
	{
		TRAP::Maths::Mat4 ProjectionMatrix;
		TRAP::Maths::Mat4 ViewMatrix;
	};
};