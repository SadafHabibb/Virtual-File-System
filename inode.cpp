#include "inode.hpp"
#include "vector.hpp"
#include "queue.hpp"


using namespace std;

Inode::Inode(string name, bool type, unsigned int size, string cr_time, Inode* parent)
    : name(name), 
      type(type), 
      size(size), 
      cr_time(cr_time), 
      parent(parent) {
}


// methiod to add a child Inode
void Inode::addChild(Inode* child) {
    if (type == Folder) {
        children.push_back(child);
        // set the parent of the child to this Inode.
        child->parent = this;
    } else {
        // when the current Inode is not a folder.
        cout << name << " is not a folder. Cannot add child." << endl;
    }
    
}

//method to list child inodes from children vector
void Inode::listChildren() {
    //check if current Inode is a folder type
    if (type == Folder) {
        cout << "Children of " << name << ":" << endl;
        //iterate through each child Inode
        for (size_t i = 0; i < children.size(); ++i) {
             // Give pointer to the current child Inode
            Inode* child = children[i];
            cout << child->name << " (Type: " << (child->type == File ? "File" : "Folder") << ")" << endl;
        }
    } else {
        // when the current Inode is not a folder.
        cout << name << " is not a folder." << endl;
    }
}

//method to remove child inode from children vector
void Inode::removeChild(Inode* child) {
    //iterate through each children vector
    for (size_t i = 0; i < children.size(); ++i) {
        //check if current child Inode is same as given child
        if (children[i] == child) {
            children.erase(i);  // Remove the child element at index i
            break;
        }
    }
}
//method to get the count of children for the current Inode
unsigned int Inode::getChildrenCount() {
    //check if current Inode is a folder type
    if (type == Folder) {
        //give number of children
        return children.size();
    } else {
        // If Inode is not a folder, it has no children.
        return 0;
    }
}

// method to get name of the Inode
string Inode::getName() {
    return name;
}
// method to get type of the Inode
bool Inode::getType() {
    return type;
}
// method to get size of the Inode
unsigned int Inode::getSize() {
    return size;
}
// method to get crearion time of the Inode
string Inode::getCreateTime() {
    return cr_time;
}
// method to get parent of the Inode
Inode* Inode::getParent() {
    return parent;
}

string Inode::getPath() const {
    if (parent == nullptr) {
        return name;
    } else {
        return parent->getPath() + "/" + name;
    }
}

