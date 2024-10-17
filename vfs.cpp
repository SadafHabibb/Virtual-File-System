#include "vfs.hpp"
#include "inode.hpp"
#include "queue.hpp"
#include <algorithm>
#include <iomanip>
#include <string>



using namespace std; 

// Constructor for the VFS class
VFS::VFS() {
    // Initialize the VFS with a root inode
    root = new Inode("/", Folder, 0, root->getCreateTime(), nullptr);
    curr_inode = root;
    prev_inode = nullptr;
    Queue<Inode*> bin;          
    Queue<string> bin_paths;
}

// Method to display available commands and their descriptions
void VFS::help() {
    cout << "Available commands:" << endl;
    cout << "pwd                                - Print the path of the current directory" << endl;
    cout << "ls                                 - List the contents of the current directory" << endl;
    cout << "mkdir <folder_name>                - Create a new folder" << endl;
    cout << "touch <file_name> <size>           - Create a new file with the given size" << endl;
    cout << "cd <path>                          - Change the current directory to the specified path" << endl;
    cout << "rm <file_name>                     - Remove a file" << endl;
    cout << "size <path>                        - Display the size of a file or directory" << endl;
    cout << "showbin                            - Show the contents of the Bin/Trash" << endl;
    cout << "emptybin                           - Empty the Bin/Trash" << endl;
    cout << "exit                               - Exit the virtual filesystem" << endl;
}

string VFS::pwd() {
    // when the current inode is the root
    if (curr_inode == root) {
        return "/";
    }

    // initialize empty string to store the path
    string path = "";
    //create temporsry pointer
    Inode* temp = curr_inode; 

    // move up the directory to build the path
    while (temp && temp != root) {
        path = "/" + temp->getName() + path;
        // move to the parent Inode
        temp = temp->getParent();
    }

    //print path
    return path;
}

void VFS::ls(bool sort) {
    // Check if the current inode is a folder
    if (curr_inode->getType() == Folder) {
        Vector<Inode*>& children = curr_inode->children;

        // Use bubble sort algorithm to sort children based on size in descending order if sort is true
        if (sort == true) {
            int numChildren = children.size();
            for (int i = 0; i < numChildren - 1; i++) {
                for (int j = 0; j < numChildren - i - 1; j++) {
                    // Check if both children are files
                    if (children[j]->getType() == File && children[j + 1]->getType() == File) {
                        // Compare sizes and swap children
                        if (children[j]->getSize() < children[j + 1]->getSize()) {
                            // Swap the two children
                            swap(children[j], children[j + 1]);
                        }
                    }
                }
            }
        }

        // Print the header
        cout << left << setw(10) << "Type" << setw(20) << "Name" << setw(20) << "Size" << setw(20) << "Date" << endl;

        // Use the begin and end functions to iterate over the children
        for (size_t i = 0; i < children.size(); ++i) {
            Inode* child = children[i];
            string fileType = (child->getType() == Folder) ? "dir" : "file";
            cout << left << setw(10) << fileType << setw(20) << child->getName() << setw(20) << child->getSize() << setw(20) << child->getCreateTime() << endl;
        }
    } else {
        // Print a warning if the current inode is not a folder
        cout << "Warning: Current inode is not a folder." << endl;
    }
}



void VFS::mkdir(string folder_name) {
    //check if current inode is folder or not
    if (curr_inode->getType() != Folder) {
        cout << "Cannot create a folder under a non-folder location." << endl;
        return;
    }

    // check if folder name is alphanumeric
    for (size_t i = 0; i < folder_name.size(); ++i) {
        char c = folder_name[i];
        if (!isalnum(c)) {
            cout << "Invalid folder name. Folder names should be alphanumeric." << endl;
            return;
        }
    }

    // check if a child with similar name already exists
    Inode* existingChild = getChild(curr_inode, folder_name);
    if (existingChild) {
        if (existingChild->getType() == Folder) {
            cout << "A folder with the same name already exists." << endl;
        } else {
            cout << "A file with the same name already exists." << endl;
        }
        return;
    }


    // create a new folder Inode
    Inode* newFolder = new Inode(folder_name, Folder, 10, getTime() , curr_inode);

    // add the new folder to the children of the current Inode
    curr_inode->addChild(newFolder);

    // update the size of the current inode
    updateSize(curr_inode);
}




