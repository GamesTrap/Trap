#include "TRAPPCH.h"
#include "ControllerEvent.h"

TRAP::Input::Controller TRAP::Events::ControllerEvent::GetController() const
{
	return m_controller;
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t TRAP::Events::ControllerEvent::GetCategoryFlags() const
{
	return static_cast<int32_t>(EventCategory::Controller) | static_cast<int32_t>(EventCategory::Input);
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::ControllerEvent::ControllerEvent(const Input::Controller controller)
	: m_controller(controller)
{	
}

//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::ControllerConnectEvent::ControllerConnectEvent(const Input::Controller controller)
	: ControllerEvent(controller)
{	
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::Events::ControllerConnectEvent::ToString() const
{
	std::stringstream ss;
	ss << "ControllerConnectEvent: " << (static_cast<uint32_t>(m_controller) + 1);

	return ss.str();
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::ControllerConnectEvent::GetStaticType()
{
	return EventType::ControllerConnect;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::ControllerConnectEvent::GetEventType() const
{
	return GetStaticType();
}

//-------------------------------------------------------------------------------------------------------------------//

const char* TRAP::Events::ControllerConnectEvent::GetName() const
{
	return "ControllerConnect";
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::ControllerDisconnectEvent::ControllerDisconnectEvent(const Input::Controller controller)
	: ControllerEvent(controller)
{
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::Events::ControllerDisconnectEvent::ToString() const
{
	std::stringstream ss;
	ss << "ControllerDisconnectEvent: " << (static_cast<uint32_t>(m_controller) + 1);

	return ss.str();
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::ControllerDisconnectEvent::GetStaticType()
{
	return EventType::ControlledDisconnect;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Events::EventType TRAP::Events::ControllerDisconnectEvent::GetEventType() const
{
	return GetStaticType();
}

//-------------------------------------------------------------------------------------------------------------------//

const char* TRAP::Events::ControllerDisconnectEvent::GetName() const
{
	return "ControllerDisconnect";
}