#pragma once

struct Quaternion {
    float w, x, y, z;

    Quaternion();
    Quaternion(float all);
    Quaternion(float w, float x, float y, float z);

    void Conjugate();


    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
};
