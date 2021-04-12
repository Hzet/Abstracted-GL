#include "assimp-loader.hpp"
#include "error.hpp"
#include "error-code.hpp"

#include <assimp/Importer.hpp>

namespace agl
{
	namespace importer
	{
		namespace assimp
		{
			void CLoader::setArguments(std::uint64_t arguments)
			{
				arguments_ = arguments;
			}

			const std::string& CLoader::getDirectory() const
			{
				return directory_;
			}

			const std::string& CLoader::getFilename() const
			{
				return filename_;
			}

			const aiScene* CLoader::loadDataFromFile(const std::string &filepath)
			{
				const aiScene *scene = importer_.ReadFile(filepath, arguments_);

				if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
					AGL_CORE_ERROR("Failed to load the model file {} {}", error::READ_FILE, importer_.GetErrorString());

				setFilepath(filepath);

				return scene;
			}

			void CLoader::saveDataToFile(aiScene *data, const std::string &filepath)
			{
				/*...*/
			}

			void CLoader::setFilepath(const std::string &filepath)
			{
				std::uint64_t found = filepath.find_last_of('/');

				if (found == std::string::npos)
					found = filepath.find_last_of('\\');

				if (found == std::string::npos)
				{
					directory_ = "";
					filename_ = filepath;
				}
				else
				{
					directory_ = filepath.substr(0, found);
					filename_ = filepath.substr(found);
				}
			}
		}
	}
}

