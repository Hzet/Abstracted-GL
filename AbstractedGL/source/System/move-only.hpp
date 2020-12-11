#pragma once

namespace agl
{
	namespace system
	{
		class CMoveOnly
		{
		public:
			CMoveOnly();
			CMoveOnly(CMoveOnly &&other);
			CMoveOnly(const CMoveOnly &) = delete;
			virtual ~CMoveOnly() = default;

			CMoveOnly& operator=(CMoveOnly&&) = default;
			CMoveOnly& operator=(const CMoveOnly&) = default;

			bool isMoveConstructing() const;

		private:
			bool move_;
		};
	}
}