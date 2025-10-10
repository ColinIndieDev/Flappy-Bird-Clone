#pragma once

#include <string>
#include "CPLib.h"

class Shader
{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);

    void Use() const;
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetColor(const std::string &name, const Color& color) const;
private:
    static void CheckCompileErrors(unsigned int shader, const std::string& type);
};