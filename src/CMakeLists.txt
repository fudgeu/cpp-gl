cmake_minimum_required(VERSION 3.25)

project(cppgl)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

include_directories(
	${SDL2_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
)

add_executable(cppgl 
		main.cpp
		render/render_system.cpp
		camera/camera.cpp
        mesh/mesh.cpp
		shader/mesh_shader.cpp
		shader/shader_registry.cpp
		entity/entity.cpp entity/entity.h
		entity/player.cpp entity/player.h
		event/key_event_handler.cpp event/key_event_handler.h object/object.cpp object/object.h mesh/shaded_mesh.h model/model.cpp model/model.h mesh/shaded_mesh.cpp world/world.cpp world/world.h model/model_factory.cpp model/model_factory.h
		texture/texture.cpp texture/texture.h extern/stb_image/stb_image.h extern/stb_image/stb_image.cpp
		engine.cpp
		model/bounding_box.cpp model/bounding_box.h vector/vec2d.h model/bound_checker.cpp model/bound_checker.h model/bound_result.h)

target_link_libraries(cppgl 
	SDL2::SDL2 
	GLEW::GLEW 
	OpenGL::GL 
	glm::glm
)

set_property(TARGET cppgl PROPERTY CXX_STANDARD 20)


