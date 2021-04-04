#pragma once 
#include <vector>

namespace agl
{
	namespace system
	{

		/// <summary>
		/// A wrapper around std::vector<> so the other classes can inherit from it,
		/// avoiding the need to provide implementation of it's features.
		/// </summary>
		template <typename T>
		class IInheritableVector
		{
		public:
			using value_type		 = typename std::vector<T>::value_type;
			using reference			 = typename std::vector<T>::reference;
			using const_reference	 = typename std::vector<T>::const_reference;
			using pointer			 = typename std::vector<T>::pointer;
			using const_pointer		 = typename std::vector<T>::const_pointer;
			using iterator			 = typename std::vector<T>::iterator;
			using const_iterator	 = typename std::vector<T>::const_iterator;

			/// <summary>
			/// Default constructor.
			/// </summary>
			IInheritableVector() = default;

			/// <summary>
			/// Resizes the vector to be capable of storing 'count' elements.
			/// </summary>
			/// <param name="count"></param>
			IInheritableVector(std::uint64_t count);

			/// <summary>
			/// Default move constructor.
			/// </summary>
			/// <param name=""></param>
			IInheritableVector(IInheritableVector&&) = default;

			/// <summary>
			/// Default copy constructor.
			/// </summary>
			/// <param name=""></param>
			IInheritableVector(const IInheritableVector&) = default;

			/// <summary>
			/// Clear the underlying vector.
			/// </summary>
			virtual ~IInheritableVector();

			/// <summary>
			/// Default move assignment operator.
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			IInheritableVector& operator=(IInheritableVector&&) = default;

			/// <summary>
			/// Default copy assignment operator.
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			IInheritableVector& operator=(const IInheritableVector&) = default;

			/// <summary>
			/// Returns the reference to the element at position 'index'.
			/// This method checks if the 'index' is between zero and 'getCount() - 1', rasing an exception otherwise.
			/// </summary>
			/// <param name="index">The index of the element</param>
			/// <returns>The reference</returns>
			reference at(std::uint64_t index);

			/// <summary>
			/// Returns the const reference to the element at position 'index'.
			/// This method checks if the 'index' is between zero and 'getCount() - 1', rasing an exception otherwise.
			/// </summary>
			/// <param name="index">The index of the element</param>
			/// <returns>The const reference</returns>
			const_reference at(std::uint64_t index) const;

			/// <summary>
			/// Returns the reference to the element at position 'index'.
			/// </summary>
			/// <param name="index">The index of the element</param>
			/// <returns>The reference</returns>
			reference operator[](std::uint64_t index);

			/// <summary>
			/// Returns the reference to the element at position 'index'.
			/// </summary>
			/// <param name="index">The index of the element</param>
			/// <returns>The reference</returns>
			const_reference operator[](std::uint64_t index) const;

			/// <summary>
			/// Returns a reference to the first element.
			/// The behavior is undefined if the element does not exist.
			/// </summary>
			/// <returns>A reference to the first element</returns>
			reference front();

			/// <summary>
			/// Returns a reference to the last element.
			/// The behavior is undefined if the element does not exist.
			/// </summary>
			/// <returns>A reference to the last element</returns>
			reference back();

			/// <summary>
			/// Returns a const reference to the first element.
			/// The behavior is undefined if the element does not exist.
			/// </summary>
			/// <returns>A const reference to the first element</returns>
			const_reference front() const;

			/// <summary>
			/// Returns a const reference to the last element.
			/// The behavior is undefined if the element does not exist.
			/// </summary>
			/// <returns>A const reference to the last element</returns>
			const_reference back() const;

			/// <summary>
			/// Returns a raw pointer to the data contained in the vector.
			/// The pointer can not be dereferenced if the vector is empty.  
			/// </summary>
			/// <returns>The pointer</returns>
			const_pointer data() const;

			/// <summary>
			/// Returns the iterator pointing to the first element in the vector.
			/// </summary>
			/// <returns>The iterator to the first element or CShaderEntryVector::end() if the vector is empty</returns>
			iterator begin();

			/// <summary>
			/// Returns the iterator pointing to the element behind the last element in the vector.
			/// </summary>
			/// <returns>The iterator to the element behind the last element</returns>
			iterator end();

			/// <summary>
			/// Returns the const iterator pointing to the first element in the vector. 
			/// </summary>
			/// <returns>The const iterator to the first element or CShaderEntryVector::end() if the vector is empty</returns>
			const_iterator cbegin() const;

			/// <summary>
			/// Returns the const iterator pointing to the element behind the last element in the vector.
			/// </summary>
			/// <returns>The const iterator to the element behind the last element</returns>
			const_iterator cend() const;

