#ifndef _TRAPEDITORPROPERTIESPANEL_H_
#define _TRAPEDITORPROPERTIESPANEL_H_

#include <TRAP_Assert.h>
#include <Scene/Entity.h>

namespace TRAP
{
	class PropertiesPanel
	{
	public:
		PropertiesPanel() = default;
		explicit PropertiesPanel(const Entity& entity);

		void SetEntity(const Entity& entity);

		void OnImGuiRender();
	private:
		void DrawComponents(Entity entity);
		template<typename T, typename F>
		void DrawComponent(const std::string& name, Entity& entity, F func);

		Entity m_entity;
	};
}

#endif /*_TRAPEDITORPROPERTIESPANEL_H_*/