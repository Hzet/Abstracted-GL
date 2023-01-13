template <typename T>
std::vector<glm::vec4> shape_builder<T>::get_colors(glm::vec4 const& c) const
{
	return std::vector<glm::vec4>(get_vertex_count(), c);
}
