#pragma once
#include "TestFramework/test.h"
namespace test
{
	class CClearColor : public TestFramework::Test
	{
	public:
		CClearColor();
		~CClearColor();

		void onUpdate(float time) override;
		void onRender() override;
		void onImGuiRender() override;

	private:
		float m_colorClear[4];

	};

}