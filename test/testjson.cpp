//
//  testjson.cpp
//  
//
//  Created by Sylvain Herbreteau on 14/12/2018.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"


// for convenience
using json = nlohmann::json;
using namespace std;

int main(int argc, char * argv[]){
    ifstream infile;

    infile.open("text2.txt");
    string filestr;
    string c;
    if(infile.is_open()){
        while(getline(infile, c)){
            filestr.append(c);
        }
    infile.close();
    }
    else
        cout << "Unable to open file" << endl;
    
    
    json j = json::parse(filestr.c_str());
    
    float pres = j["payload_fields"]["barometric_pressure_3"].get<float>();
    float hum  = j["payload_fields"]["relative_humidity_2"].get<float>();
    float temp = j["payload_fields"]["temperature_1"].get<float>();
    /*
    j.at("relative_humidity_2").get_to(hum);
    j.at("temperature_1").get_to(temp);
    */
    
    cout << j.dump(4) << endl;
    cout << "pressure : " << pres << endl
         << "humidity : " << hum  << endl
         << "temperature : " << temp << endl;
    
}
