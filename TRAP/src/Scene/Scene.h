#ifndef _TRAP_SCENE_H_
#define _TRAP_SCENE_H_

#pragma warning(push, 0)
#include "entt.h"
#pragma warning(pop)

namespace TRAP
{
	namespace Utils
	{
		struct TimeStep;
	}

	class Entity;
	
	class Scene
	{
	public:
		Scene();
		~Scene();
		
		Scene(const Scene&) = delete;
		Scene(Scene&&) = default;
		Scene& operator=(const Scene&) = delete;
		Scene& operator=(Scene&&) = default;

		Entity CreateEntity(const std::string& name = std::string());

		//TEMP
		entt::registry& Reg()
		{
			return m_registry;
		}

		void OnUpdate(Utils::TimeStep deltaTime);
		void OnTick();
		void OnViewportResize(uint32_t width, uint32_t height);
		
	private:
		entt::registry m_registry;
		uint32_t m_viewportWidth = 0, m_viewportHeight = 0;

		friend class Entity;
	};
}

#endif /*_TRAP_SCENE_H_*/