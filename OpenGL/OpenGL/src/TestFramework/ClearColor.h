#pragma once
#include "TestFramework/test.h"
#include <vector>
#include <string>
#include <functional>

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


	class CTestMenu : public TestFramework::Test
	{
	public:
		
		CTestMenu(TestFramework::Test*& instance );
		~CTestMenu();

		void onImGuiRender() override;

		template <typename T>
		void registerTaskInstance(const std::string& name) {
			m_vecTask.push_back({ std::make_pair(name, []() {return new T(); }) });
		}

	private:
		TestFramework::Test*& m_testCurr;
		std::vector<std::pair<std::string, std::function<TestFramework::Test*()>>>  m_vecTask;

	};

}