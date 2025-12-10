PQC Enhanced DNP3 
========
Contributors: Ralph Tan & Zukai Sagan

This project expands on OpenDNP3 to integrate Post-Quantum Cryptography (PQC) algorithms. By incorporating PQC, we aim to future-proof communications, enhance resilience, and promote interoperability. This initiative will be a proactive step towards securing industrial contol systems against post-quantum threats.

Opendnp3 is a portable, scalable, and rigorously tested implementation 
of the [DNP3](https//www.dnp.org) protocol stack written in C++11. The library 
is designed for high-performance applications like many concurrent TCP
sessions or huge device simulations. It also embeds with a small footprint on Linux.

## Setup and Execution - Windows OS

### Prerequisites
* **Git** 
* **CMake** (v3.20+)
* **Visual Studio 2022 Community Edition** (C++ Desktop Workload)
* **Developer Command Prompt for VS 2022**

### Phase 1: Build & Configure

#### 1. Clone and Prepare Dependencies
Open Developer Command Prompt for VS 2022 and run:
```
git clone --recursive https://github.com/RalphTan37/PQC-Enhanced-DNP3-Smart-Grid.git
cd PQC-Enhanced-DNP3-Smart-Grid\dependencies\liboqs
```

#### 2. Build PQC Library (liboqs)
Build and install the cryptographic library locally:
```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="..\install" -DBUILD_SHARED_LIBS=OFF ..
cmake --build . --config Release
cmake --install . --config Release
cd ..\..\..\
```
#### 3. Configure PQC Enhanced DNP3 Project
Create the build directory and run the initial configuration:
```
mkdir build
cd build
cmake -DDNP3_DEMO=ON ..
```

***IMPORTANT CONFIGURATION (Manual Verification)*** <br>
To ensure the demos are definitely enabled, launch the CMake GUI from the build directory:
```
cmake-gui .
```
1. Locate the `DNP3_EXAMPLES` variable in the list
2. Manually check the box if it is not already checked.
3. Press Configure.
4. Press Generate.
5. Close the GUI and return to your terminal.

#### 4. Build Executables
Compile all targets, including the Master and Outstation demos:
```
cmake --build . --config Release --target ALL_BUILD
```

### Phase 2: Run Simulation
Open two separate Developer Command Prompt windows and navigate to the build folder in both:
```
cd PQC-Enhanced-DNP3-Smart-Grid\build
```

#### Window 1: Start the Outstation (Server)
This simulates a smart grid device (RTU) listening for a connection on `0.0.0.0:20000`.
```
.\cpp\examples\outstation\Release\outstation-demo.exe
```
####  Output: `=== PQC-ENHANCED OUTSTATION: READY FOR KYBER ===`

#### Window 2: Start the Master (Client)
This simulates the control center connecting to the device.
```
.\cpp\examples\master\Release\master-demo.exe
```
#### Output: Benchmark results and `channel state change: OPEN`

#### Interactive Commands
Once connected, you can interact with the grid simulation.

| Window | Key | Action |
| :--- | :--- | :--- |
| **Master** | `i` | **Integrity Scan** (Poll all data points) |
| **Master** | `c` | **Control Command** (Send Latch On/Off) |
| **Master** | `d` | **Disable Unsolicited** messages |
| **Outstation** | `b` | Toggle **Binary Input** (Switch Flip) |
| **Outstation** | `a` | Update **Analog Input** (Voltage Change) |
| **Both** | `x` | **Exit** Program |

The log output in both windows will confirm the successful connection and exchange of DNP3 application layer messages, validating the entire process
