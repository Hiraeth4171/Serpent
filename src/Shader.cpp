#include "Shader.h"

#include <iostream>
#include <fstream> // replace with c code for reading files later for better perfromance
#include <string>
#include <sstream>

#include "Renderer.h"


Shader::Shader(const std::string& filepath) 
	: m_FilePath(filepath), m_RendererID(0)
{
    ShaderSource src = ParseShader(filepath);
    m_RendererID = CreateShader(src.VertexSource, src.FragmentSource);

}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderSource Shader::ParseShader(const std::string& file) {
    std::ifstream stream(file);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int res;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &res));
    if (res == GL_FALSE) {
        int len;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len));
        char* report = (char*)alloca(len * sizeof(char));
        GLCall(glGetShaderInfoLog(id, len, &len, report));

        std::cout << "Compilation failed - " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << std::endl << report << std::endl;
        GLCall(glDeleteShader(id));

        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    GLCall(int ColorUniformLocation = glGetUniformLocation(m_RendererID, name.c_str()));
    if (ColorUniformLocation == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist.\n";
    else
        m_UniformLocationCache[name] = ColorUniformLocation;
    return ColorUniformLocation;
}
