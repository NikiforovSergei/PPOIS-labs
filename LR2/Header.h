#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;


class Input_Choice{
    public:
    Input_Choice() {
        cout << "1 - Ввод из файла." << endl << "2 - Ввод рандомно." << endl;
        cin >> input_choice;
        if(input_choice == 1){
            read_from_file = true;
        }else if (input_choice == 2){
            read_from_file = false;
        }
        if(read_from_file == true){

            ifstream inFile;
            inFile.exceptions(ifstream::badbit | ifstream::failbit);
            try{

                inFile.open("file.txt");
                cout << "ФАЙЛИК" << endl;
            }
            catch(const std::exception & ex)
            {
                cout << ex.what() << endl;
                cout << "Ошибка открытия файла((";
            }

            
            inFile >> route_amount_of_stations; //количество станций

            route = new int*[route_amount_of_stations];
            for(int i=0; i<route_amount_of_stations; i++){     
		        route[i] = new int[2];
            }

            for(int i = 0; i < route_amount_of_stations; i++){
                for(int j = 0; j < 2; j++){
                    
                    inFile >> route[i][j];

                }
            
            }


            inFile >> amount_of_connections;

            connections = new int*[amount_of_connections];
            for(int i=0; i<amount_of_connections; i++){     
		    connections[i] = new int[3];
            }

            for(int i = 0; i < amount_of_connections; i++){
                for(int j = 0; j < 3; j++){
                    inFile >> connections[i][j];
                
                }
         
            }

        }
    };
    ~Input_Choice() {};
    protected:
    int input_choice;
    bool read_from_file;
    int route_amount_of_stations;
    int amount_of_connections;
    int **route;
    int **connections;

};

class Carriage{
    public:
    virtual void Carriage_Type() = 0;

};
class Carriage_Products : public Carriage{
    public:
    void Carriage_Type()
    {
        printf("Вагон является товарным.\n");
    }

};
class Carriage_Passengers : public Carriage{
    public:
    void Carriage_Type()
    {
        printf("Вагон является пассажирским.\n");
    }

};
class Player{
    public:
    void Carriage_Type(Carriage *carriage)
    {
        carriage->Carriage_Type();
    }
};

class Station {
    public:
    Station() {};
    ~Station() {};


    protected:
};
class Station_Products : public Station {
    public:
    Station_Products(int n){
        printf("Станция №%d является товарной.\n", n+1);
    };
    ~Station_Products() {};


    private:

};
class Station_Passengers : public Station {
    public:
    Station_Passengers(int n){
        printf("Станция №%d является пассажирской.\n", n+1);
    };
    ~Station_Passengers() {};


    private:
};
class Station_Products_Passengers : public Station {
    public:
    Station_Products_Passengers(int n){
        printf("Станция №%d является пассажирско-товарной.\n", n+1);
    };
    ~Station_Products_Passengers() {};


    private:

};
class Locomotive{
    public:
    Locomotive(int pulling_force, int speed, int service_life, int number_of_carriages){
        this->pulling_force = pulling_force;
        cout << "Тяговая сила локомотива равна: " << pulling_force << endl;
        this->speed = speed;
        int changed_speed;
        changed_speed = speed - 3 * number_of_carriages;
        cout << "Скорость локомотива равна: " << changed_speed << endl;
        this->service_life = service_life;
        cout << "Срок службы локомотива: " << pulling_force << endl;
    };
    int Speed(){

        return this->changed_speed;
    }
    ~Locomotive() {};
    //смесь вагонов и локомотивов

    private:
    int pulling_force; //тяговая сила
    int speed; //скорость
    int service_life; //срок службы
    int changed_speed;

};

class Route : public Input_Choice{
    public:
        Route(){

            cout << "Количество станций в маршруте для поезда: " << endl;
            if(read_from_file == false){
                route_amount_of_stations = arc4random()%5+2;

                route = new int*[route_amount_of_stations];
                for(int i=0; i<route_amount_of_stations; i++){     
		        route[i] = new int[2];
                }
            }
            
            cout << route_amount_of_stations << endl;

            
            cout << "Маршрут для поезда и цель остановки: " << endl << "1 - Загрузка" << endl << "2 - Разгрузка" << endl << "3 - Транзит" << endl << "4 - Временная стоянка" << endl;
            for(int i = 0; i < route_amount_of_stations; i++){
                for(int j = 0; j < 2; j++){
                    if(j == 0){
                        if(read_from_file == false){
                            route[i][0] = i+1;
                        } 
                        cout << route[i][j] << " ";
                    }else if(j == 1){
                        if(read_from_file == false){
                            route[i][1] = arc4random()%4+1;
                        }
                        cout << route[i][j] << " ";
                    }
                    
                    
                }
                cout << endl;
            }
            
        }
        ~Route(){};

    protected:
    //int route_amount_of_stations;
    //int **route;
    //bool read_from_file;


};

