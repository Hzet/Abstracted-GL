#pragma once

namespace agl
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