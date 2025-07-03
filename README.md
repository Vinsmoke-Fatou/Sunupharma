# SunupharmaManagement - Pharmacy Management Console Application
Overview
This is a console-based pharmacy management system developed in C for the SUNUPHARMA pharmacy. The application automates stock management, sales processing, user administration, and daily reporting to streamline pharmacy operations.

Features
Product Management
Manage medicines with unique 5-character codes, names, prices, stock quantities, categories, and expiration dates.

Data stored in a binary file (PRODUCTS.dat) for persistence and quick access.

Category Management
Create and manage product categories with auto-incremented IDs and descriptive labels.

Stored in a binary file (CATEGORIES.dat).

User Management
Two user roles:

Admin: Full control to add/edit/delete products, manage categories, and create/block pharmacist accounts.

Pharmacist: Can sell products, check stock, and generate sales invoices.

Secure login system with enforced password change on first login.

User info stored in a binary file (USERS.dat).

Sales Management
Each sale is assigned a unique timestamp-based ID (AAAAMMDDHHmmSS format).

Automatic stock update after each sale with expiration date verification.

Generates detailed invoices stored in /BILLS/ folder as text files.

Daily Reports
Generates daily sales reports (ETAT_AAAAMMDD.txt) summarizing total sales, quantities sold, and alerts for low stock.

User Interface and Experience
Styled console UI with ASCII art headers and color-coded menus.

Data displayed in aligned tables for easy reading.

Animated status messages (e.g., success, error notifications) to improve user feedback.

Confirmation prompts before critical actions like deletion.

How to Run
1- Compile the C source files using a C compiler (e.g., gcc).

2- Run the executable in a terminal or command prompt.

3- Follow on-screen menus to navigate and use the system.
