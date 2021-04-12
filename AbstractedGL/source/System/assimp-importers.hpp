#pragma once
#include <vector>
#include <glm/glm.hpp>

struct aiMaterial;
struct aiMesh;
struct aiScene;
struct aiLight;
struct aiNode;
enum aiTextureType;

namespace agl
{
	class CMesh;
	class CModel;
	class CDirectionalLight;
	class CSpotLight;
	class CTextureUID;
	class CTextureMaterial;
	class CTransform;

	namespace importer
	{
		namespace assimp
		{
			class CLoader;

			/// <summary>
			/// Loads the default model.
			/// </summary>
			struct SModel
			{
				CModel importFrom(CLoader &loader, const aiScene *scene);
			};

			/// <summary>
			/// Loads the vector of default meshes.
			/// </summary>
			struct SNode
			{
				std::vector<CMesh> importFrom(CLoader &loader, const aiNode *node, const aiScene *scene);
			};

			/// <summary>
			/// Loads the default mesh.
			/// </summary>
			struct SMesh
			{
				CMesh importFrom(CLoader &loader, const aiMesh *mesh, const aiScene *scene);
			};

			/// <summary>
			/// Loads the texture material uniform.
			/// </summary>
			struct STextureMaterial
			{
				CTextureMaterial importFrom(CLoader &loader, const aiMaterial *material, const std::string &name);
			};

			/// <summary>
			/// Loads the transformation.
			/// </summary>
			struct STransform
			{
				CTransform importFrom(CLoader &loader, const aiNode *node);
			};

			/// <summary>
			/// Loads the directional light uniform.
			/// </summary>
			struct SDirectionalLight
			{
				CDirectionalLight importFrom(CLoader &loader, const aiLight *light, const std::string &name);
			};

			/// <summary>
			/// Loads the vector of 2d texture identifiers registering them in the texture atlas.
			/// </summary>
			struct STexture2D
			{
				std::vector<CTextureUID> importFrom(CLoader &loader, const aiMaterial *material, aiTextureType type);
			};

			/// <summary>
			/// Loads the spot light uniform.
			/// </summary>
			struct SSpotLight
			{
				CSpotLight importFrom(CLoader &loader, const aiLight *light, const std::string &name);
			};

			/// <summary>
			/// Loads the vector of 2D vertices.
			/// </summary>
			struct SVertex2D
			{
				std::vector<glm::vec2> importFrom(CLoader &loader, const aiMesh *mesh);
			};

			/// <summary>
			/// Loads the vector of 3D vertices.
			/// </summary>
			struct SVertex3
			{
				std::vector<glm::vec3> importFrom(CLoader &loader, const aiMesh *mesh);
			};

			/// <summary>
			/// Loads the vector of 2D texture coordinates.
			/// </summary>
			struct STexCoord2
			{
				std::vector<glm::vec2> importFrom(CLoader &loader, const aiMesh *mesh);
			};

			/// <summary>
			/// Loads the vector of 3D normals.
			/// </summary>
			struct SNormal3
			{
				std::vector<glm::vec3> importFrom(CLoader &loader, const aiMesh *mesh);
			};

			/// <summary>
			/// Loads the vector of 4D colors.
			/// </summary>
			struct SColor4
			{
				std::vector<glm::vec4> importFrom(CLoader &loader, const aiMesh *mesh);
			};

			/// <summary>
			/// Loads the vector of indices.
			/// </summary>
			struct SIndices
			{
				std::vector<std::uint32_t> importFrom(CLoader &loader, const aiMesh *mesh);
			};
		}
	}
}