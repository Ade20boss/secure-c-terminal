
# Secure Terminal Authentication System

A robust C-based console application simulating a secure employee authentication terminal. This project demonstrates best practices for **safe input handling**, **overflow protection**, and **buffer management** in C without relying on standard, unsafe functions like `scanf` or `gets`.

## 📖 Overview

This program simulates a security checkpoint where employees enter their names and IDs. The system checks these credentials against an internal database and grants access based on a minimum security clearance level.

The primary focus of this codebase is **defensive programming**. It implements custom input functions to rigorously validate user input, ensuring the program is resistant to common vulnerabilities such as integer overflows and buffer overruns.

## ✨ Key Features

* **Custom Safe Input Parsing (`my_scanf`):**
* Manually parses unsigned integers character by character.
* **Overflow Protection:** Mathematically verifies that adding the next digit will not exceed `UINT_MAX` before processing.
* Automatic input flushing on invalid data detection.


* **Secure String Handling (`get_string_safe`):**
* Reads string input with strict bounds checking to prevent buffer overflows.
* **Input Validation:** Automatically rejects names containing numeric characters.
* Handles whitespace and tabs gracefully.


* **Mock Database:** Internal structure array representing an employee database with Security Clearance Levels.
* **Access Control Logic:** Compares user clearance against `MIN_REQUIRED_LEVEL` (Default: 3).

## 🚀 Getting Started

### Prerequisites

* A C compiler (GCC recommended).

### Compilation

Open your terminal and run the following command:

```bash
gcc main.c -o auth_system

```

### Running the Application

```bash
./auth_system

```

## 💻 Usage Example

**1. Successful Login (Access Granted)**

> Alice has Clearance Level 5 (Required: 3).

```text
--- SECURE TERMINAL ACTIVE ---
Enter Name: 
Alice Gabriel
Enter Employee ID: 
1001
Checking Database for User credentials
MATCH FOUND
CHECKING ACCESS ENTRY

--- AUTHENTICATING: Alice Gabriel ---
[ACCESS GRANTED] Welcome, Officer Alice Gabriel.

```

**2. Successful Login (Access Denied)**

> Bob has Clearance Level 1 (Required: 3).

```text
--- SECURE TERMINAL ACTIVE ---
Enter Name: 
Bob Chen
Enter Employee ID: 
1002
Checking Database for User credentials
MATCH FOUND
CHECKING ACCESS ENTRY

--- AUTHENTICATING: Bob Chen ---
[ACCESS DENIED] Clearance Level 3 required.

```

**3. Overflow/Error Handling**

> Demonstrating the robust input validation.

```text
--- SECURE TERMINAL ACTIVE ---
Enter Name: 
Alice123
Invalid Username
[CRITICAL ERROR] Invalid Input format

```

## ⚙️ Technical Details

### Integer Overflow Logic

The standard `scanf("%u", &var)` does not inherently protect against entering a number larger than the variable can hold (wrapping around). This program uses a custom algorithm:

By rearranging the overflow check `(total * 10 + c) <= UINT_MAX`, we ensure the calculation itself never causes an overflow during the check.

### Database Schema

The system simulates a database using the following structure:

```c
struct Employee {
    char name[50];      // 50 char limit
    short access_lvl;   // 1-10 scale
    unsigned int id;    // Unique ID
};

```

**Default Users:**
| Name | ID | Clearance | Result |
| :--- | :--- | :--- | :--- |
| **Alice Gabriel** | 1001 | 5 | Granted |
| **Bob Chen** | 1002 | 1 | Denied |
| **Charlie Grey** | 1003 | 7 | Granted |

## 🛡️ License

MIT LICENSE - This project is open-source and available for educational purposes.


* Create a **Makefile** to go along with this README?
* Add **inline comments** to the code to explain the math behind `(value - c)/10` more clearly?
