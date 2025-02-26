# Pharmacy - Medication Management Application

## Description
Pharmacy is a C++ application to manage medications and prescribe them. The project is designed considering Object-Oriented Programming. 
I have acquired knowledge about resources management: rule of 3, rule of 5, RAII. The program has a console user interface (UI) and a graphical 
user interface (GUI) implemented using Qt, with the use of the Observer Pattern and Model-View architecture.

## Features
- Manage a list of medications (add, delete, update, print)
- Search and filter by active substance and price
- Sort by name, producer, substance + price
- Manage a prescription (add, generate automatically, export to CSV)
- Implements Observer Pattern and Model-View for real-time updates

## Technologies Used
- C++17
- STL (vector, string, algorithms: sort, copy_if, find_if)
- Exception handling (custom exception classes)
- Qt for GUI
- Observer Pattern
- Model-View

## Architecture
- **Domain** – Defines base classes (Med, Prescription)
- **Repository** – Manages data storage(memory/file) and validation
- **Service** – Application logic
- **UI** – User interface (console and GUI)

## Demo
[Video here](https://youtu.be/v2OwC-wIFdU)