			/// <summary>
			/// Checks whether the vector is empty.
			/// </summary>
			/// <returns>
			/// True - the vector is empty
			/// False - the vector is not empty
			/// </returns>
			bool empty() const;

			/// <summary>
			/// Returns the current count of the elements that the vector can store.
			/// </summary>
			/// <returns>The count</returns>
			std::uint64_t count() const;

			/// <summary>
			/// If the 'count' is greater than current 'capacity()' new memory will be allocated,
			/// causing the iterators to be invalidated. Otherwise this method has no effect.
			/// </summary>
			/// <param name="count">New capacity</param>
			void reserve(std::uint64_t count);

			/// <summary>
			/// Returns the total count of the elements that the vector
			/// can expand to without allocating new memory.
			/// </summary>
			/// <returns></returns>
			std::uint64_t capacity() const;

			/// <summary>
			/// Removes all elements in the vector and set it's count to zero.
			/// </summary>
			void clear();

			/// <summary>
			/// Insert 'value' before 'position'.
			/// </summary>
			/// <param name="position">The position</param>
			/// <param name="value">The value</param>
			/// <returns>Iterator pointing to the inserted value</returns>
			iterator insert(const_iterator position, T &&value);

			/// <summary>
			/// Inserts 'count' 'values' before 'position'.
			/// </summary>
			/// <param name="position">The position</param>
			/// <param name="count">The count</param>
			/// <param name="value">The value</param>
			/// <returns>Iterator pointing to the first element inserted, or pos if count==0</returns>
			iterator insert(const_iterator position, std::uint64_t count, const T &value);

			/// <summary>
			/// Insert elements from range ['first', 'last') before 'position'.
			/// </summary>
			/// <param name="position">The position</param>
			/// <param name="first">The iterator of the first element</param>
			/// <param name="last">The iterator of the second element</param>
			/// <returns>Iterator pointing to the first element inserted, or pos if first == last</returns>
			template<class InputIt>
			iterator insert(const_iterator position, InputIt first, InputIt last);

			/// <summary>
			/// Inserts elements from 'list' before 'position'.
			/// </summary>
			/// <param name="position">The position</param>
			/// <param name="list">The initializer list</param>
			/// <returns>Iterator pointing to the first element inserted, or pos if list is empty</returns>
			iterator insert(const_iterator position, std::initializer_list<T> list);
			
			/// <summary>
			/// Removes the element from the vector located at 'position'.
			/// The iterator must be valid and possible to be dereferenced.
			/// All the iterators are invalidated after this method succeeds.
			/// </summary>
			/// <param name="position">The iterator pointing to the element</param>
			void erase(iterator position);

			/// <summary>
			/// Removes the element from the vector located at 'position'.
			/// The iterator must be valid and possible to be dereferenced.
			/// All the iterators are invalidated after this method succeeds.
			/// </summary>
			/// <param name="position">The iterator pointing to the element</param>
			void erase(const_iterator position);

			/// <summary>
			/// Removes the elements from the vector from the range starting at 'first' and ending one element before the 'last' position.
			/// The iterator must be valid and possible to be dereferenced.
			/// All the iterators are invalidated after this method succeeds.
			/// </summary>
			/// <param name="first">The beginning of the range</param>
			/// <param name="last">The end of the range (excluded)</param>
			void erase(iterator first, iterator last);

			/// <summary>
			/// Removes the elements from the vector from the range starting at 'first' and ending one element before the 'last' position.
			/// The iterator must be valid and possible to be dereferenced.
			/// All the iterators are invalidated after this method succeeds.
			/// </summary>
			/// <param name="first">The beginning of the range</param>
			/// <param name="last">The end of the range (excluded)</param>
			void erase(const_iterator first, const_iterator last);

			/// <summary>
			/// Adds a copy of an element to the end of the vector.
			/// </summary>
			/// <param name="element">The element</param>
			void push_back(const T &element);

			/// <summary>
			/// Moves an element to the end of the vector.
			/// </summary>
			/// <param name="element">The element</param>
			void push_back(T &&element);

			/// <summary>
			/// Resizes the vector, so it can be capable of storing 'count' elements.
			/// If the 'count' is different from the current count, all the iterators are invalidated.
			/// </summary>
			/// <param name="count">The new count</param>
			void resize(std::uint64_t count);

		protected:
			/// <summary>
			/// Method that will be called each time, the vector's size is modified.
			/// The vector does not track the modify status of stored elements.
			/// </summary>
			virtual void onUpdate() {};

		private:
			std::vector<T> vector_;
		};

#include "inheritable-vector.inl"
	}
}