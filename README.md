# BANK_MANAGEMENT_SYSTEM
A simple but powerful Bank Management System implemented in C, featuring account creation, deposit/withdrawal operations, fund transfer, transaction history, and persistent file storage. This project is designed with clean data structures, file handling, linked lists, and circular transaction logs.

---
## 🧾 **Project Structure**

```
📂 Bank_Managment_System_C
 ├── Bank_System.c
 ├── Images/
 │     ├── Flowchart.png
 │     ├── Bank_Sample_output.png
 |     ├── 00_sample written_output_format/
 |
 ├── README.md
```

## 🚀 **Features**

### ✔ **Account Management**

* Create new bank accounts
* Search accounts
* Display all accounts

### ✔ **Banking Operations**

* Deposit money
* Withdraw money
* Transfer funds between accounts

### ✔ **Transaction Management**

* Stores last **5 transactions per account**
* Circular transaction buffer (FIFO)
* Auto-generated Transaction IDs

### ✔ **Persistent Storage**

* Saves all account data to **bank.dat**
* Loads previous data automatically at startup

### ✔ **Data Structures Used**

* **Singly Linked List** for storing accounts
* **Array of Structs** for storing transactions per account
* **Circular Indexing** for transaction history

---


---

## 🖥 **How It Works (Program Flow)**

1. Load previous data from file
2. Display main menu
3. Perform user-selected operation
4. Save changes
5. Exit safely

---


## 🧠 **Core Concepts Demonstrated**

| Concept             | Description                         |
| ------------------- | ----------------------------------- |
| **Structures in C** | Account & Transaction management    |
| **Linked Lists**    | Dynamic account storage             |
| **File Handling**   | Binary file I/O using fread/fwrite  |
| **Circular Buffer** | For 5-transaction history           |
| **Modularity**      | Clean function-based implementation |
| **Error Handling**  | Input validation & safe operations  |

---

## 🏗️ **Compilation & Execution**

### **Compile**

```bash
gcc Bank_System.c -o bank
```

### **Run**

```bash
./bank
```

---

## 📚 **Menu Options**

| Option | Description              |
| ------ | ------------------------ |
| 1      | Add Account              |
| 2      | Show All Accounts        |
| 3      | Deposit Money            |
| 4      | Withdraw Money           |
| 5      | Balance Enquiry          |
| 6      | Transfer Funds           |
| 7      | Show Last 5 Transactions |
| 8      | Search Account           |
| 9      | Save Data to File        |
| 10     | Exit Program             |

---

## ⭐ **Why This Project**

* Demonstrates **strong understanding of C fundamentals**
* Uses **data structures & algorithms** effectively
* Shows **real-world problem solving**
* Implements **persistent storage like a real bank system**
* Clean coding structure suitable for scaling

---
## 🏅 **Author**

**Sai Ganesh**  <br>
📌 *Bank Management System in C*


