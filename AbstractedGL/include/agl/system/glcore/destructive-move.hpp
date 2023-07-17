#pragma once

namespace agl
{

	/// <summary>
	/// A base class for move only objects that have potentially side effects on destruct.
	/// The class obligates the user to declare the constructors and assignment operators as default
	/// or delegate this object's constructors and assignment operators.
	/// </summary>
	class destructive_move
	{
	public:
		/// <summary>
		/// Set the 'm_moving' to false.
		/// </summary>
		destructive_move();

		/// <summary>
		/// Set the 'other' 'm_moving' to true.
		/// </summary>
		/// <param name="other"></param>
		destructive_move(destructive_move &&other);

		/// <summary>
		/// Default copy constructor.
		/// </summary>
		/// <param name=""></param>
		destructive_move(const destructive_move&) = default;
			
		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~destructive_move() = default;

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		destructive_move& operator=(destructive_move&&) = default;

		/// <summary>
		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		destructive_move& operator=(const destructive_move&) = default;

		/// <summary>
		/// Check whether 'this' object is being moved to other object.
		/// </summary>
		/// <returns></returns>
		bool is_move_constructing() const;

	private:
		bool m_moving;
	};
}