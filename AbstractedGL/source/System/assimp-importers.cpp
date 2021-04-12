#include "assimp-importers.hpp"
#include "assimp-loader.hpp"

#include "../Graphic/default-agl-shaders.hpp"
#include "../Graphic/directional-light-uniform.hpp"
#include "../Graphic/spot-light-uniform.hpp"
#include "../Graphic/mesh.hpp"
#include "../Graphic/model.hpp"
#include "../Graphic/texture-atlas.hpp"
#include "../Graphic/texture-material-uniform.hpp"

#include <assimp/scene.h>
#include <glm/glm.hpp>


namespace agl
{
	namespace importer
	{
		namespace assimp
		{
			CTransform STransform::importFrom(CLoader &loader, const aiNode *node)
			{
				auto t = node->mTransformation;
				return { {t.a1, t.a2, t.a3, t.a4,
						  t.b1, t.b2, t.b3, t.b4,
						  t.c1, t.c2, t.c3, t.c4,
						  t.d1, t.d2, t.d3, t.d4} };
			}

			CModel SModel::importFrom(CLoader &loader, const aiScene *scene)
			{
				CModel result;

				std::vector<CMesh> meshes = loader.loadFromData<SNode>(scene->mRootNode, scene);

				result.setMeshes(meshes);

				return result;
			}

			std::vector<CMesh> SNode::importFrom(CLoader &loader, const aiNode *node, const aiScene *scene)
			{
				std::vector<CMesh> result;

				for (std::uint64_t i = 0u; i < node->mNumMeshes; i++)
				{
					const aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
					result.push_back(loader.loadFromData<SMesh>(mesh, scene));
					result.back().setTransform(loader.loadFromData<STransform>(node));
				}

				for (std::uint64_t i = 0u; i < node->mNumChildren; i++)
				{
					std::vector<CMesh> subresult = loader.loadFromData<SNode>(node->mChildren[i], scene);
					result.insert(result.cend(), subresult.cbegin(), subresult.cend());
				}

				return result;
			}

			CMesh SMesh::importFrom(CLoader &loader, const aiMesh *mesh, const aiScene *scene)
			{
				CMesh result;

				result.setShader(agl::Shader::LIGHT_SHADER);
				result.setIndices(loader.loadFromData<SIndices>(mesh));
				result.setVertices(loader.loadFromData<SVertex3>(mesh));
				result.setNormals(loader.loadFromData<SNormal3>(mesh));
				result.setTexCoords(loader.loadFromData<STexCoord2>(mesh));

				CTextureMaterial material = loader.loadFromData<STextureMaterial>(scene->mMaterials[mesh->mMaterialIndex], "agl_texture_material");
				material.setShader(agl::Shader::LIGHT_SHADER);

				if (!material.isEmpty())
					result.addUniform(material);

				return result;
			}

			CTextureMaterial STextureMaterial::importFrom(CLoader &loader, const aiMaterial *material, const std::string &name)
			{
				CTextureMaterial result(name);

				result.ambient = loader.loadFromData<STexture2D>(material, aiTextureType_AMBIENT);
				result.diffuse = loader.loadFromData<STexture2D>(material, aiTextureType_DIFFUSE);
				result.specular = loader.loadFromData<STexture2D>(material, aiTextureType_SPECULAR);

				return result;
			}

			CDirectionalLight SDirectionalLight::importFrom(CLoader &loader, const aiLight *light, const std::string &name)
			{
				throw std::logic_error("Method not yet implemented!");
			}

			CSpotLight SSpotLight::importFrom(CLoader &loader, const aiLight *light, const std::string &name)
			{
				throw std::logic_error("Method not yet implemented!");
			}

			std::vector<glm::vec2> SVertex2D::importFrom(CLoader &loader, const aiMesh *mesh)
			{
				std::vector<glm::vec2> result(mesh->mNumVertices);

				for (std::uint64_t i = 0u; i < result.size(); i++)
				{
					result[i].x = mesh->mVertices[i].x;
					result[i].y = mesh->mVertices[i].y;
				}

				return result;
			}

			std::vector<glm::vec3> SVertex3::importFrom(CLoader &loader, const aiMesh *mesh)
			{
				std::vector<glm::vec3> result(mesh->mNumVertices);

				for (std::uint64_t i = 0u; i < result.size(); i++)
				{
					result[i].x = mesh->mVertices[i].x;
					result[i].y = mesh->mVertices[i].y;
					result[i].z = mesh->mVertices[i].z;
				}

				return result;
			}

			std::vector<glm::vec2> STexCoord2::importFrom(CLoader &loader, const aiMesh *mesh)
			{
				std::vector<glm::vec2> result(mesh->mNumVertices);

				for (std::uint64_t i = 0u; i < result.size(); i++)
				{
					result[i].x = mesh->mTextureCoords[0u][i].x;
					result[i].y = mesh->mTextureCoords[0u][i].y;
				}

				return result;
			}

			std::vector<glm::vec3> SNormal3::importFrom(CLoader &loader, const aiMesh *mesh)
			{
				std::vector<glm::vec3> result(mesh->mNumVertices);

				for (std::uint64_t i = 0u; i < result.size(); i++)
				{
					result[i].x = mesh->mNormals[i].x;
					result[i].y = mesh->mNormals[i].y;
					result[i].z = mesh->mNormals[i].z;
				}

				return result;
			}

			std::vector<glm::vec4> SColor4::importFrom(CLoader &loader, const aiMesh *mesh)
			{
				std::vector<glm::vec4> result(mesh->mNumVertices);

				for (std::uint64_t i = 0u; i < result.size(); i++)
				{
					result[i].x = mesh->mColors[i]->r;
					result[i].y = mesh->mColors[i]->g;
					result[i].z = mesh->mColors[i]->b;
					result[i].w = mesh->mColors[i]->a;
				}

				return result;
			}

			std::vector<std::uint32_t> SIndices::importFrom(CLoader &loader, const aiMesh *mesh)
			{
				std::vector<std::uint32_t> result;

				for (std::uint64_t i = 0u; i < mesh->mNumFaces; i++)
				{
					result.resize(result.size() + mesh->mFaces[i].mNumIndices);

					for (std::uint64_t j = 0; j < mesh->mFaces[i].mNumIndices; j++)
						result[i] = mesh->mFaces[i].mIndices[j];
				}

				return result;
			}

			std::vector<CTextureUID> STexture2D::importFrom(CLoader &loader, const aiMaterial *material, aiTextureType type)
			{
				std::vector<CTextureUID> result;

				for (std::uint64_t i = 0u; i < material->GetTextureCount(type); i++)
				{
					aiString filename;
					material->GetTexture(type, i, &filename);

					if (CTextureAtlas::HasTexture2D(loader.getDirectory() + '/' + filename.C_Str()))
					{
						result.push_back(CTextureAtlas::GetTextureUID(loader.getDirectory() + '/' + filename.C_Str()));
						continue;
					}

					CTexture2D texture;
					texture.loadFromFile(loader.getDirectory() + '/' + filename.C_Str());
					texture.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
					texture.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
					texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

					result.push_back(CTextureAtlas::AddTexture2D(texture, loader.getDirectory() + '/' + filename.C_Str()));
				}

				return result;
			}
		}
	}
}

