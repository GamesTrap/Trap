#include "TRAPPCH.h"
#include "MouseEvent.h"

TRAP::Events::MouseMoveEvent::MouseMoveEvent(const float x, const float y, const std::string_view title)
	: m_mouseX(x), m_mouseY(y), m_title(title)
{
}

//-------------------------------------------------------------------------------------------------------------------//

float TRAP::Events::MouseMoveEvent::GetX() const
{
	return m_mouseX;
}

//-------------------------------------------------------------------------------------------------------------------//

float TRAP::Events::MouseMoveEvent::GetY() const
{
	return m_mouseY;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Math::Vec2 TRAP::Events::MouseMoveEvent::GetPosition() const
{
	return { m_mouseX, m_mouseY };
}

//-------------------------------------------------------------------------------------------------------------------//

std::string_view TRAP::Events::MouseMoveEvent::GetTitle() const
{
	return m_title;
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::Events::MouseMoveEvent::ToString() const
{
	std::stringstream ss;
	ss << "MouseMoveEvent: " << m_mouseX << ", " << m_mouseY;

	return ss.str();
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseMoveEvent::GetStaticType()
{
	return EventType::MouseMove;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseMoveEvent::GetEventType() const
{
	return GetStaticType();
}

//-------------------------------------------------------------------------------------------------------------------//

const char* TRAP::Events::MouseMoveEvent::GetName() const
{
	return "MouseMove";
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t TRAP::Events::MouseMoveEvent::GetCategoryFlags() const
{
	return static_cast<int32_t>(EventCategory::Mouse) | static_cast<int32_t>(EventCategory::Input);
}

//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::MouseScrollEvent::MouseScrollEvent(const float xOffset, const float yOffset, const std::string_view title)
	: m_xOffset(xOffset), m_yOffset(yOffset), m_title(title)
{
}

//-------------------------------------------------------------------------------------------------------------------//

float TRAP::Events::MouseScrollEvent::GetXOffset() const
{
	return m_xOffset;
}

//-------------------------------------------------------------------------------------------------------------------//

float TRAP::Events::MouseScrollEvent::GetYOffset() const
{
	return m_yOffset;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Math::Vec2 TRAP::Events::MouseScrollEvent::GetOffset() const
{
	return { m_xOffset, m_yOffset };
}

//-------------------------------------------------------------------------------------------------------------------//

std::string_view TRAP::Events::MouseScrollEvent::GetTitle() const
{
	return m_title;
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::Events::MouseScrollEvent::ToString() const
{
	std::stringstream ss;
	ss << "MouseScrollEvent: " << GetXOffset() << ", " << GetYOffset();

	return ss.str();
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseScrollEvent::GetStaticType()
{
	return EventType::MouseScroll;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseScrollEvent::GetEventType() const
{
	return GetStaticType();
}

//-------------------------------------------------------------------------------------------------------------------//

const char* TRAP::Events::MouseScrollEvent::GetName() const
{
	return "MouseScroll";
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t TRAP::Events::MouseScrollEvent::GetCategoryFlags() const
{
	return static_cast<int32_t>(EventCategory::Mouse) | static_cast<int32_t>(EventCategory::Input);
}

//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//

TRAP::Input::MouseButton TRAP::Events::MouseButtonEvent::GetMouseButton() const
{
	return m_button;
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t TRAP::Events::MouseButtonEvent::GetCategoryFlags() const
{
	return static_cast<int32_t>(EventCategory::Mouse) | static_cast<int32_t>(EventCategory::Input);
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::MouseButtonEvent::MouseButtonEvent(const Input::MouseButton button)
	: m_button(button)
{
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::Events::MouseButtonEvent::MouseButtonToString(const Input::MouseButton button)
{
	switch(button)
	{
	case Input::MouseButton::One:
		return "Left";

	case Input::MouseButton::Two:
		return "Right";

	case Input::MouseButton::Three:
		return "Middle";

	case Input::MouseButton::Four:
		return "4";
		
	case Input::MouseButton::Five:
		return "5";

	case Input::MouseButton::Six:
		return "6";

	case Input::MouseButton::Seven:
		return "7";

	case Input::MouseButton::Eight:
		return "8";
		
	default:
		return "";
	}
}

//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::MouseButtonPressEvent::MouseButtonPressEvent(const Input::MouseButton button, const std::string_view title)
	: MouseButtonEvent(button), m_title(title)
{
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::Events::MouseButtonPressEvent::ToString() const
{
	std::stringstream ss;
	ss << "MouseButtonPressEvent: " << MouseButtonToString(m_button) << "(" << static_cast<int32_t>(m_button) << ")";

	return ss.str();
}

//-------------------------------------------------------------------------------------------------------------------//

std::string_view TRAP::Events::MouseButtonPressEvent::GetTitle() const
{
	return m_title;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseButtonPressEvent::GetStaticType()
{
	return EventType::MouseButtonPress;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseButtonPressEvent::GetEventType() const
{
	return GetStaticType();
}

//-------------------------------------------------------------------------------------------------------------------//

const char* TRAP::Events::MouseButtonPressEvent::GetName() const
{
	return "MouseButtonPress";
}

//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::MouseButtonReleaseEvent::MouseButtonReleaseEvent(const Input::MouseButton button, const std::string_view title)
	: MouseButtonEvent(button), m_title(title)
{
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::Events::MouseButtonReleaseEvent::ToString() const
{
	std::stringstream ss;
	ss << "MouseButtonReleaseEvent: " << MouseButtonToString(m_button) << "(" << static_cast<int32_t>(m_button) << ")";

	return ss.str();
}

//-------------------------------------------------------------------------------------------------------------------//

std::string_view TRAP::Events::MouseButtonReleaseEvent::GetTitle() const
{
	return m_title;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseButtonReleaseEvent::GetStaticType()
{
	return EventType::MouseButtonRelease;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseButtonReleaseEvent::GetEventType() const
{
	return GetStaticType();
}

//-------------------------------------------------------------------------------------------------------------------//

const char* TRAP::Events::MouseButtonReleaseEvent::GetName() const
{
	return "MouseButtonRelease";
}

//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::MouseEnterEvent::MouseEnterEvent(const std::string_view title)
	: m_title(title)
{
}

//-------------------------------------------------------------------------------------------------------------------//

std::string_view TRAP::Events::MouseEnterEvent::GetTitle() const
{
	return m_title;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseEnterEvent::GetStaticType()
{
	return EventType::MouseEnter;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseEnterEvent::GetEventType() const
{
	return GetStaticType();
}

//-------------------------------------------------------------------------------------------------------------------//

const char* TRAP::Events::MouseEnterEvent::GetName() const
{
	return "MouseEnter";
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t TRAP::Events::MouseEnterEvent::GetCategoryFlags() const
{
	return static_cast<int32_t>(EventCategory::Mouse) | static_cast<int32_t>(EventCategory::Input);
}

//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::MouseLeaveEvent::MouseLeaveEvent(const std::string_view title)
	: m_title(title)
{
}

//-------------------------------------------------------------------------------------------------------------------//

std::string_view TRAP::Events::MouseLeaveEvent::GetTitle() const
{
	return m_title;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseLeaveEvent::GetStaticType()
{
	return EventType::MouseLeave;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::MouseLeaveEvent::GetEventType() const
{
	return GetStaticType();
}

//-------------------------------------------------------------------------------------------------------------------//

const char* TRAP::Events::MouseLeaveEvent::GetName() const
{
	return "MouseLeave";
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t TRAP::Events::MouseLeaveEvent::GetCategoryFlags() const
{
	return static_cast<int32_t>(EventCategory::Mouse) | static_cast<int32_t>(EventCategory::Input);
}