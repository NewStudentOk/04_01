#include <iostream>
#include <fstream>


class Address{
private:
    std::string city;
    std::string street;
    int house;
    int appart;
public:
    Address(){
        this->house = 0;
        this->appart = 0;
    }

    bool setCity(std::string City){
        if(City ==""){
            return false;
        } else{
            city = City;
            return true;
        }
    }
    bool setStreet(std::string Street){
        if(Street ==""){
            return false;
        } else{
            street = Street;
            return true;
        }
    }
    bool setHouse(int House){
        if(House <= 0){
            return false;
        } else{
            house = House;
            return true;
        }
    }
    bool setAppart(int Appart){
        if(Appart <= 0){
            return false;
        } else{
            appart = Appart;
            return true;
        }
    }

    std::string getCity(){
        return city;
    }
    std::string getStreet(){
        return street;
    }
    int getHouse(){
        return house;
    }
    int getAppart(){
        return appart;
    }
};

void delMEM(Address*& address)
{
    if (address)
    {
        delete[] address;
        address = nullptr;
    }
}

int main(int argc, char** argv) {
    int addressCount=0;
    Address* address = nullptr;
    std::ifstream file("in.txt");
    if (file.is_open())
    {

        if ((file >> addressCount) && addressCount > 0)
        {
            address = new Address[addressCount];
            for (int i = 0; i < addressCount; ++i)
            {
                std::string str;
                int intVal;
                if (!(file >> str && address[i].setCity(str) &&
                      file >> str && address[i].setStreet(str) &&
                      file >> intVal && address[i].setHouse(intVal) &&
                      file >> intVal && address[i].setAppart(intVal)))
                {
                    delMEM(address);
                    break;
                }
            }
        }
        else {
            std::cout << "Ошибка чтения файла" << std::endl;
        }

        file.close();
    }
    else {
        std::cout << "Ошибка открытия файла" << std::endl;
    }

    // пишу в файл
    std::ofstream file_wr("out.txt");
    if (file_wr.is_open())
    {
        if (address)
        {
            file_wr << addressCount << std::endl;
            for (int i = addressCount-1; i >= 0; --i)
            {
                file_wr << address[i].getCity() << ", "
                        << address[i].getStreet() << ", "
                        << address[i].getHouse() << ", "
                        << address[i].getAppart() << std::endl;
            }
            std::cout << "Смотри файл: out.txt" << std::endl;
        }
        else
            std::cout << "Ошибка" << std::endl;

        file_wr.close();
    }
    else std::cout << "Не удалось сохранить файл: out.txt" << std::endl;

    delMEM(address);
    return 0;
}