void VFS::touch(string file_name, unsigned int size) {
    // check if current inode is a folder, as files are only created in folders
    if (curr_inode->getType() != Folder) {
        cout << "Cannot create a file under a non-folder location." << endl;
        return;
    }

    // check if the file name is alphanumeric
    for (size_t i = 0; i < file_name.size(); ++i) {
        char c = file_name[i];
        if (!isalnum(c) && c != '.') {
            cout << "File name should be alphanumeric and may include periods for file extensions." << endl;
            return;
        }
    }

    // Create a new file Inode 
    Inode* newFile = new Inode(file_name, File, size, getTime() ,curr_inode);
    // add the new file Inode to the current folder
    curr_inode->addChild(newFile);

    // update the size of the current inode
    updateSize(curr_inode);
    
}

void VFS::cd(string path) {
    Inode* temp = nullptr;

    //check if path is empty 
    if (path.empty() || path == " ") {
        // Change current inode to root
        curr_inode = root;
    } else if (path == "..") {
        // change current inode to its parent folder
        if (curr_inode != root) {
            prev_inode = curr_inode; // update the previous inode
            curr_inode = curr_inode->getParent();
        } else {
            cout << "Already at root." << endl;
            return; 
        }
    } else if (path == "-") {
        // Change current inode to the previous working directory
        if (prev_inode) {
            temp = curr_inode;
            curr_inode = prev_inode; //update prev inode
            prev_inode = temp;
        } else {
            cout << "No previous working directory." << endl;
            return; 
        }
    } else if (path == "/") {
        // Change current inode to root
        curr_inode = root;
    } else if (path[0] == '/') {
        // Change current inode to the specified path if it exists
        Inode* new_inode = getNode(path);
        if (new_inode) {
            prev_inode = curr_inode; // update the prev inode
            curr_inode = new_inode;
        } else {
            cout << "Path not found." << endl;
            return; 
        }
        //return an error if it is file 
  } else {
        // Change current inode to the specified folder
        Inode* new_inode = getChild(curr_inode, path);
        if (new_inode) {
            prev_inode = curr_inode; // update the prev inode

            if (new_inode->getType() == Folder) {
                curr_inode = new_inode;
            } else {
                cout << "Error: Cannot cd into a file." << endl;
            }
        } else {
            cout << "Folder not found." << endl;
            return; // No need to proceed further
        }
        return;
    }

}


void VFS::rm(string name) {
    // check if the current inode is a folder
    if (curr_inode->getType() != Folder) {
        cout << "Error: Cannot remove from a file." << endl;
        return;
    }

    // Find the child with the specified name
    Inode* child = getChild(curr_inode, name);

    if (child) {
        // check if child is root
        if (child == root) {
            cout << "Error: Cannot remove the root directory." << endl;
        } else if (child->getType() == Folder && child->children.empty()) {
            // remove the child from the current inode's children
            curr_inode->removeChild(child);

            // add the removed folder to the Bin
            bin.enqueue(child);
            bin_paths.enqueue(pwd() + "/" + name);  // Include separator ("/") here

            // update the size of the current inode and its parent
            updateSize(curr_inode);

            cout << "Removed: " << name << " (Added to Bin)" << endl;
        } else if (child->getType() == Folder) {
            cout << "Error: Cannot remove a non-empty folder. Use 'emptybin' to clear the Bin." << endl;
        } else {
            // add file to the Bin
            bin.enqueue(child);
            bin_paths.enqueue(pwd() + "/" + name);  // Include separator ("/") here

            // update the size of the current inode and its parent
            updateSize(curr_inode);

            cout << "Removed: " << name << " (Added to Bin)" << endl;
        }
    } else {
        cout << "Error: " << name << " not found in the current folder." << endl;
    }
}

void VFS::size(string name) {
    // check if the name is '/'
    if (name == "/") {
        // update the size of the entire file system starting from the root
        updateSize(root);
        cout << "Size of root folder: " << root->getSize() << " bytes" << endl;
        return;
    }

    // Check if the name starts with '/' and adjust the path accordingly
    string fullPath = (name[0] == '/') ? name : (pwd() + "/" + name);

    // get the child with the specific name
    Inode* target = getNode(fullPath);

    // check if the target Inode exists
    if (target) {
        // If the target is a folder, update its size and print the total size
        if (target->getType() == Folder) {
            updateSize(target);
            cout << target->getSize() << " bytes" << endl;
        } else {
            // If the target is a file, print its size
            cout << target->getSize() << " bytes" << endl;
        }
    } else {
        // If the target Inode doesn't exist, print an error message
        cout << "Error: " << fullPath << " not found." << endl;
    }
}



