# IoTProject

This Qt code is an application that connect to a MQTT client and display the results on charts.

## Library installation

### QtMqtt

To install this library you must already have Qt installed (version 4.8 or higher) then

```bash
    git clone https://github.com/qt/qtmqtt.git
```

Create a build folder

```bash
    mkdir build
    cd build
    qmake -r ..
    make 
    sudo make install
```
To use the library, the path must be changed on the .pro file

### QtChart

This library is available on the Qt installer. If not already installed, the same process must be done.
The building process is also explained on the QtCharts repository

```bash
    git clone https://github.com/qt/qtcharts.git
```

## Software installation

To compile and execute the programm, cd into the project directory then run :

```bash
    mkdir build 
    cd build
    qmake -r ../IoTProject.pro
    make
    ./IoTProject
```

