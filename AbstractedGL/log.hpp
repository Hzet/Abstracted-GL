#pragma once
#include <string>
#include <iostream>

namespace agl
{
	class CLogInstance
	{
		friend class CLog;

		CLogInstance(std::ostream &target);
		CLogInstance(const CLogInstance &other);
		//CLogInstance& operator=(const CLogInstance&);

		void log(std::initializer_list<std::string> msgs);

		std::ostream &target_;
	};

	class CLog
	{
	public:
		static void SendMessage(std::initializer_list<std::string> msgs);
		static void MessageTarget(std::ostream &target);

	private:
		CLog() = default;
		CLog(CLog &&other) = default;
		~CLog() = default;

		static std::unique_ptr<CLogInstance> Instance_;
	};
}