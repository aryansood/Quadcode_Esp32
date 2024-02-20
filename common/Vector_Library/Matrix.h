/*
Matrix def, op: sum, mult, inverse(square), SVD, Identity matrix, constant multip, vector multi.
*/
/*
For Quaternion multiplication just create a a matrix and then just pass the value and reget original matrix.
*/

template <typename T, typename U>
struct Pair {
    T first;
    U second;

    Pair(const T& f, const U& s) : first(f), second(s){}
};

class Matrix
{
public:
    int num_row;
    int num_col;
    float ** m;

    //Identity Matrix
    Matrix (int num)
    {
        num_row = num;
        num_col = num;
        m = new float*[num];
        for(int i = 0;i<num;i++) m[i] = new float[num];
        for(int i = 0;i<num_row;i++)
        {
            for(int j = 0;j<num_col;j++) m[i][j] = 1.0;
        }
    }

    Matrix (int rs, int cs)
    {
        num_row = rs;
        num_col = cs;
        m = new float*[rs];
        for(int i = 0;i<rs;i++) m[i] = new float[cs];
        for(int i = 0;i<num_row;i++)
        {
            for(int j = 0;j<num_col;j++) m[i][j] = 0.0;
        }
    }

    Matrix add(Matrix other)
    {
        if(other.num_row == num_row && other.num_col == num_col)
        {
            Matrix ret_mat = Matrix(num_row,num_col);
            for(int i = 0;i<num_row;i++)
            {
                for(int j = 0;j<num_col;j++) ret_mat.m[i][j] = m[i][j]+other.m[i][j];
            }
            return ret_mat;
        }
    }

    Matrix mul(Matrix other)
    {
        if(num_col == other.num_row)
        {
            Matrix ret_mat = Matrix(num_row, other.num_col);
            for(int i = 0;i<num_row;i++)
            {
                for(int j = 0;j<other.num_col;j++)
                {
                    ret_mat.m[i][j] = 0.0;
                    for(int z = 0;z<num_col;z++)
                    {
                        ret_mat.m[i][j] += m[i][z]+other.m[z][j];
                    }
                }
            }
            return ret_mat;
        }
    }

    Matrix Tran()
    {
        Matrix ret_mat = Matrix(num_col,num_row);
        for(int j = 0;j<num_col;j++)
        {
            for(int i = 0;i<num_row;i++)
            {
                ret_mat.m[j][i] = m[i][j];
            }
        }
        return ret_mat;
    }

    //LU decomposition in an inteligent way can be used to find The K matrix of the Kalman Filter
    //We will do LU and solve system of equation + inverse with using 

    Pair<Matrix, Matrix> PLU_dec()
    {
        Matrix A(num_row, num_col);
        Matrix P(num_row);
        for(int i = 0;i<num_row;i++)
        {
            for(int j = 0;j<num_col;j++)
            {
                A.m[i][j] = m[i][j];
            }
        }

        //for() Read code and implement
    }
    

        
};