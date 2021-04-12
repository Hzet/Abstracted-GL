#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "loader.hpp"

namespace agl
{
	namespace importer
	{
		namespace assimp
		{
			/// <summary>
			/// Object loader that uses ASSIMP library to load the objects.
			/// </summary>
			class CLoader
				: public ILoader<CLoader, aiScene*>
			{
			public:
				/// <summary>
				/// Sets the arguments that the data will be imported with.
				/// </summary>
				/// <param name="arguments">The ASSIMP arguments</param>
				void setArguments(std::uint64_t arguments);

				/// <summary>
				/// Returns the directory that the data was loaded from.
				/// </summary>
				/// <returns>The directory</returns>
				const std::string& getDirectory() const;

				/// <summary>
				/// Returns the filename that the data was loaded from.
				/// </summary>
				/// <returns>The filename</returns>
				const std::string& getFilename() const;

				/// <summary>
				/// Loads the data from a file.
				/// Throws an AGL exception on failure.
				/// </summary>
				/// <param name="filepath">The path to the file</param>
				/// <returns>The data</returns>
				virtual const aiScene* loadDataFromFile(const std::string &filepath) override;

				/// <summary>
				/// Saves the data to a file.
				/// Throws an AGL exception on failure.
				/// </summary>
				/// <param name="data">The data to be saved</param>
				/// <param name="filepath">The path to the file</param>
				virtual void saveDataToFile(aiScene *data, const std::string &filepath) override;
									   
			private:
				/// <summary>
				/// Helper method to set the 'directory_' and the 'filename_'.
				/// </summary>
				/// <param name="filepath">The path to the file</param>
				void setFilepath(const std::string &filepath);

				Assimp::Importer importer_;
				std::uint64_t arguments_;
				std::string directory_;
				std::string filename_;
			};
		}
	}
}