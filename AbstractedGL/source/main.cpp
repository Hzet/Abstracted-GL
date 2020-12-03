#include <iostream>

#include "Graphics/window.hpp"
#include "Graphics/camera.hpp"

constexpr float SCR_WIDTH = 1920.f;
constexpr float SCR_HEIGHT = 1080.f;

constexpr float cameraVelocity = 0.1f;
constexpr float mouseSensitivity = 0.01f;

int main()
{
	agl::CWindow window("Abstracted OpenGL", SCR_WIDTH, SCR_HEIGHT);
	
	agl::CRenderer renderer;
	if (!renderer.loadShaderFromFile("resource/basic_shader", "resource/basic_shader.vertex", "resource/basic_shader.fragment"))
	{
		std::cerr << "Failed to create shader program:\n" << agl::CShaderProgram::getErrorInfoLog() << std::endl;
		return -1;
	}

	if (!renderer.loadShaderFromFile("resource/light_shader", "resource/basic_shader.vertex", "resource/light_shader.fragment"))
	{
		std::cerr << "Failed to create shader program:\n" << agl::CShaderProgram::getErrorInfoLog() << std::endl;
		return -1;
	}

	window.setRenderer(renderer);

	agl::CCamera camera;
	camera.setAspectRatio(SCR_WIDTH / SCR_HEIGHT);
	camera.setPosition({ 0.f, 0.f, 3.f });
	/*camera.lookAt(qubes[4u].getPosition());*/

/*
	GLCall(glEnable(GL_DEPTH_TEST));

	while (window.isOpen())
	{
		haz::SEvent event;
		while (window.pollEvent(event))
		{
			if (event.type == haz::SEvent::KEY_PRESSED || event.type == haz::SEvent::KEY_REPEATED)
			{
				switch (event.key.code)
				{
				case haz::Keyboard::ESCAPE:
					window.close();
					break;
				case haz::Keyboard::A:
					camera.move(camera.getDirection().right * -cameraVelocity);
					break;
				case haz::Keyboard::D:
					camera.move(camera.getDirection().right * cameraVelocity);
					break;
				case haz::Keyboard::W:
					camera.move(camera.getDirection().forward * cameraVelocity);
					break;
				case haz::Keyboard::S:
					camera.move(camera.getDirection().forward * -cameraVelocity);
					break;
				case haz::Keyboard::SPACE:
					camera.move(camera.getDirection().up * cameraVelocity);
					break;
				case haz::Keyboard::LEFT_CONTROL:
					camera.move(camera.getDirection().up * -cameraVelocity);
					break;
				}
			}
			else if (event.type == haz::SEvent::MOUSE_SCROLL_MOVED)
			{
				camera.setFieldOfView(camera.getFieldOfView() - event.scroll.y);
			}
			else if (event.type == haz::SEvent::MOUSE_MOVED)
			{
				camera.rotate({ (SCR_WIDTH / 2.f - event.position.x) * mouseSensitivity , (SCR_HEIGHT / 2.f - event.position.y) * -mouseSensitivity, 0.f });

				window.setCursorPosition({ SCR_WIDTH / 2.f, SCR_HEIGHT / 2.f });
			}
		}

		GLCall(glClearColor(0.f, 0.1f, 0.2f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


		const haz::CShaderProgram &shader = window.getRenderer().getShader("basic_shader");
		const haz::CShaderProgram &lightShader = window.getRenderer().getShader("light_shader");

		shader.useProgram();
		shader.setMat4f("view", camera.getView());
		shader.setMat4f("projection", camera.getProjection());

		lightShader.useProgram();
		lightShader.setMat4f("view", camera.getView());
		lightShader.setMat4f("projection", camera.getProjection());
	}*/
	return 0;
}