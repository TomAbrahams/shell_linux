#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;


int main()
{
	/* The command buffer */
	//string cmdBuff;
	char cmdBuff[256];
	string theStr(cmdBuff);
	/* The ID of the child process */
	pid_t pid;
	cout << "hello!\n";
	/* Keep running until the user has typed "exit" */
	do
	{
		cout<<"in the list\n";
		/* Prompt the user to enter the command */
		cout << "cmd>";
		cin.getline(cmdBuff,256);
		string myStr(cmdBuff);
		theStr = myStr;
		vector<char*> arguments;
		//Need to split the token.
		char* prog = strtok(cmdBuff, " ");
		char* temp = prog;
		
		while (temp != NULL)
		{
			arguments.push_back(temp);
			temp = strtok(NULL, " ");
		}
		char** argv = new char*[arguments.size() + 1];
		for (int k = 0; k < arguments.size(); k++)
			argv[k] = arguments[k];
		argv[arguments.size()] = NULL;

		/* If the user wants to exit */
		
		if (theStr != "exit")
		{
			/* TODO: Create a child */
			pid_t kidpid = fork();
			/* TODO: Error check to make sure the child was successfully created */
			if (kidpid < 0)
			{
				cerr << "Child was not created , an error has occurred" << endl;
				return -1;
			}
			/*** TODO: If I am child, I will do this: ****/
			else if (kidpid == 0)
			{
				/* Call execlp() to replace my program with that specified at the command line.
				* PLEASE NOTE: YOU CANNOT PASS cmdBuff DIRECTLY to execlp(). It is because
				* cmdBuff is an object of type string (i.e., a class) and execlp() expects
				* an array of characters.  However, you can pass cmdBuff.c_str(), which will
				* return an array of characters representation of the string object.
				*
				* Also, please do not forget to error check your exelp() system calls.
				*/
				//Call execlp() to replace my program with that specified at the command line.
				execvp(prog, argv);
				perror("execlp has failed \n");
				return -1;

			}
			else if (kidpid > 0)
			{
				/*** TODO: If I am a parent, I will do the following ***?
				/* Wait for the child process to terminate */
				wait(NULL);
			}
		}
		/*
		for(int j = 0; j<arguments.size() + 1;j++)
			delete[] argv[j];		
		delete[] argv;
		*/
	} while(theStr != "exit");
	
	return 0;
}
