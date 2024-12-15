#include "ClearColor.h"

#include "../GLCommondef.h"
#include "imgui/imgui.h"

namespace test
{

	CClearColor::CClearColor() : m_colorClear{ 0.2f,0.3f,0.8f,1.0f }
	{
	}

	CClearColor::~CClearColor()
	{
	}

	void CClearColor::onUpdate(float time)
	{
	}

	void CClearColor::onRender()
	{
		GLCall(glClearColor(m_colorClear[0], m_colorClear[1], m_colorClear[2], m_colorClear[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void CClearColor::onImGuiRender()
	{
		ImGui::ColorEdit4("setcolor", m_colorClear);
	}
	CTestMenu::CTestMenu(TestFramework::Test*& instance)
		: m_testCurr(instance)
	{
	}
	CTestMenu::~CTestMenu()
	{
	}

	void CTestMenu::onImGuiRender()
	{
		for (auto& task : m_vecTask)
		{
			
		}
		for (auto& iter : m_vecTask)
		{
			if (ImGui::Button(iter.first.c_str()))
				m_testCurr = iter.second();
			
		}
	}
}