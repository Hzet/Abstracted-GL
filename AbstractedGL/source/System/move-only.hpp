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
			virtual ~CMoveOnly() = default;

			bool isMoveConstructing() const;
		private:
			bool move_;
		};
	}
}