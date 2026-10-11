# BioTelemetry

![BioMonitor](assets/BIOTELEMETRY_IN_C.png)

> A lightweight, modular C telemetry system designed to simulate and track patient health metrics (temperature, heart rate, and ECG). Built as a hands-on project to practice systems programming concepts in C.

---

## Features

- **Modular Architecture:** Clean separation of concerns with dedicated header (`include/`) and source (`src/`) files.
- **Custom Data Models:** Leverages structs, enums, and unions to efficiently handle multi-sensor data types.
- **Dynamic Memory Management:** Explicit heap allocation and deallocation (`malloc`/`free`) with robust `NULL` pointer safety checks.
- **Signal Processing:** Performs basic statistical analysis (mean and standard deviation) using the standard math library (`-lm`).
- **File Persistence:** Supports human-readable ASCII text exports and direct binary file streams (`fread`/`fwrite`).
- **Build Automation:** Fully automated compilation and clean-up via a custom `Makefile`.

---

## Project Structure

```text
BioMonitor/
├── include/
│   ├── analytics.h
│   ├── buffer.h
│   ├── file_io.h
│   └── patient.h
├── src/
│   ├── analytics.c
│   ├── buffer.c
│   ├── file_io.c
│   └── patient.c
├── main.c
└── Makefile
```

---

## Getting Started

### Prerequisites

To compile and run this project, you will need:
- A C compiler (such as `gcc`)
- The `make` utility

### Building and Running

Clone the repository and use the included `Makefile` to build the executable:

```bash
# 1. Build the project
make

# 2. Run the program
./biomonitor

# (Optional) Start by loading an existing binary save file
./biomonitor patient_data.bin

# 3. Clean up build artifacts and generated test files
make clean
```

---

## License

This project is open source and available under the [MIT License](LICENSE).