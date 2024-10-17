
#ifndef INODE_H
#define INODE_H
#include<cstdlib>
#include<string>
#include<ctime>
#include<iostream>
#include "vector.hpp"
#include "queue.hpp"


using namespace std;
enum {File=0,Folder=1};

class Inode
{
	private:
		string name;				//name of the Inode
		bool type;					//type of the Inode 0 for File 1 for Folder
		unsigned int size;			//size of current Inode
		string cr_time; 			//time of creation
		Vector<Inode*> children;	//Children of Inode
		Inode* parent; 				//link to the parent 

	public:
		Inode(string name, bool type, unsigned int size, string cr_time, Inode* parent);

		//methods to HELP
		void addChild(Inode* child);
		void listChildren();
		void removeChild(Inode* child);
		unsigned int getChildrenCount();
		string getName();
		bool getType();
		unsigned int getSize();
		string getCreateTime();
		Inode* getParent();
		string getPath() const;

		friend class VFS;
};
#endif