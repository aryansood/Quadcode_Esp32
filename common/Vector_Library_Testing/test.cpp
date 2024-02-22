#include<iostream>
#include<fstream>
#include</home/aryan/Desktop/Quadcode_Esp32/common/Vector_Library/Matrix.h>
using namespace std;

int main()
{
    ifstream inputfile("testing_in.txt");
    ofstream outputFile("output.txt");
    int num_of_testing;
    inputfile>>num_of_testing;
    if(num_of_testing == 1)
    {
        int num_cases;
        inputfile>>num_cases;
        for(int z = 0;z<num_cases;z++)
        {
            int a;
            int b;
            inputfile>>a;
            inputfile>>b;
            cout<<a<<"-"<<b<<" ";
            Matrix A(a,b);
            Matrix B(a,b);
            float sporco;
            for(int i = 0;i<a;i++)
            {
                for(int j = 0;j<b;j++)
                {
                    inputfile>>A[i][j];
                }
            }

            for(int i = 0;i<a;i++)
            {
                for(int j = 0;j<b;j++)
                {
                    inputfile>>B[i][j];
                }
            }

            for(int i = 0;i<a;i++)
            {
                for(int j = 0;j<b;j++)
                {
                    inputfile>>sporco;
                }
            }

            for(int i = 0;i<a;i++)
            {
                for(int j = 0;j<b;j++)
                {
                    inputfile>>sporco;
                }
            }
            Matrix C = A.add(B);
            Matrix D = A.sub(B);
            for(int i = 0;i<a;i++)
            {
                for(int j = 0;j<b;j++)
                {
                    outputFile<<C[i][j];
                    outputFile<<" ";
                }
                outputFile<<endl;
            }
            outputFile<<endl;

            for(int i = 0;i<a;i++)
            {
                for(int j = 0;j<b;j++)
                {
                    outputFile<<D[i][j];
                    outputFile<<" ";
                }
                outputFile<<endl;
            }
            outputFile<<endl;
         }
    }
    else if(num_of_testing == 2)
    {
        int num_cases;
        inputfile>>num_cases;
        for(int z = 0;z<num_cases;z++)
        {
            int a;
            int b;
            int c;
            inputfile>>a;
            inputfile>>b;
            inputfile>>c;
            cout<<a<<"-"<<b<<"-"<<c;
            Matrix A(a,b);
            Matrix B(b,c);
            float sporco;
            for(int i = 0;i<a;i++)
            {
                for(int j = 0;j<b;j++)
                {
                    inputfile>>A[i][j];
                }
            }

            for(int i = 0;i<b;i++)
            {
                for(int j = 0;j<c;j++)
                {
                    inputfile>>B[i][j];
                }
            }

            for(int i = 0;i<a;i++)
            {
                for(int j = 0;j<c;j++)
                {
                    inputfile>>sporco;
                }
            }

            Matrix C = A.mul(B);
            for(int i = 0;i<a;i++)
            {
                for(int j = 0;j<c;j++)
                {
                    outputFile<<C[i][j];
                    outputFile<<" ";
                }
                outputFile<<endl;
            }
            outputFile<<endl;
         }
    }
    return 0;
}