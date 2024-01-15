# AbstractedGL
### About 
An ever in demand for features monstrocity which grows unpredictably in various directions. Or otherwise just an abstraction over the OpenGL functionalities with addition of various tools making working on the abstraction itself a bit more interesting. 
It is build in a way I hope one day could be called a general purpose graphic engine with at least most basic features that this genre is offering. 

#
### Currently supported features overview
Most of the libraries and features are integrated within the AGL environment making them unusable in the outside of AGL.

#### Entity component system
 An integrated package to manage the logic flow of the application by providing the end user with objects that can have properties assigned to it. Properties and sets of properties can be processed by systems in any given order. 
This approach comes with certain benefits, which apply mostly but not limited to  memory heavy applications, since each type of property is stored independently of other types in a contiguous array, hence the processor can utilize it's cache to preload next objects.

#### Layers
Layer represent the state in which the application is now operating. Layers are stored on a stack. Layers and layer trees can be added and removed on demand but are updated by AGL Core.

#### Unique Identifier
 An efficient system of unique identifiers which can be distributed in three possible applications:
- UID - new ID is assigned with constructor, call to destructor decreases reference count
- Static UID - new ID is assigned and destroyed on demand
- Type UID - new ID is assigned on demand, Type ID can be checked without registering it as possible ID (it is often used in types which do not expose their internal Type ID to the outside of it's class)

#### Logger
Simple utility to report five different types of logs to designated output streams. There are two basic types of loggers Core, which is used internally by the AbstractedGL, and Client, which is used by the developers of dependend applications.

#### Abstracted Editor
If you were to open the editor and hoped that you will see what the name suggests, you would be very dissapointed. As for the time in which development of AGL Core is tidious and irregular in terms of the attention payed to it, the Editor will remain the battleground on which the programmer will stand against its own code.

#### Debug
Boring stuff. Exceptions, asserts and macros (don't be thrown off by this - macros are nice to have sometimes)

#
### How to use?
However you want! 
Actually, it is a bit more difficult that I wrote before but we will get there.
In order to use the engine, you must create your application, which is nothing else that just initialization of the program's main loop. It is what the engine expects you to do. 
An AGL dependent application class must inherit from ```agl::application``` and can optionally override ```init()``` method, which is later called by AGL Core after the ```agl::create_application()``` is called. The last function is also provided by the developer of dependent app.
Here is a minimal example of the above.
```cpp
namespace my_app
{
	class my_application
		: public agl::application
	{
	public:
		virtual void init() override
		{
		    
		}
	};
}

namespace agl
{
	std::unique_ptr<application> create_application()
	{
		// Initialize OpenGL and AGL 
		window::init();
		window::set_opengl_api_version(4, 3);
		window::set_opengl_api_profile(OPENGL_CORE_PROFILE);

		auto wnd = window{};

		// Configure window properties
		wnd.create("Test app", { 1280, 1024 });

		// Initialize the application
		auto app = std::make_unique<my_app::my_application>();
		app->create(std::move(wnd));

		return app;
	}
}
```

For more information about the project or how to start getting into it, you should check Abstracted Editor directory.

