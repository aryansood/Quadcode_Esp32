class Vector3
{
    public:
    float x,y,z;
    float norm;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    void Norm()
    {
        norm = x*x+y*y+z*z;
    }

    Vector3 add(Vector3 other)
    {
        return Vector3(x+other.x, y+other.y,z+other.z);
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
};