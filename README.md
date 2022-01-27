<img align="center" src="https://i.imgur.com/m8tpDq1.png" width="100" ></img> 
# Notes 
A command-line note-taking program. Created to help me organising my life and plans. It allows you to create a note, name it and optionally give it a description and a date. The notes can be saved to a file which is loaded automatically each time the program runs. Each note has its unique id, which is assigned dynamically with every new session. The id is used for commands like modify or delete. The notes are sorted by date in increasing order. The program has the short mode, which cuts the descriptions, and the archive mode, which shows the notes that were archived. The notes cannot be modified in the archive mode. The program provides a primitive form of command parsing (reading a command and, in some cases, its argument, which is the note's id). <br>
The programs uses object-oriented programming. All the notes are objects of the class note. They are stored in a vector. During the program startup, if there exists the .dtb file, it reads it, creates the objects and pushes them to the vector. The same happens to the notes created by the user during the program's execution. The command "save" allows the program to write the notes from the vector to the database file.<br>
The program also has a custom icon.
#### Technologies used:
Object-oriented C++
## Compiling & running
Compiled using Visual Studio 2019, all the necessary project files are in the repository<br>
Pre-compiled executable available: "notes.exe"
## Screenshots 
#### Creating a note
![first](https://i.imgur.com/37o3WZ5.png)
#### Some notes
![notes](https://i.imgur.com/n9pRlQo.png)
#### Short mode (no descriptions)
![first](https://i.imgur.com/r1sRYOz.png)
#### Archive mode
![notes](https://i.imgur.com/upYgiJU.png)
