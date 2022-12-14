#pragma once

#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace ModelConverter {

    void convert(
            const float *data,
            size_t dataSize,
            std::vector<glm::vec3> &vertices,
            std::vector<glm::vec3> &normals
    );

    void convert(
            const float *data,
            size_t dataSize,
            std::vector<glm::vec3> &vertices,
            std::vector<glm::vec3> &normals,
            std::vector<glm::vec2> &uvs
    );

    void convertDataToVector(
            const float *data,
            size_t dataSize,
            std::vector<glm::vec3> &vector
    );
};
