template <typename TGroupName>
group<TGroupName>::group()
	: group_base(group_type_uid::get_id<TGroupName>())
{
}