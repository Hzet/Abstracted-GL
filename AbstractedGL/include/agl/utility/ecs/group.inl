template <typename TGroupName>
group<TGroupName>::group()
	: group_base(TGroupTypeUID<TGroupName>::value())
{
}