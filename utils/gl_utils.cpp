#include "gl_utils.h"

Shader::Shader(const char *vertex_path, const char *fragment_path) {
    // Read files
    std::string vertex_string, fragment_string;
    std::ifstream vertex_shader_file, fragment_shader_file;
    vertex_shader_file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    fragment_shader_file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try {
        vertex_shader_file.open(vertex_path);
        fragment_shader_file.open(fragment_path);
        std::stringstream vertex_stream, fragment_stream;
        vertex_stream << vertex_shader_file.rdbuf();
        fragment_stream << fragment_shader_file.rdbuf();
        vertex_shader_file.close();
        fragment_shader_file.close();
        vertex_string = vertex_stream.str();
        fragment_string = fragment_stream.str();
    } catch (std::ifstream::failure &e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char *vertex_code = vertex_string.c_str();
    const char *fragment_code = fragment_string.c_str();

    // Setup vertex shader
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_code, NULL);
    glCompileShader(vertex_shader);

    // Check the compilation of vertex shader
    Shader::check_errors(vertex_shader, "VERTEX");

    // Setup fragment shader
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_code, NULL);
    glCompileShader(fragment_shader);

    // Check the compilation of fragment shader
    Shader::check_errors(fragment_shader, "FRAGMENT");

    // Setup shader program
    Shader::id = glCreateProgram();
    glAttachShader(Shader::id, vertex_shader);
    glAttachShader(Shader::id, fragment_shader);
    glLinkProgram(Shader::id);

    // Check the linking of shader program
    Shader::check_errors(Shader::id, "PROGRAM");
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::use() {
    glUseProgram(Shader::id);
}

void Shader::destroy() {
    glDeleteProgram(Shader::id);
}

void Shader::check_errors(unsigned int shader, std::string type) {
    int success;
    char info_log[1024];
    if (type == "PROGRAM") {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, info_log);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << info_log
                      << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, info_log);
            std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n"
                      << info_log
                      << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
}