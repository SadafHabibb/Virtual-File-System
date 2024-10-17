
#ifndef VFS_H
#define VFS_H
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
#include<ctime>
#include<fstream>
#include <sstream>
#include <algorithm>
#include "inode.hpp"
#include "queue.hpp"

using namespace std;

class VFS
{

	private:
		Inode *root;				//root of the VFS
		Inode *curr_inode;			//current iNode
		Inode *prev_inode;			//previous iNode
		Queue<Inode*> bin;			//bin containing the deleted Inodes
		Queue<string> bin_paths;	//paths of the items in bin
		
	public:	 	
		//Required methods
		VFS();	
		void help();						
		string pwd();
		void ls(bool sort = false);				
		void mkdir(string folder_name);
		void touch(string file_name, unsigned int size);
		void cd(string path);
		void rm(string file_name);
		void size(string path);
		void showbin();
		void emptybin();
		void exit();
		void find(const string& name);
	
		
		/*
		//Optional methods
		void recover();*/

		//Optional helper methods
		//void load(ifstream &fin);				//Helper method to load the vfs.dat
		Inode* getNode(string path);			//Helper method to get a pointer to iNode at given path
		Inode* getChild(Inode *ptr, string childname);	//returns a specific child of given Inode
		bool find_helper(Inode *ptr,const string& name);		//recursive method to check if a given child is present under specific Inode or not
		void updateSize(Inode *ptr);					//re-calculatre the size of an Inode and its parents
		//void write(ofstream &fout, Inode *ptr);			//traverse and write recrusively the vfs data
		string getTime();								//return system time as an string
		
};
//===========================================================
#endif
