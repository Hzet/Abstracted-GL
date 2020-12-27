#pragma once
#include <string>
#include <chrono>
#include <unordered_map>

namespace agl
{
	namespace system
	{
		/// <summary>
		/// The clock that counts the time taken by a method/function.
		/// </summary>
		class CProfilerClock
		{
		public:
			/// <summary>
			/// Set the 'name_' to 'callerName' and start the timer.
			/// </summary>
			/// <param name="callerName">The name under which the time passed will be added</param>
			CProfilerClock(std::string &&callerName);

			/// <summary>
			/// Stop the timer and add it's time to the 'name_'
			/// </summary>
			~CProfilerClock();

			/// <summary>
			/// Get all names and corresponding clocks.
			/// </summary>
			/// <returns>
			/// The 'Clocks_'
			/// </returns>
			static const std::unordered_map<std::string, std::uint64_t>& GetClocks();

		private:
			static std::unordered_map<std::string, std::uint64_t> Clocks_;

			const std::string name_;
			const std::chrono::milliseconds myClock_;
		};
	}
}
#ifdef AGL_DEBUG
	#define AGL_FILE __FILE__
	#define AGL_LINE __LINE__

	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define AGL_FUNC_NAME __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define AGL_FUNC_NAME __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define AGL_FUNC_NAME __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define AGL_FUNC_NAME __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define AGL_FUNC_NAME __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define AGL_FUNC_NAME __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define AGL_FUNC_NAME __func__
	#else
		#define AGL_FUNC_NAME "AGL_FUNC_NAME could not be established!"
	#endif

	#define AGL_CODE_POINT std::string("Filename: ") + AGL_FILE + "\nFunction: " + AGL_FUNC_NAME + "\nLine: " + std::to_string(AGL_LINE)

	#define AGL_PROFILE_THIS() ::agl::system::CProfilerClock AGL_PROFILER_VARIABLE(AGL_CODE_NAME)

	#define AGL_HALT() __debugbreak()

#else
	#define AGL_PROFILE_THIS()
#endif