class Railway : public Route{
    public:
    Railway(){

        amount_of_stations = route_amount_of_stations;
        amount_of_connections = amount_of_stations - 1;
        station_types = new int*[amount_of_stations];
        for(int i=0; i<amount_of_stations; i++){     
		station_types[i] = new int[3];
        }
        for(int i = 0; i < amount_of_stations; i++){
            int station_type = arc4random()%3+1;
            if(station_type == 1){
                this->station_types[i][0] = 1;
                Station_Products S(i);
                this->station_types[i][1] = arc4random()%50+1;

            }else if(station_type == 2){
                this->station_types[i][0] = 2;
                Station_Passengers S(i);
                this->station_types[i][1] = arc4random()%50+1;

            }else if(station_type == 3){
                this->station_types[i][0] = 3;
                Station_Products_Passengers S(i);
                this->station_types[i][1] = arc4random()%50+1;

            }

        }

        if(read_from_file == false){
            connections = new int*[amount_of_connections];
            for(int i=0; i<amount_of_connections; i++){     
		    connections[i] = new int[3];
            }
        }

        for(int i = 0; i < amount_of_connections; i++){
            cout << "Связываемые станции и расстояние между ними: " << endl;
            for(int j = 0; j < 3; j++){
                if(j==0){
                    if(read_from_file == false){
                        connections[i][j] = i+1;
                    }
                    cout << connections[i][j] << " ";
                }else if(j==1){
                    if(read_from_file == false){
                        connections[i][j] = i+2;
                    }
                    cout << connections[i][j] << " ";
                }else if(j==2){
                    if(read_from_file == false){
                        connections[i][j] = (arc4random()%5+1)*10;
                    }
                    cout << connections[i][j] << " ";
                }
                
            }
            cout << endl;
        }

        cout << "////// Отправляемся в путь! //////" << endl;
        for(int i = 0; i < route_amount_of_stations; i++){
            cout << "Мы находимя на станции №" << route[i][0] << "." << endl;
            cout << "Тип станции: " << endl;
            switch(this->station_types[i][0]){
                case 1:{
                    cout << "Станция является товраной." << endl;
                    cout << "Количество ресурсов: " << this->station_types[i][1] << endl;
                    break;
                }
                case 2:{
                    cout << "Станция является пассажирской." << endl;
                    cout << "Количество ресурсов: " << this->station_types[i][1] << endl;
                    break;
                }
                case 3:{
                    cout << "Станция является пассажирско-товарной." << endl;
                    cout << "Количество ресурсов: " << this->station_types[i][1] << endl;
                    break;
                }
            }

            cout << "Цель остановки: " << endl;
            switch(this->route[i][1]){
                case 1:{
                    cout << "Загрузка." << endl;
                    cout << "Количество ресурсов после остановки: " << endl;
                    switch(this->station_types[i][0]){
                        case 1:{
                            cout << this->station_types[i][1] + 5;
                            break;
                        }
                        case 2:{
                            cout << this->station_types[i][1];
                            break;
                        }
                        case 3:{
                            cout << this->station_types[i][1];
                            break;
                        }
                    }
                    break;
                }
                case 2:{
                    cout << "Разгрузка." << endl;
                    cout << "Количество ресурсов после остановки: " << endl;
                    switch(this->station_types[i][0]){
                        case 1:{
                            if(this->station_types[i][1] > 5){
                                cout << this->station_types[i][1] - 5;
                            }else{
                                cout << 0;
                            }
                            break;
                        }
                        case 2:{
                            cout << this->station_types[i][1];
                            break;
                        }
                        case 3:{
                            if(this->station_types[i][1] > 5){
                                cout << this->station_types[i][1] - 5;
                            }else{
                                cout << 0;
                            }
                            break;
                        }
                    }
                    break;
                }
                case 3:{
                    cout << "Транзит." << endl;
                    cout << "Количество ресурсов после остановки: " << endl;
                    switch(this->station_types[i][0]){
                        case 1:{
                            cout << this->station_types[i][1];
                            break;
                        }
                        case 2:{
                            cout << this->station_types[i][1] - 5;
                            break;
                        }
                        case 3:{
                            cout << this->station_types[i][1] - 5;
                            break;
                        }
                    }
                    break;
                }
                case 4:{
                    cout << "Временная остановка." << endl;
                    cout << "Количество ресурсов после остановки: " << endl;
                    cout << this->station_types[i][1];
                    break;
                }
            }
            cout << endl;
            
        }
    }   

    ~Railway() {};


    protected:
    int amount_of_stations;
    //int amount_of_connections;
    //int **connections;
    int **station_types;


};

class Train{
    public:
    Train(int pulling_force, int speed, int service_life, int number_of_carriages){
        Carriage_Products carriage_products;
        Carriage_Passengers carriage_passengers;
        Player P;
        cout << "Данные по поезду: " << endl;
        Locomotive S(pulling_force, speed, service_life, number_of_carriages);
        for(int i = 0; i < number_of_carriages; i++){
            int carriage_type = arc4random()%2+1;
            if(carriage_type == 1){
                this->carriage_types[i] = 1;
                P.Carriage_Type(&carriage_products);
            }else if(carriage_type == 2){
                this->carriage_types[i] = 2;
                P.Carriage_Type(&carriage_passengers);
            }
            
        }
    }

    ~Train() {};
    //смесь вагонов и локомотивов

    private:
    int carriage_types[];

};

class World{
    public:
        World(){
            Train S(10, 20, 30, 3);
            Railway R;
        }
        ~World() {};

    private:


};
