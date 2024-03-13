#include <iostream>
#include <vector>
#include<fstream>
using  namespace  std;

//bool isSTLBinary(const char* fileName);
//void openBinaryFile(std::string fileName, std::vector<float>& positions, std::vector<float>& normals);
//
//int main() {
//    setbuf(stdout, NULL);
//    vector<float> positions;
//    vector<float> normals;
//    char * path = "C:\\Users\\25137\\Desktop\\STLReader\\single.stl";
//    openBinaryFile(path, positions, normals);
//    const int rows = positions.size() / 9;
//    cout << positions.size() / 9 << " " << normals.size() / 9 << endl;
//
//    float ** p = new float * [rows];
//    for(int i = 0; i < rows; i++)
//        p[i] = new float [3];
//
//    cout << positions[299] << endl;
//
//    for(int i = 0, n = 0, m = 0; i < positions.size() / 3; i++)
//    {
//        if(i !=0 && i % 3 == 0) n ++,m = 0;
//        p[n][m++] = positions[i];
//    }
//
//    cout << p[99][0] << endl;
//    for(int i = 0; i < 100; i++)
//    {
//        for(int j = 0; j < 3; j++)
//        {
//            cout << p[i][j] << " ";
//        }
//
//        cout << endl;
//    }
//    return 0;
//
//
//}
//
//void openBinaryFile(std::string fileName, std::vector<float>& positions, std::vector<float>& normals)
//{
//    FILE *fp = fopen(fileName.c_str(), "rb");
//    int numFacet;
//    //int error= fopen_s(&fp,fileName, "rb");
//
//    float normal[3];
//    float point1[3];
//    if (fp)//成功打开文件
//    {
//        fseek(fp, 80, SEEK_SET);//跳过开头
//        size_t t = fread(&numFacet, sizeof(int), 1, fp);//读取facet的数目
//        for (int facetIndex = 0; facetIndex < numFacet;++facetIndex)
//        {
//            unsigned short attr; //用来储存属性,实际上把这个值丢弃了
//            t = fread(normal, sizeof(float), 3, fp);//读取facet的法向量
//            for (int i = 0; i < 3;++i)
//            {
//                t = fread(point1, sizeof(float), 3, fp);//读取vertex
//                positions.push_back(point1[0]);
//                positions.push_back(point1[1]);
//                positions.push_back(point1[2]);
//                normals.push_back(normal[0]);
//                normals.push_back(normal[1]);
//                normals.push_back(normal[2]);
//            }
//            t = fread(&attr, sizeof(unsigned short), 1, fp);//读取属性
//        }
//    }
//    else
//    {
//        printf("%s open fail\n", fileName.c_str());
//    }
//    fclose(fp);
//}
//
//
//bool isSTLBinary(const char* fileName)
//{
//    bool isBinary = false;//return value
//    FILE *fp = fopen(fileName, "r");
//    //int errorCode = fopen_s(&fp, fileName, "r");
//
//    // #ifdef __unix
//    // #define fopen_s(pFile,filename, "r") ((*(pFile))=fopen((fileName),  ("r")))==NULL
//    // #endif
//
//    if (fp)//成功打开文件
//    {
//        printf("%s isSTLBinary open success\n", fileName);
//        //确定文件实际大小
//        fseek(fp, 0, SEEK_END);//将fp移动到文件尾部
//        int fileSize = ftell(fp);//返回文档首部到fp位置大小（bytes）
//        int facetNum;
//        //计算标准stl二进制文件的大小
//        fseek(fp, 80, SEEK_SET);//跳过文档开头的注释
//        size_t t = fread(&facetNum, sizeof(int), 1, fp);//读取facet的数目并保存在facetNum中
//        int standardBinaryFileSize = 80 + sizeof(int) + facetNum * 50;
//        //判断是否是标准stl文件
//        if (fileSize == standardBinaryFileSize)
//        {
//            isBinary = true;
//        }
//        //判断是否是非标准stl文件
//        unsigned char tmpbuf[128];//如果文件过短，这里会有Bug
//        t = fread(tmpbuf, sizeof(tmpbuf), 1, fp);//读取128个char大小的数据
//        for (unsigned int i = 0;i<sizeof(tmpbuf);i++)
//        {
//            //char类型取值范围是-128~127,如果是ASCII格式，应该全是char
//            if (tmpbuf[i]>127)
//            {
//                isBinary = true;
//                break;
//            }
//        }
//        fclose(fp);
//        printf("t=%d\n", (int)t);
//    }
//    else
//    {
//        printf("%s isSTLBinary open file fail\n", fileName);
//    }
//    return isBinary;
//}

bool readSTL_Binary(std::string fileName, std::vector<float>& positions)
{
    ifstream ifs(fileName.c_str(), ios::binary);
    if (!ifs)
    {
        ifs.close();
        cout << "read stl error" << endl;
        return false;
    }

    int intSize = sizeof(int);
    int floatSize = sizeof(float);
    ifs.ignore(80);

    // 面的个数
    int num_tris;
    ifs.read((char*)(&num_tris), intSize);
    cout << "面片数量：" << num_tris << endl;

    float tn0, tn1, tn2;
    float v0, v1, v2;

    for (int i = 0; i < num_tris; i++)
    {

        // 法向量
        ifs.read((char*)(&tn0), floatSize);
        ifs.read((char*)(&tn1), floatSize);
        ifs.read((char*)(&tn2), floatSize);

        // 面片的第一个点坐标
        ifs.read((char*)(&v0), floatSize);
        ifs.read((char*)(&v1), floatSize);
        ifs.read((char*)(&v2), floatSize);
        positions.push_back(v0);
        positions.push_back(v1);
        positions.push_back(v2);

        // 面片的第二个点坐标
        ifs.read((char*)(&v0), floatSize);
        ifs.read((char*)(&v1), floatSize);
        ifs.read((char*)(&v2), floatSize);
        positions.push_back(v0);
        positions.push_back(v1);
        positions.push_back(v2);

        // 面片的第三个点坐标
        ifs.read((char*)(&v0), floatSize);
        ifs.read((char*)(&v1), floatSize);
        ifs.read((char*)(&v2), floatSize);
        positions.push_back(v0);
        positions.push_back(v1);
        positions.push_back(v2);

        ifs.ignore(2);
    }
    ifs.close();
    return true;
}

int main()
{
    setbuf(stdout, NULL);
    vector<float> positions;
    char * path = "C:\\Users\\25137\\Desktop\\STLReader\\single.stl";
    readSTL_Binary(path,positions);

    const int rows = positions.size() / 3;
    float ** points = new float * [rows];
    for(int i = 0; i < rows; i++) points[i] = new float [3];

    for(int i = 0, n = 0, m = 0; i < positions.size(); i++)
    {
        if(i != 0 && i % 3 == 0) n ++, m = 0;
        points[n][m ++] = positions[i];
    }

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cout << points[i][j] << " ";
        }
        cout << endl;
    }
}
