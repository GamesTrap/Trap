#include "IconTests.h"

//Simple TRAP Logo
std::array<std::string, 16> IconTests::s_iconStrings
{
	 "................",
	 "................",
	 "..00000...000...",
	 "....0.....0..0..",
	 "....0.....000...",
	 "....0.....0.0...",
	 "....0.....0..0..",
	 "................",
	 "................",
	 "....0.....000...",
	"...0.0....0..0..",
	"..0...0...000...",
	"..00000...0.....",
	"..0...0...0.....",
	"................",
	"................"
};

//-------------------------------------------------------------------------------------------------------------------//

std::array<std::array<uint8_t, 4>, 5> IconTests::s_iconColors
{
	{
		{  0,   0,   0, 255}, //Black
		{255,   0,   0, 255}, //Red
		{  0, 255,   0, 255}, //Green
		{  0,   0, 255, 255}, //Blue
		{255, 255, 255, 255}  //White
	}
};

//-------------------------------------------------------------------------------------------------------------------//

int32_t IconTests::s_cursorIconColor = 0;

//-------------------------------------------------------------------------------------------------------------------//

IconTests::IconTests()
	: Layer("Icon")
{
}

//-------------------------------------------------------------------------------------------------------------------//

void IconTests::OnImGuiRender()
{
	ImGui::Begin("IconTests", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
	ImGui::Text("Press ESC to close");
	ImGui::Text("Press Space to cycle through Window Icons");
	ImGui::Text("Press X to reset Window Icon");
	ImGui::End();
}

//-------------------------------------------------------------------------------------------------------------------//

void IconTests::OnAttach()
{
	TRAP::Application::GetWindow()->SetTitle("Icon");

	SetIcon(TRAP::Application::GetWindow(), s_cursorIconColor);
}

//-------------------------------------------------------------------------------------------------------------------//

void IconTests::OnUpdate(const TRAP::Utils::TimeStep& deltaTime)
{
	//Render
	TRAP::Graphics::RenderCommand::SetClearColor();
	TRAP::Graphics::RenderCommand::Clear(TRAP::Graphics::RendererBufferType::Color);
}

//-------------------------------------------------------------------------------------------------------------------//

void IconTests::OnEvent(TRAP::Events::Event& event)
{
	TRAP::Events::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<TRAP::Events::KeyPressEvent>([this](TRAP::Events::KeyPressEvent& e) {return OnKeyPress(e); });
}

//-------------------------------------------------------------------------------------------------------------------//

void IconTests::SetIcon(const TRAP::Scope<TRAP::Window>& window, const int32_t iconColor)
{
	std::vector<uint8_t> pixels(16 * 16 * 4, 0);
	uint8_t* target = pixels.data();

	for(int32_t y = 0; y < 16; y++)
	{
		for(int32_t x = 0; x < 16; x++)
		{
			if (s_iconStrings[y][x] == '0')
				memcpy(target, s_iconColors[iconColor].data(), 4);
			else
				memset(target, 0, 4);

			target += 4;
		}
	}

	const TRAP::Scope<TRAP::Image> image = TRAP::Image::LoadFromMemory(16, 16, TRAP::Image::ColorFormat::RGBA, pixels);
	window->SetIcon(image);
}

//-------------------------------------------------------------------------------------------------------------------//

bool IconTests::OnKeyPress(TRAP::Events::KeyPressEvent& event)
{
	if (event.GetRepeatCount() > 0)
		return true;

	switch(event.GetKey())
	{
	case TRAP::Input::Key::Escape:
		TRAP::Application::Shutdown();
		break;

	case TRAP::Input::Key::Space:
		s_cursorIconColor = (s_cursorIconColor + 1) % 5;
		SetIcon(TRAP::Application::GetWindow(), s_cursorIconColor);
		break;

	case TRAP::Input::Key::X:
		TRAP::Application::GetWindow()->SetIcon();
		break;
		
	default:
		break;
	}
	
	return true;
}