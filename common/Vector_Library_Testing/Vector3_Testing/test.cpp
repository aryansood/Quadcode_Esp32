#include<iostream>
#include<fstream>
#include</home/aryan/Desktop/Quadcode_Esp32/common/Vector_Library/Vector3.h>
#include <iomanip>
using namespace std;

int main()
{
    ifstream inputfile("testing_in.txt");
    ofstream outputFile("output.txt");
    int num_test;
    inputfile>>num_test;
    for(int i = 0;i<num_test;i++)
    {
        Vector3 s1(0,0,0);
        Vector3 s2(0,0,0);
        Vector3 s3(0,0,0);
        Vector3 s4(0,0,0);
        Vector3 s5(0,0,0);
        double s6 = 0;
        inputfile>>s1.x;
        inputfile>>s1.y;
        inputfile>>s1.z;
        inputfile>>s2.x;
        inputfile>>s2.y;
        inputfile>>s2.z;
        double sporco;
        for(int i = 0;i<10;i++) inputfile>>sporco;
        s3 = s1+s2;
        s4 = s1-s2;
        s5 = s1*s2;
        s6 = s1.dot(s2);
        outputFile<<s3.x;
        outputFile<<endl;
        outputFile<<s3.y;
        outputFile<<endl;
        outputFile<<s3.z;
        outputFile<<endl;
        outputFile<<endl;
        outputFile<<s4.x;
        outputFile<<endl;
        outputFile<<s4.y;
        outputFile<<endl;
        outputFile<<s4.z;
        outputFile<<endl;
        outputFile<<endl;
        outputFile<<s5.x;
        outputFile<<endl;
        outputFile<<s5.y;
        outputFile<<endl;
        outputFile<<s5.z;
        outputFile<<endl;
        outputFile<<endl;
        outputFile<<s6;
        outputFile<<endl;
        outputFile<<endl;
    }
    return 0;
}