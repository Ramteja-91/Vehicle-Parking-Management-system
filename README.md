# Vehicle Parking Management System

A console-based parking management application written in **C++17**. The program can park Cars, Bikes, and Trucks, assign parking slots, calculate parking fees, and store parking records in text files.

## Features

- Park Cars, Bikes, and Trucks.
- Assign the first available parking slot automatically.
- Prevent the same vehicle from being parked twice at the same time.
- Search for and display parked vehicles.
- Display occupied and available parking slots.
- Generate a bill when a vehicle exits.
- Keep a record of completed parking visits.
- Restore active parking records when the program is started again.

## Parking fees

| Vehicle type | Fee per hour |
|---|---:|
| Bike | Rs. 20 |
| Car | Rs. 40 |
| Truck | Rs. 60 |

A minimum of one hour is charged. Any extra part of an hour is counted as a full hour.

## OOP concepts used

### Encapsulation
The `Vehicle` class keeps its data members private. Public getter functions provide access to the required information.

### Inheritance
`Car`, `Bike`, and `Truck` inherit common data and behaviour from the `Vehicle` base class.

### Polymorphism
The derived classes override `getVehicleType()` and `calculateFee()`. The program uses `Vehicle` pointers, so the correct derived-class function is called at runtime.

### Abstraction
`Vehicle` is an abstract class because it contains pure virtual functions. It defines the common interface for all vehicle types.

### Other concepts
- Classes and objects
- Constructors and a virtual destructor
- Function overriding
- Composition: `ParkingManager` contains a `ParkingLot`
- STL `vector` and `unique_ptr`
- File handling using text files

## Project structure

```text
Vehicle-Parking-Management-System/
├── main.cpp
├── README.md
├── .gitignore
├── src/
│   ├── Vehicle.h
│   ├── Vehicle.cpp
│   ├── Car.h
│   ├── Car.cpp
│   ├── Bike.h
│   ├── Bike.cpp
│   ├── Truck.h
│   ├── Truck.cpp
│   ├── ParkingLot.h
│   ├── ParkingLot.cpp
│   ├── ParkingManager.h
│   └── ParkingManager.cpp
└── data/
    ├── active_vehicles.txt
    └── parking_history.txt
```

## Requirements

- Windows, Linux, or macOS
- A C++17-compatible compiler (GCC or MinGW-w64)
- No third-party libraries

## Installation and execution

### 1. Open the project folder

Open the extracted `Vehicle-Parking-Management-System` folder in VS Code or a terminal.

### 2. Compile the program

**Windows (MinGW-w64 / GCC):**

```bash
g++ -std=c++17 -Wall -Wextra main.cpp src/Vehicle.cpp src/Car.cpp src/Bike.cpp src/Truck.cpp src/ParkingLot.cpp src/ParkingManager.cpp -o parking.exe
```

**Linux / macOS:**

```bash
g++ -std=c++17 -Wall -Wextra main.cpp src/Vehicle.cpp src/Car.cpp src/Bike.cpp src/Truck.cpp src/ParkingLot.cpp src/ParkingManager.cpp -o parking
```

### 3. Run the program

**Windows:**

```powershell
.\parking.exe
```

**Linux / macOS:**

```bash
./parking
```

Run the program from the project root folder. The `data` folder and its files are created automatically if they do not exist.

## How to use

1. Select **Park a vehicle**.
2. Choose Car, Bike, or Truck.
3. Enter the vehicle registration number and owner's name.
4. The system assigns an available slot.
5. Select **Vehicle exit and generate bill** when the vehicle leaves.
6. Use the search, parked-vehicle list, slot-status, and history options when required.

## Data storage

- `data/active_vehicles.txt` stores vehicles that are currently parked.
- `data/parking_history.txt` stores completed parking visits and their bills.

The application uses plain-text files, so a database is not required. Keep the `data` folder with the program files.

## Configuration

The default parking capacity is **10 slots**. It can be changed in `main.cpp` when creating the `ParkingManager` object.

---

**Language:** C++  
**Standard:** C++17  
**Application type:** Console-based
