#pragma once
#include <string>

namespace agl
{
	namespace importer
	{
		/// <summary>
		/// An interface for future object loaders.
		/// To use this interface one must inherit from it, providing:
		///  > TDerived - inheriting class
		///  > TData - data type returned by the loader
		/// 
		/// Virtual methods loadDataFromFile and saveDataToFile are used to load and save the data to or from a file.
		/// 
		/// To make importer classes compatible with ILoader these must have 
		///  > public default constructor
		///  > method to load object from a data - TReturn importFrom(TDerived&, TPartData, Args...) where:
		///		> TReturn - type that the method returns
		///		> TDerived - inheriting class
		///		> TPartData - at least one argument is required
		///		> Args... - optionally other arguments
		///  > method to save object to the data - void exportTo(TDerived&, TImportable, TPartData, Args...) where:
		///		> TDerived - inheriting class
		///		> TImportable - object to be saved
		///		> TPartData - object to which the data will be saved
		///		> Args... - optionally other arguments
		/// </summary>
		template <typename TDerived, typename TData>
		struct ILoader
		{
			using TConstData = std::conditional_t<std::is_reference_v<TData>, const std::remove_reference_t<TData>&, 
							   std::conditional_t<std::is_pointer_v<TData>, const std::remove_pointer_t<TData>*, const TData>>;

			/// <summary>
			/// Loads the object from a file.
			/// Invokes the loadDataFromFile method.
			/// </summary>
			/// <param name="filepath">The path to the file</param>
			/// <returns>The object</returns>
			template <typename TImporter> auto loadFromFile(const std::string &filepath);

			/// <summary>
			/// Saves the object to a file.
			/// Invokes the saveDataToFile method.
			/// </summary>
			/// <param name="importable">The object to be saved</param>
			/// <param name="filepath">The path to the file</param>
			template <typename TImporter, typename TReturn> void saveToFile(TReturn importable, const std::string &filepath);

			/// <summary>
			/// Loads the object from provided data using TImporter.
			/// </summary>
			/// <param name="data">The input data</param>
			/// <param name="...args">Optional input data</param>
			/// <returns>The object</returns>
			template <typename TImporter, typename TPartData, typename... Args> auto loadFromData(TPartData data, Args&&... args);

			/// <summary>
			/// Saves the object to the data using TImporter.
			/// </summary>
			/// <param name="importable">The object to be saved</param>
			/// <param name="data">The output data</param>
			/// <param name="...args">Optional output data</param>
			template <typename TImporter, typename TReturn, typename TPartData, typename... Args> void saveToData(TReturn importable, TPartData data, Args&&... args);

			/// <summary>
			/// Loads the data from a file.
			/// </summary>
			/// <param name="filepath">The path to the file</param>
			/// <returns>The data</returns>
			virtual TConstData loadDataFromFile(const std::string &filepath) = 0;

			/// <summary>
			/// Saves the data to a file.
			/// </summary>
			/// <param name="data">The input data</param>
			/// <param name="filepath">The path to the object</param>
			virtual void saveDataToFile(TData data, const std::string &filepath) = 0;
		};

#include "loader.inl"
	}
}