#pragma once

#include <GL/glew.h>
#include <string>

namespace KingPin
{
class GLSLProgram
{
public:
  GLSLProgram();
  ~GLSLProgram();

  // Creates vertex and fragment shader IDs and calls compileShader with the
  // filepaths
  void compileShaders(const std::string &vertexShaderFilePath,
                      const std::string &fragmentShaderFilePath);

  // Attaches the shaders to _programID, links the program, detaches the shaders
  // and deletes them.
  void linkShaders();

  // Binds an attribute location
  void addAttribute(const std::string &attributeName);

  // searches the shaders for uniformName and returns the ID
  GLuint getUniformLocation(const std::string &uniformName);

  // Uses the program and enables the vertex attribute arrays
  void use();
  // Ends the program and disables the vertex attribute arrays
  void unuse();

private:
  int _numAttributes;
  GLuint _programID, _vertexShaderID, _fragmentShaderID;

  // reads in the shader file in filePath and compiles them with id
  void compileShader(const std::string &filePath, const GLuint &id);
};

} // namespace KingPin