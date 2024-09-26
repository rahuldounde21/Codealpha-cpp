#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

// Function to list files and directories in a given path
void list_files(const string& path) {
    DIR *dir;
    struct dirent *ent;
    struct stat st;

    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string filename = path + "/" + ent->d_name;

            if (stat(filename.c_str(), &st) == 0) {
                if (S_ISDIR(st.st_mode)) {
                    cout << "\033[34m" << ent->d_name << "\033[0m" << endl; // Blue for directories
                } else {
                    cout << ent->d_name << endl;
                }
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
}

// Function to create a new directory
void create_directory(const string& path) {
    if (mkdir(path.c_str(), 0755) == 0) {
        cout << "Directory created successfully: " << path << endl;
    } else {
        perror("Could not create directory");
    }
}

// Function to delete a file or directory
void delete_file(const string& path) {
    if (remove(path.c_str()) == 0) {
        cout << "File or directory deleted successfully: " << path << endl;
    } else {
        perror("Could not delete file or directory");
    }
}

// Function to rename a file or directory
void rename_file(const string& old_path, const string& new_path) {
    if (rename(old_path.c_str(), new_path.c_str()) == 0) {
        cout << "File or directory renamed successfully: " << old_path << " to " << new_path << endl;
    } else {
        perror("Could not rename file or directory");
    }
}

int main() {
    string current_path = ".";

    while (true) {
        cout << "Current directory: " << current_path << endl;
        cout << "Enter a command (list, create, delete, rename, cd, help): ";
        string command;
        getline(cin, command);

        if (command == "list") {
            list_files(current_path);
        } else if (command == "create") {
            cout << "Enter the name of the new directory: ";
            string new_dir;
            getline(cin, new_dir);
            create_directory(current_path + "/" + new_dir);
        } else if (command == "delete") {
            cout << "Enter the name of the file or directory to delete: ";
            string file_to_delete;
            getline(cin, file_to_delete);
            delete_file(current_path + "/" + file_to_delete);
        } else if (command == "rename") {
            cout << "Enter the old name of the file or directory: ";
            string old_name;
            getline(cin, old_name);
            cout << "Enter the new name: ";
            string new_name;
            getline(cin, new_name);
            rename_file(current_path + "/" + old_name, current_path + "/" + new_name);
        } else if (command == "cd") {
            cout << "Enter the new directory path: ";
            string new_path;
            getline(cin, new_path);
            if (chdir(new_path.c_str()) == 0) {
                current_path = new_path;
            } else {
                perror("Could not change directory");
            }
        } else if (command == "help") {
            cout << "Available commands:\n"
                 << "  list: List files and directories in the current directory\n"
                 << "  create: Create a new directory\n"
                 << "  delete: Delete a file or directory\n"
                 << "  rename: Rename a file or directory\n"
                 << "  cd: Change the current directory\n"
                 << "  help: Display this help message\n";
        } else {
            cout << "Invalid command. Try 'help' for a list of available commands." << endl;
        }
    }

    return 0;
}