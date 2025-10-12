
#include <iostream>

#define NAME_MAX_LENGTH 64

struct
{
    char name[NAME_MAX_LENGTH];
    unsigned int age;
    float weight;
    float height;
} typedef Patient;

void printHeader();
Patient *getPatientInfo();
void printSeparator();
void printPatientInfo(Patient *patient);
float calculateIMC(Patient *patient);
void printIMCRating(const float imc);
bool shouldCloseProgram();

int main()
{
    while (true)
    {
        printHeader();

        Patient *patient = getPatientInfo();
        printPatientInfo(patient);
        delete patient;

        if (shouldCloseProgram())
            break;
    }

    return 0;
}

void printHeader()
{
    printSeparator();
    std::cout << "\tCalculadora de IMC\n";
    printSeparator();
}

Patient *getPatientInfo()
{
    Patient *patient = new Patient();

    std::cout << "Ingresa el nombre: ";
    std::cin >> patient->name;

    std::cout << "Ingresa la edad: ";
    std::cin >> patient->age;

    std::cout << "Ingresa el peso(kg): ";
    std::cin >> patient->weight;

    std::cout << "Ingresa la estatura(m): ";
    std::cin >> patient->height;

    return patient;
}

void printPatientInfo(Patient *patient)
{
    printSeparator();

    std::cout << "Nombre: " << patient->name << '\n';
    std::cout << "Edad: " << patient->age << '\n';
    std::cout << "Peso: " << patient->weight << "kg\n";
    std::cout << "Estatura: " << patient->height << "m\n";

    printSeparator();

    float imc = calculateIMC(patient);
    std::cout << "\tIMC: " << imc << '\n';
    std::cout << "\t";
    printIMCRating(imc);

    printSeparator();
}

float calculateIMC(Patient *patient)
{
    return patient->weight / (patient->height * patient->height);
}

void printIMCRating(const float imc)
{
    if (imc < 18.5)
    {
        std::cout << "Estas bien seco carnal\n";
    }
    else if (imc < 25)
    {
        std::cout << "Peso normal\n";
    }
    else if (imc < 30)
    {
        std::cout << "Sobrepeso\n";
    }
    else if (imc < 35)
    {
        std::cout << "Obesidad leve\n";
    }
    else if (imc < 40)
    {
        std::cout << "Obesidad media\n";
    }
    else
    {
        std::cout << "Aimep3\n";
    }
}

bool shouldCloseProgram()
{
    char answer;
    std::cout << "Continuar(Y/N)? ";
    std::cin >> answer;
    return (answer != 'Y' && answer != 'y');
}

void printSeparator()
{
    std::cout << "--------------------------------------\n";
}