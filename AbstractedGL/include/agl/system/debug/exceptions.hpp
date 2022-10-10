#pragma once
#include <string>
#include <exception>

namespace agl
{
	class exception
		: public std::exception
	{
	public:
		exception() noexcept = default;
		exception(const std::string &message) noexcept;
		exception(std::string &&message) noexcept;
		exception(const exception &other) noexcept;

		virtual ~exception() noexcept = default;

		virtual const char* what() const noexcept override;

		virtual std::string defaultMessage() const = 0;

	private:
		bool m_initialized;
		mutable std::string m_message;
	};


		// File
		struct ExFileOpen : exception {
			using exception::exception;

			virtual std::string defaultMessage() const override { 
				return "Failed to open a file"; 
			}
		};

		struct ExFileRead : exception {
			using exception::exception;

			virtual std::string defaultMessage() const override {
				return "Failed to read from a file";
			}
		};

		struct ExFileWrite : exception {
			using exception::exception;

			virtual std::string defaultMessage() const override {
				return "Failed to write to a file";
			}
		};

		// API
		// GLFW
		struct ExGLFW : exception {
			using exception::exception;

			virtual std::string defaultMessage() const override {
				return "GLFW has failed to execute call";
			}
		};

		struct ExGLFWNotInitialized : ExGLFW {
			using ExGLFW::ExGLFW;
		};

		struct ExGLFWNoCurrentContext : ExGLFW {
			using ExGLFW::ExGLFW;
		};

		struct ExGLFWInvalidEnum : ExGLFW {
			using ExGLFW::ExGLFW;
		};

		struct ExGLFWInvalidValue : ExGLFW {
			using ExGLFW::ExGLFW;
		};

		struct ExGLFWOutOfMemory : ExGLFW {
			using ExGLFW::ExGLFW;
		};

		struct ExGLFWUnavailable : ExGLFW {
			using ExGLFW::ExGLFW;
		};

		struct ExGLFWPlatform : ExGLFW {
			using ExGLFW::ExGLFW;
		};

		struct ExGLFWFormatUnavailable : ExGLFW {
			using ExGLFW::ExGLFW;
		};

		struct ExGLFWNoWindowContext : ExGLFW {
			using ExGLFW::ExGLFW;
		};

		struct ExGLAD : exception {
			using exception::exception;

			virtual std::string defaultMessage() const override {
				return "GLAD has failed to execute call";
			}
		};

		// OpenGL
		struct ExOpenGL : exception {
			using exception::exception;

			virtual std::string defaultMessage() const override {
				return "OpenGL has failed to execute call";
			}
		};

		// Shaders
		struct ExShaderCompilation : exception {
			using exception::exception;

			virtual std::string defaultMessage() const override {
				return "Shader program has failed to compile";
			}
		};

		struct ExShaderLinking : exception {
			using exception::exception;

			virtual std::string defaultMessage() const override {
				return "Shader program has failed to link";
			}
		};

		// Importer
		struct ExImport : exception {
			using exception::exception;

			virtual std::string defaultMessage() const override {
				return "Failed to import the data";
			}
		};

		struct ExExport : exception {
			using exception::exception;

			virtual std::string defaultMessage() const override {
				return "Failed to export the data";
			}
		};
	
}