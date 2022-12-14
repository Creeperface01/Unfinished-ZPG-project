#pragma once

#include "../../util/debug.h"
#include "../../util/Noncopyable.h"

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include <utility>
#include <type_traits>
#include <unordered_map>
#include <initializer_list>
#include <exception>
#include <tuple>

template<typename T>
struct always_false : std::false_type {
};

template<typename T>
concept supported_type = std::is_scalar_v<T> || std::is_same_v<T, glm::vec3> || std::is_same_v<T, glm::mat4>;

template<supported_type T>
class UniformVariable : public Noncopyable {
private:
    GLint _id = -1;
    std::string _name;

    UniformVariable(GLuint programId, std::string name)
            : _name(std::move(name)) {
        _id = debugGlCall(glGetUniformLocation, programId, _name.c_str());
//        assert(_id >= 0 && "Invalid uniform variable");
    }

    void checkExists() const {
        if(_id < 0) {
//            throw std::runtime_error("Cannot write to non-existing uniform variable '" + _name + "'");
        }
    }

public:
    virtual ~UniformVariable() = default;

    UniformVariable<T> &operator=(UniformVariable<T> &&)  noexcept = default;

    UniformVariable(UniformVariable &&)  noexcept = default;

    UniformVariable(std::string name, GLuint programId) : UniformVariable(programId, std::move(name)) {
    }

    UniformVariable &operator=(const T &value) {
        static_assert(always_false<T>::value);
    }

};

template<>
UniformVariable<GLint> &UniformVariable<GLint>::operator=(const GLint &value);

template<>
UniformVariable<GLuint> &UniformVariable<GLuint>::operator=(const GLuint &value);

template<>
UniformVariable<GLfloat> &UniformVariable<GLfloat>::operator=(const GLfloat &value);

template<>
UniformVariable<glm::vec3> &UniformVariable<glm::vec3>::operator=(const glm::vec3 &value);

template<>
UniformVariable<glm::mat4> &UniformVariable<glm::mat4>::operator=(const glm::mat4 &value);

template<>
UniformVariable<GLboolean> &UniformVariable<GLboolean>::operator=(const GLboolean &value);

template<typename T>
concept struct_or_class = std::is_class_v<T>;

template<struct_or_class T>
class StructUniformVariable : public UniformVariable<T> {
public:

};

template<typename T>
concept array_type = std::is_array_v<T>;

template<array_type T>
class ArrayUniformVariable : public UniformVariable<T> {

};

//template<>
//UniformVariable<glm::vec3>::UniformVariable(std::string name, GLuint programId)
//        : UniformVariable(programId, std::move(name)) {
//
//}
//
//template<>
//UniformVariable<glm::mat4>::UniformVariable(std::string name, GLuint programId)
//        : UniformVariable(programId, std::move(name)) {
//
//}


