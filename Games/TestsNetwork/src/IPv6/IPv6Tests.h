#ifndef _GAMESTRAP_IPV6TESTS_H_
#define _GAMESTRAP_IPV6TESTS_H_

#include <TRAP.h>

class IPv6Tests final : public TRAP::Layer
{
public:
	IPv6Tests();

	void OnAttach() override;
	void OnDetach() override;

private:
	static void IPv6();
	
	TRAP::Scope<std::thread> m_ipv6Thread;
};


#endif /*_GAMESTRAP_IPV6TESTS_H_*/