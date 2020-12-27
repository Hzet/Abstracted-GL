#pragma once

namespace agl
{
	namespace system
	{
		/// <summary>
		/// A base class for move only objects that have potentially side effects on destruct.
		/// The class obligates the user to declare the constructors and assignment operators as default
		/// or delegate this object's constructors and assignment operators.
		/// </summary>
		class CMoveOnly
		{
		public:
			/// <summary>
			/// Set the 'move_' to false.
			/// </summary>
			CMoveOnly();

			/// <summary>
			/// Set the 'other' 'move_' to true.
			/// </summary>
			/// <param name="other"></param>
			CMoveOnly(CMoveOnly &&other);

			/// <summary>
			/// Deleted copy constructor.
			/// </summary>
			/// <param name=""></param>
			CMoveOnly(const CMoveOnly&) = delete;
			
			/// <summary>
			/// Default virtual destructor.
			/// </summary>
			virtual ~CMoveOnly() = default;

			/// <summary>
			/// Default move assignment operator.
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			CMoveOnly& operator=(CMoveOnly&&) = default;

			/// <summary>
			/// Deleted copy assignment operator.
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			CMoveOnly& operator=(const CMoveOnly&) = default;

			/// <summary>
			/// Check whether 'this' object is being moved to other object.
			/// </summary>
			/// <returns></returns>
			bool isMoveConstructing() const;

		private:
			bool move_;
		};
	}
}