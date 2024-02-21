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

    Pair(T f, U s) : first(f), second(s){}
};

float abs(int a) {return ((a>=0) ? a : -a);}

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
        for(int i = 0;i<num;i++)
        {
            for(int j = 0;j<num;j++) m[i][j] = 0.0;
        }
        for(int i = 0;i<num;i++) m[i][i] = 1.0;
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

    float* operator[](int index) {
        return m[index];
    }

    void Insert(float a, int i, int j)
    {
        if(i<num_row && j<num_col) m[i][j] = a;
    }

    Matrix add(Matrix other)
    {
        if(other.num_row == num_row && other.num_col == num_col)
        {
            Matrix ret_mat = Matrix(num_row,num_col);
            for(int i = 0;i<num_row;i++)
            {
                for(int j = 0;j<num_col;j++) ret_mat[i][j] = m[i][j]+other[i][j];
            }
            return ret_mat;
        }
    }

    void row_exchange(int i, int j)
    {
        if(i<num_row && j<num_row && i!=j)
        {
            Matrix single_row(1,num_col);
            for(int z = 0;z<num_col;z++) single_row[0][z] = m[i][z];

            for(int z = 0;z<num_col;z++) m[i][z] = m[j][z];

            for(int z = 0;z<num_col;z++) m[j][z] = single_row[0][z];
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
                    ret_mat[i][j] = 0.0;
                    for(int z = 0;z<num_col;z++)
                    {
                        ret_mat[i][j] += m[i][z]+other[z][j];
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
                ret_mat[j][i] = m[i][j];
            }
        }
        return ret_mat;
    }

    Pair<Matrix, Matrix> PLU_dec()
    {
        Matrix A(num_row, num_col);
        Matrix P(num_row);
        int size_m = num_row;
        for(int i = 0;i<num_row;i++)
        {
            for(int j = 0;j<num_col;j++)
            {
                A[i][j] = m[i][j];
            }
        }

        for(int k = 0;k<size_m-1;k++)
        {
            int max_r = k;
            for(int r  = k+1;r<size_m;r++)
            {
                if(abs(A[r][k]) > abs(A[max_r][k])) max_r = r;
            }
            A.row_exchange(k,max_r);
            P.row_exchange(k,max_r);
            for(int i = k+1;i<size_m;i++)
            {
                //We are now going to do l[i][k] which is the lower triangular matrix
                A[i][k] = A[i][k]/A[k][k];
                for(int j = k+1;j<size_m;j++)
                {
                    A[i][j] = A[i][j]-A[i][k]*A[k][j];
                }
            }
        }
        return {P,A};
    }

    Matrix Solver(Matrix B)
    {  
        Pair<Matrix, Matrix> LU_decomp = PLU_dec();
        Matrix P = LU_decomp.first;
        Matrix A = LU_decomp.second;
        Matrix x(A.num_col, B.num_col);
        Matrix y(A.num_col, B.num_col);
        if(B.num_row == P.num_col)
        {
            int num_of_solving = B.num_col;
            int num_size = A.num_row;
            Matrix t1 = P.mul(B);
            
            for(int s = 0;s<num_of_solving;s++)
            {
                y[0][s] = B[0][s];
                for(int i =1;i<num_size;i++)
                {
                    y[i][s] = B[i][s];
                    for(int j = 0;j<i;j++) y[i][s]+=-(A[i][j]*y[j][s]);
                }
            }

            for(int s = 0;s<num_of_solving;s++)
            {
                x[num_size-1][s] = y[num_size-1][s]/A[num_size-1][num_size-1];
                for(int i =num_size-2;i>=0;i--)
                {
                    x[i][s] = y[i][s];
                    for(int j = i+1;j<num_size;j++) x[i][s]+=-(A[i][j]*x[j][s]);
                    x[i][s] = x[i][s]/A[i][i];
                }
            }
        }
      //Assertion not valid;
    }

    Matrix inverse()
    {
        int get_size = num_row;
        Matrix I_M(get_size);
        return Solver(I_M);
    }
};