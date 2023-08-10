# Presonal Diary Application With C
 The Personal Diary Application is a console-based program that allows users to register, login, and maintain their diary entries
# Features
1. Data Structures:
   - The application defines two data structures: `struct DiaryEntry` and `struct User`.
   - `struct DiaryEntry` stores information about a diary entry, including the username, date, and content.
   - `struct User` stores information about a registered user, including the username and hashed password.

2. Function Prototypes:
   - The application declares several function prototypes that will be defined later in the code.
   - These function prototypes provide a structure to the code and allow functions to be used before their actual implementation.

3. Constants:
   - The application defines two constant arrays: `usersFileName` and `diaryFileName`.
   - These arrays store the file names where user data and diary entries will be stored, respectively.
   - `encryptionKey` is also defined as a constant, which is used to encrypt and decrypt diary content.

4. `main()` Function:
   - The main function is the entry point of the program.
   - It displays the main menu options using `displayMenu()` and takes user input for the choice using `fgets()` and `sscanf()`.
   - Depending on the user's choice, it calls relevant functions such as `registerUser()`, `loginUser()`, and `displayUserMenu()`.

5. `displayMenu()` Function:
   - This function displays the main menu options for the user to choose from.

6. `displayUserMenu()` Function:
   - This function displays the user menu options after successful login.
   - It takes the username as input and provides options to write a new entry, view previous entries, search entries, and logout.
   - Depending on the user's choice, it calls relevant functions like `writeEntry()`, `viewEntries()`, and `searchEntries()`.

7. `registerUser()` Function:
   - This function allows a new user to register by providing a username and password.
   - The password is hashed using `simpleHash()` function before being stored in the users file.

8. `loginUser()` Function:
   - This function allows an existing user to log in by providing their username and password.
   - The provided password is hashed and compared with the stored hashed password in the users file.

9. `writeEntry()` Function:
   - This function allows a logged-in user to write a new diary entry.
   - It takes the date and content of the entry as input from the user.
   - The content of the entry is encrypted using `encrypt()` function before being stored in the diary file.

10. `viewEntries()` Function:
   - This function allows a logged-in user to view their previous diary entries.
   - It reads entries from the diary file and decrypts the content using the `decrypt()` function before displaying it.

11. `searchEntries()` Function:
   - This function allows a logged-in user to search for specific diary entries based on a search term (date or content).
   - It reads entries from the diary file, decrypts the content using the `decrypt()` function, and checks if the search term matches the date or content.

12. `encrypt()` and `decrypt()` Functions:
   - These functions provide basic encryption and decryption functionality using a simple shift cipher based on the `encryptionKey`.
   - The `encrypt()` function encrypts the provided text, and the `decrypt()` function decrypts the encrypted text.

13. `validateDate()` Function:
   - This function checks if the provided date is in the valid format (DD-MM-YYYY) and within a reasonable range.

14. `clearBuffer()` Function:
   - This function clears the input buffer, ensuring that any extra characters from previous input are discarded.
# Working Mechanism
1. The application starts by displaying the main menu with three options: Register, Login, and Exit.

2. If the user selects the "Register" option, they can create a new account by providing a username and password. The password is hashed using a simple hashing algorithm, and the user's information is stored in a file named "users.txt".

3. If the user selects the "Login" option, they are prompted to enter their username and password. The application reads the "users.txt" file, hashes the provided password, and checks if the credentials match any of the registered users. If the login is successful, the user is redirected to the user menu.

4. The user menu provides four options: Write an Entry, View Previous Entries, Search Entries, and Logout.

5. If the user selects "Write an Entry", they are prompted to enter the date (in the format DD-MM-YYYY) and the content of the diary entry (up to 200 characters). The application encrypts the content using a simple encryption algorithm and then saves the entry to the "diary.txt" file along with the username and date.

6. If the user selects "View Previous Entries", the application reads the "diary.txt" file and displays all previous diary entries associated with the logged-in user. The encrypted content is decrypted before displaying it to the user.

7. If the user selects "Search Entries", they can search for previous diary entries based on a search term (either the date or the content). The application reads the "diary.txt" file, decrypts the content, and checks for a match with the search term. If a match is found, the corresponding entry is displayed to the user.

8. If the user selects "Logout", they are logged out of the current session, and the application returns to the main menu.

9. The application uses functions for various tasks, such as hashing passwords, validating dates, encrypting and decrypting content, and clearing the input buffer.

10. The main data structures used in the application are `struct DiaryEntry` to store diary entries and `struct User` to store user information.

11. The application uses files to store user information and diary entries. The "users.txt" file stores user information (username and hashed password), while the "diary.txt" file stores diary entries (username, date, and encrypted content).

12. The encryption and decryption algorithms used in the application are simple and not meant for strong security but to provide a basic level of privacy for the diary entries.
# Other people who directly and indirectly helped in this project:
<a href="https://github.com/Rajeshsharma-123">RajeshSharma</a></br>
<a href="https://github.com/smtjoshibctioepc">SumitJoshi</a></br>
<a href="https://github.com/prtkdhl">PratikDahal</a></br>
