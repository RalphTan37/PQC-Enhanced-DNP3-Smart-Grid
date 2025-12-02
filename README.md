PQC Enhanced DNP3 
========
Contributors: Ralph Tan & Zukai Sagan

This project expands on OpenDNP3 to integrate Post-Quantum Cryptography (PQC) algorithms. By incorporating PQC, we aim to future-proof communications, enhance resilience, and promote interoperability. This initiative will be a proactive step towards securing industrial contol systems against post quantum threats.

Opendnp3 is a portable, scalable, and rigorously tested implementation 
of the [DNP3](https//www.dnp.org) protocol stack written in C++11. The library 
is designed for high-performance applications like many concurrent TCP
sessions or huge device simulations. It also embeds with a small footprint on Linux.

Setup and Execution - Windows OS
========

### Required Software Tools (Prerequisites)
* Git
* CMake (version 3.20+)
* Developer Command Prompt for VS 2022
* Visual Studio 2022 Commmunity Edition

#### 1. Clone the Repository
```
git clone https://github.com/RalphTan37/PQC-Enhanced-DNP3-Smart-Grid.git
```

#### 2. Change directory to project
```
cd PQC-Enhanced-DNP3-Smart-Grid
```

#### 3. Create and Enter the Build Directory
```
mkdir build
cd build
```

#### 4. Initial CMake Configuration
Launch the Developer Command Prompt for VS 2022 <br>
Make sure you are in the `build` directory
```
cd \PQC-Enhanced-DNP3-Smart-Grid\build
```
Run command to generate the Visual Studio project files (.sln) in the `build` directory, pointing to the source code (..) and include the DNP3 demos
```
cmake -DDNP3_DEMO=ON ..
```

***IMPORTANT CONFIGURATION*** <br>
Launch the CMake GUI from the build directory
```
cmake-gui .
```
Manually enable `DNP3_EXAMPLES` variable by checking the box. Then press Configure and Generate buttons to update the build files. <br>
Rerun build command to compile all targets, including newly added demo projects.
```
cmake --build . --config Release --target ALL_BUILD
```

#### 5. Open Two Terminal Windows (Developer Command Prompt for VS 2022)
Navigate to the project's root `build` directory 
```
cd \PQC-Enhanced-DNP3-Smart-Grid\build
```
#### 6. Start the Outstation (Window 1)
The Outstation starts first and begins listening for a connection on `0.0.0.0:20000`
```
.\cpp\examples\outstation\Release\outstation-demo.exe
```

#### 7. Start the Master (Window 2)
The Master connects to the Outstation and initiates the DNP3 communication sequence (Disable Unsolicited, Clear Restart IIN, Integrity Poll, Enable Unsolicited, follow by periodic polls).
```
.\cpp\examples\master\Release\master-demo.exe
```

The log output in both windows will confirm the successful connection and exchange of DNP3 application layer messages, validating the entire process