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
		class CDestructiveMove
		{
		public:
			/// <summary>
			/// Set the 'move_' to false.
			/// </summary>
			CDestructiveMove();

			/// <summary>
			/// Set the 'other' 'move_' to true.
			/// </summary>
			/// <param name="other"></param>
			CDestructiveMove(CDestructiveMove &&other);

			/// <summary>
			/// Deleted copy constructor.
			/// </summary>
			/// <param name=""></param>
			CDestructiveMove(const CDestructiveMove&) = delete;
			
			/// <summary>
			/// Default virtual destructor.
			/// </summary>
			virtual ~CDestructiveMove() = default;

			/// <summary>
			/// Default move assignment operator.
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			CDestructiveMove& operator=(CDestructiveMove&&) = default;

			/// <summary>
			/// Deleted copy assignment operator.
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			CDestructiveMove& operator=(const CDestructiveMove&) = default;

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