void VFS::emptybin() {
    //goes on until bin is empty 
    while (!bin.isEmpty()) {
        // dequeue the Inode and its original path from the Bin
        Inode* deletedInode = bin.dequeue();
        string deletedPath = bin_paths.dequeue(); 
        //get parent inode of deleted inode
        Inode* parentInode = getNode(deletedPath);

        // trying the restoration or deletion of the deleted Inode
        if (deletedInode) {
            // check if the parent Inode is a folder
            if (parentInode && parentInode->getType() == Folder) {
                // Restore Inode to its original location 
                parentInode->addChild(deletedInode);
                cout << "Restored: " << deletedInode->getName() << " to " << parentInode->getName() << endl;
            } else {
                // when the parent Inode doesn't exist or is not a folder
                cout << "Unable to restore: " << deletedInode->getName() << endl;
            }
        }
    }
}
void VFS::showbin() {
    // Check if bin is not empty
    if (!bin.isEmpty()) {
        // Get the oldest Inode and its path from the front of the Bin
        Inode* oldestInode = bin.front_element();
        string oldestPath = bin_paths.front_element();

        // Ensure the path starts with '/'
        if (!oldestPath.empty() && oldestPath[0] != '/') {
            oldestPath = "/" + oldestPath;
        }

        // Display the oldest inode and its path
        cout << "Next Element to remove: " << oldestPath << " (" << oldestInode->getSize() << " bytes, ";
        cout << oldestInode->getCreateTime() << ")" << endl;
    } else {
        cout << "The Bin is empty." << endl;
    }
}

void VFS::exit() {

    // Exit the program
    ::exit(0); 
}

void VFS::find(const string& name) {
    find_helper(curr_inode, name);
}

bool VFS::find_helper(Inode* ptr, const string& name) {
    if (!ptr) {
        return false;
    }

    // Check if the current inode's name matches the search name
    if (ptr->getName() == name) {
        std::cout << "Found: " << ptr->getPath() << std::endl;
        return true;
    }

    // Recursively search in child folders
    if (ptr->getType() == Folder) {
        for (size_t i = 0; i < ptr->children.size(); ++i) {
            Inode* child = ptr->children[i];
            if (find_helper(child, name)) {
                return true;
            }
        }
    }

    return false;
}



Inode* VFS::getNode(string path) {
    // initiate at the root node
    Inode* currentNode = root;

    // Tokenize the input path
    istringstream iss(path);
    string token;

    //iteraste through each token
    while (getline(iss, token, '/')) {
        if (token == "") {
            // Skip empty tokens
            continue;
        }

        // find the child with the given name
        bool found = false;
        for (size_t i = 0; i < currentNode->children.size(); ++i) {
            Inode* child = currentNode->children[i];
            if (child->getName() == token) {
                // Move to the child if found
                currentNode = child;
                found = true;
                break;
            }
        }

        // If the child is not found return nullptr
        if (!found) {
            return nullptr;
        }
    }

    // Return the Inode found at the specified path
    return currentNode;
}



Inode* VFS::getChild(Inode* ptr, string childname) {
    // iterate through the children of the parent Inode
    for (size_t i = 0; i < ptr->children.size(); ++i) {
        Inode* child = ptr->children[i];
        //check if name of child is same as given name
        if (child->getName() == childname) {
            //return given child 
            return child;
        }
    }
    return nullptr; // if child not found
}

void VFS::updateSize(Inode* ptr) {
    while (ptr) {
        unsigned int newSize = 0;

        // calculate size of inode's children
        for (size_t i = 0; i < ptr->children.size(); ++i) {
            Inode* child = ptr->children[i];
            newSize += child->getSize();

            // If the child is a folder, include the sizes of its children
            if (child->getType() == Folder) {
                for (size_t j = 0; j < child->children.size(); ++j) {
                    newSize += child->children[j]->getSize();
                }
            }
        }

        // set the new size for this inode
        ptr->size = newSize;

        // Move up to the parent inode to update its size
        ptr = ptr->getParent();
    }
}


string VFS::getTime() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    //get current local time
    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    string str(buffer);

    return str;
}







