#pragma once

namespace TestFramework
{
	class Test {
	public:
		Test() {}
		virtual ~Test(){}
		virtual void onUpdate(float time){}
		virtual void onRender() {}
		virtual void onImGuiRender() {}
	};
}
