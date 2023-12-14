class Vector3
{
    public:
    float x,y,z;
    float norm;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {norm = 0;}

    void Norm()
    {
        norm = x*x+y*y+z*z;
    }

    Vector3 add(Vector3 other)
    {
        return Vector3(x+other.x, y+other.y,z+other.z);
    }

    Vector3 operator+(Vector3 other)
    {
        return add(other);
    }

    float dot(Vector3 other)
    {
        return (x*other.x+y*other.y+z*other.z);
    }

    Vector3 cross(Vector3 other)
    {
        float tmp_x, tmp_y, tmp_z;
        tmp_x = y*other.z-z*other.y;
        tmp_y = x*other.z-z*other.x;
        tmp_z = x*other.y-y*other.x;
        return Vector3(tmp_x,-tmp_y,tmp_z);
    }

    Vector3 operator*(Vector3 other)
    {
        return cross(other);
    }

    Vector3 scalar_prod(float mult_const)
    {
        return Vector3(mult_const*x, mult_const*y, mult_const*z);
    }
};