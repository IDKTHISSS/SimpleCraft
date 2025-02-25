cmake_minimum_required(VERSION 3.30)
project(SimpleVoxelEngine)

set(CMAKE_CXX_STANDARD 20)

set(ENGINE_VERSION_MAJOR 0)
set(ENGINE_VERSION_MINOR 0)
set(ENGINE_VERSION_PATCH 8)

# Убедитесь, что пути указаны правильно
set(SDL3_DIR "C:/Users/IDKTHIS/Desktop/SimpleVoxelEngine/Dependencies/SDL3")
set(GLEW_DIR "C:/Users/IDKTHIS/Desktop/SimpleVoxelEngine/Dependencies/Glew")
set(GLM_DIR "C:/Users/IDKTHIS/Desktop/SimpleVoxelEngine/Dependencies/GLM")
set(STB_DIR "C:/Users/IDKTHIS/Desktop/SimpleVoxelEngine/Dependencies/stb_image")
set(JSON_DIR "C:/Users/IDKTHIS/Desktop/SimpleVoxelEngine/Dependencies/JSON")
set(IMGUI_DIR "C:/Users/IDKTHIS/Desktop/SimpleVoxelEngine/Dependencies/ImGui")

find_path(SDL3_INCLUDE_DIR SDL3/SDL.h PATHS ${SDL3_DIR}/include)
find_path(GLM_INCLUDE_DIR glm/glm.hpp PATHS ${GLM_DIR}/include)
find_path(STB_INCLUDE_DIR stb_image.h PATHS ${STB_DIR}/include)
find_path(JSON_INCLUDE_DIR nlohmann/json.hpp PATHS ${JSON_DIR}/include)
find_path(IMGUI_INCLUDE_DIR imgui.h PATHS ${IMGUI_DIR}/include)

set(SDL3_LIB "${SDL3_DIR}/lib/x64/SDL3.lib")
set(SDL3_DLL "${SDL3_DIR}/lib/x64/SDL3.dll")

find_path(GLEW_INCLUDE_DIR GL/glew.h PATHS ${GLEW_DIR}/include)
set(GLEW_LIB "${GLEW_DIR}/lib/Release/x64/glew32s.lib")

# Добавляем исходники ImGui с поддержкой SDL3 и OpenGL3
set(IMGUI_SRC
        ${IMGUI_INCLUDE_DIR}/imgui.cpp
        ${IMGUI_INCLUDE_DIR}/imgui_demo.cpp
        ${IMGUI_INCLUDE_DIR}/imgui_draw.cpp
        ${IMGUI_INCLUDE_DIR}/imgui_tables.cpp
        ${IMGUI_INCLUDE_DIR}/imgui_widgets.cpp
        ${IMGUI_INCLUDE_DIR}/backends/imgui_impl_sdl3.cpp
        ${IMGUI_INCLUDE_DIR}/backends/imgui_impl_opengl3.cpp
)

# Создаём статическую библиотеку ImGui
add_library(imgui STATIC ${IMGUI_SRC})

# Указываем зависимости для ImGui
target_include_directories(imgui PRIVATE
        ${IMGUI_INCLUDE_DIR}
        ${SDL3_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
)
target_link_libraries(imgui PRIVATE ${SDL3_LIB})

# Основной исполняемый файл
add_executable(SimpleVoxelEngine
        EntryPoint.cpp
        Engine/Application.cpp
        Engine/Application.h
        Engine/Platform/Window/Window.h
        Engine/Platform/GraphicsAPI/APIContext.h
        Engine/Platform/GraphicsAPI/OpenGL/GLShader.cpp
        Engine/Platform/GraphicsAPI/OpenGL/GLShader.h
        Engine/Platform/GraphicsAPI/OpenGL/GLTexture.cpp
        Engine/Platform/GraphicsAPI/OpenGL/GLTexture.h
        Engine/Platform/GraphicsAPI/OpenGL/GLContext.cpp
        Engine/Platform/GraphicsAPI/OpenGL/GLContext.h
        Engine/Core/SubSystems/WindowInput/WindowInputComponent.cpp
        Engine/Core/SubSystems/WindowInput/WindowInputComponent.h
        Engine/World/World.cpp
        Engine/World/World.h
        Engine/World/Generators/BaseWorldGenerator.cpp
        Engine/World/Generators/BaseWorldGenerator.h
        Engine/Platform/Window/SDLWindow/Window_SDL.cpp
        Engine/Platform/Window/SDLWindow/Window_SDL.h
        Engine/Core/SubSystems/Console/SimpleConsole.cpp
        Engine/Core/SubSystems/Console/SimpleConsole.h
        Engine/Core/SubSystems/CommandLineParse/CommandLineParse.h
)

# Подключаем заголовочные файлы
target_include_directories(SimpleVoxelEngine PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${SDL3_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
        ${STB_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
        ${IMGUI_INCLUDE_DIR}
)

# Линкуем зависимости
target_link_libraries(SimpleVoxelEngine PRIVATE
        ${GLEW_LIB}
        opengl32
        ${SDL3_LIB}
        imgui
)

# Добавляем системные библиотеки, необходимые для SDL3 в Windows
if(WIN32)
    target_link_libraries(SimpleVoxelEngine PRIVATE
            user32.lib
            shell32.lib
            advapi32.lib
            imm32.lib
            setupapi.lib
            version.lib
    )
endif()

# Копируем DLL файл SDL3
add_custom_command(TARGET SimpleVoxelEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL3_DLL} $<TARGET_FILE_DIR:SimpleVoxelEngine>
)

# Версия движка
set(ENGINE_VERSION "${ENGINE_VERSION_MAJOR}.${ENGINE_VERSION_MINOR}.${ENGINE_VERSION_PATCH}")
add_definitions(-DENGINE_VERSION="${ENGINE_VERSION}")