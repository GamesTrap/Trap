#ifndef _TRAP_ORTHOGRAPHICCAMERACONTROLLER_H_
#define _TRAP_ORTHOGRAPHICCAMERACONTROLLER_H_

#include "OrthographicCamera.h"
#include "Utils/TimeStep.h"

#include "Event/ApplicationEvent.h"
#include "Event/MouseEvent.h"
#include "Application.h"

namespace TRAP::Graphics
{
	class OrthographicCameraController
	{
	public:
		explicit OrthographicCameraController(float aspectRatio, bool useController = false, Input::Controller controller = Input::Controller::One, bool rotation = false, const std::unique_ptr<Window>& window = Application::GetWindow());

		void OnUpdate(Utils::TimeStep deltaTime);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera();
		const OrthographicCamera& GetCamera() const;

		float GetTranslationSpeed() const;
		void SetTranslationSpeed(float translationSpeed);
		
		float GetRotationSpeed() const;
		void SetRotationSpeed(float rotationSpeed);
		
		float GetZoomLevel() const;
		void SetZoomLevel(float zoomLevel);
		
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		
		float m_aspectRatio;
		float m_zoomLevel = 1.0f;
		
		OrthographicCamera m_camera;

		bool m_rotation;
		bool m_useController;
		Input::Controller m_controller;
		const std::unique_ptr<Window>& m_window;

		Math::Vec3 m_cameraPosition{ 0.0f };
		Math::Vec3 m_cameraRotation{ 0.0f };
		float m_cameraTranslationSpeed = 1.0f, m_cameraRotationSpeed = 180.0f;
	};
}

#endif /*_TRAP_ORTHOGRAPHICCAMERACONTROLLER_H_*/