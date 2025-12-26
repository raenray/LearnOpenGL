add_executable(LearnOpenGLApp
    # src/main.cpp
    src/Application.cpp
)

target_link_libraries(LearnOpenGLApp PRIVATE
    engine
)
