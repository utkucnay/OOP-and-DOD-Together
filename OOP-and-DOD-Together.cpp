#include<stdio.h>
#include<stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

class Apartment
{
public:
    float light;
    char* ApartOwnerName = new char[100];

    float apartNumber;
    Apartment(float light , float apartNumber)
    {
        this->light = light;
        this->apartNumber = apartNumber;
    }
    Apartment()
    {
        light = 0;
        apartNumber = -1;
    }
};

class ApartmentDOD
{
public:
    float* light;
    char* ApartOwnerName = new char[100];
    float apartNumber;
    ApartmentDOD(float* light)
    {
        this->light = light;
    }
    ApartmentDOD()
    {
        light = nullptr;
        apartNumber = -1;
    }
};

class Structure
{
public:
    char* StructureName = new char[100];
    char* StructureColor = new char[100];
    Apartment* Apartments = new Apartment[5];
};

class StructureDOD
{
public:
    char* StructureName = new char[100];
    char* StructureColor = new char[100];
    ApartmentDOD* Apartments = new ApartmentDOD[5];
};

struct ApartNameData {
    char* ApartOwnerName = new char[100];
};

struct ApartData
{
    ApartData(int N)
    {
        //we split memory for cache line
        lights->resize(N);
        ApartNames->resize(N);
    }
    vector<float>* lights = new vector<float>;
    vector<ApartNameData>* ApartNames = new vector<ApartNameData>;
};

int main() {
    vector<Structure*>* Structures = new vector<Structure*>();
    int N = 1000000*2;
    Structures->resize(N/5);

    //OOP
    clock_t tStart = clock();
    for (int i = 0; i < N/5; i++)
    {
        Structure* structure = new Structure();

        Apartment* Apart1 = new Apartment();
        Apartment* Apart2 = new Apartment();
        Apartment* Apart3 = new Apartment();
        Apartment* Apart4 = new Apartment();
        Apartment* Apart5 = new Apartment();

        structure->Apartments[0] = *Apart1;
        structure->Apartments[1] = *Apart2;
        structure->Apartments[2] = *Apart3;
        structure->Apartments[3] = *Apart4;
        structure->Apartments[4] = *Apart5;

        Structures->at(i) = structure;
    }

    printf("structure creater Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    tStart = clock();

    for (int b = 0; b < N / 5; b++)
    {
        for (int i = 0; i < 5; i++)
        {
            Structures->at(b)->Apartments[i].light = 5;
        }
    }

    printf("Set Light OOP Time taken: %.4fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    //DOD
    tStart = clock();
    ApartData* apartData = new ApartData(N);

    printf("ApartData creater Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    tStart = clock();
    for (int i = 0; i < N; i++)
    {
        apartData->lights->at(i) = 5;
    }

    printf("Set Light DOD Time taken: %.4fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    //DOD and OOP together
    vector<StructureDOD*>* StructuresDOD = new vector<StructureDOD*>();
    StructuresDOD->resize(N / 5);

    ApartData* apartDataForOOP = new ApartData(N);

    tStart = clock();
    for (int i = 0; i < N / 5; i++)
    {
        StructureDOD* structure = new StructureDOD();

        ApartmentDOD* Apart1 = new ApartmentDOD(&apartDataForOOP->lights->at(i * 5));
        ApartmentDOD* Apart2 = new ApartmentDOD(&apartDataForOOP->lights->at(i * 5 + 1));
        ApartmentDOD* Apart3 = new ApartmentDOD(&apartDataForOOP->lights->at(i * 5 + 2));
        ApartmentDOD* Apart4 = new ApartmentDOD(&apartDataForOOP->lights->at(i * 5 + 3));
        ApartmentDOD* Apart5 = new ApartmentDOD(&apartDataForOOP->lights->at(i * 5 + 4));

        structure->Apartments[0] = *Apart1;
        structure->Apartments[1] = *Apart2;
        structure->Apartments[2] = *Apart3;
        structure->Apartments[3] = *Apart4;
        structure->Apartments[4] = *Apart5;

        StructuresDOD->at(i) = structure;
    }

    printf("DOD and OOP together create class Time taken: %.4fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    tStart = clock();
    
    for (int b = 0; b < N; b++)
    {
        apartDataForOOP->lights->at(b) = 5;
    }
    
    printf("DOD and OOP together set light Time taken: %.4fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}
