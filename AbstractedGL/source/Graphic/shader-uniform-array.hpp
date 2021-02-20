#pragma once

#include <type_traits>

#include "shader-uniform.hpp"
#include "shader-manager.hpp"
#include "../System/inheritable-vector.hpp"

namespace agl
{
	class IUniformVariable;

	namespace detail
	{
		template <typename T>
		struct is_not_agl_uniform_concrete
			: std::enable_if<!std::is_base_of<IUniform, T>::value>
		{
		};

/*
		template <typename T>
		using is_not_agl_uniform_concrete_t = typename is_not_agl_uniform_concrete<T>::type;*/

		template <typename T>
		struct is_agl_uniform_concrete
			: std::enable_if<!std::is_same<IUniformVariable, T>::value &&
							  std::is_base_of<IUniformVariable, T>::value>
		{
		};		
		
/*
		template <typename T>
		using is_agl_uniform_concrete_t = typename is_agl_uniform_concrete<T>::type;*/
	}

	template <typename T, typename = void>
	class CUniformArray
	{
	};

	template <typename T>
	class CUniformArray<T, typename detail::is_not_agl_uniform_concrete<T>::type>
		: public IUniform,
		public system::CInheritableVector<T>
	{
	public:
		using system::CInheritableVector<T>::CInheritableVector;

		CUniformArray() : shaderUID_(CShaderUID::InvalidValue())
		{
		}


		virtual void setName(const std::string &name) override 
		{
			IUniform::setName(name);

			updateDictionary();
		}

		const CShaderUID& getShader() const
		{
			return shaderUID_;
		}

		void create(const std::string &name, const CShaderUID &shaderUID = CShaderUID::InvalidValue())
		{
			setName(name);
			shaderUID_ = shaderUID;
		}

		void redirect(const CShaderUID &shaderUID) 
		{
			shaderUID_ = shaderUID;
		}

		virtual void passToShader() const override 
		{
			const CShader &shader = CShaderManager::GetShader(shaderUID_);
			shader.setActive();

			if (lastCount_ != this->count())
			{
				updateDictionary();
				lastCount_ = this->count();
			}

			auto key = dictionary_.cbegin();
			for (auto it = this->cbegin(); it != this->cend(); ++it)
				shader.setUniform(*(key++), *it);
		}

		virtual std::unique_ptr<IUniform> clone() const 
		{
			return std::unique_ptr<IUniform>(new CUniformArray<T>(*this));
		}

	private:
		void updateDictionary() const
		{
			dictionary_.resize(this->count());

			std::string elemName = this->getName() + "[ ]";
			const std::uint64_t insert = this->getName().size();

			for (std::uint64_t i = 0u; i < this->count(); i++)
			{
				const std::string num = std::to_string(i);
				elemName.replace(insert, num.size(), num);
				dictionary_[i] = elemName;
			}
		}

		CShaderUID shaderUID_;

		mutable std::uint64_t lastCount_;
		mutable std::vector<std::string> dictionary_;
	};

	template <typename T>
	class CUniformArray<T, typename detail::is_agl_uniform_concrete<T>::type>
		: public IUniform,
		public system::CInheritableVector<T>
	{
	public:
		using system::CInheritableVector<T>::CInheritableVector;

		virtual void setName(const std::string &name) override
		{
			IUniform::setName(name);

			updateUniforms();
		}

		const CShaderUID& getShaderOf(const std::string &name, std::uint64_t index) const
		{
			return (*this)[index].getShaderOf(name);
		}

		void redirect(const std::string &name, std::uint64_t index, const CShaderUID &shaderUID) 
		{
			(*this)[index].redirect(name, shaderUID);
		}

		virtual void passToShader() const override 
		{
			if (lastCount_ != this->count())
			{
				updateUniforms();
				lastCount_ = this->count();
			}

			for (auto it = this->cbegin(); it != this->cend(); ++it)
				it->passToShader();
		}

		virtual std::unique_ptr<IUniform> clone() const 
		{
			return std::unique_ptr<IUniform>(new CUniformArray<T>(*this));
		}

	private:
		void updateUniforms() const 
		{
			std::string elemName = this->getName() + "[ ]";
			const std::uint64_t insert = this->getName().size();

			for (std::uint64_t i = 0u; i < this->count(); i++)
			{
				const std::string num = std::to_string(i);
				elemName.replace(insert, num.size(), num);
				(*this)[i].setName(elemName);
			}
		}

		mutable std::uint64_t lastCount_;
	};

#include "shader-uniform-array.inl"
}