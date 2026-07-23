#pragma once

struct Quaternion {
    float w, x, y, z;

    Quaternion();
    Quaternion(const float all);
    Quaternion(const float x, const float y, const float z, const float w);

    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
};
