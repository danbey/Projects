#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <ctype.h>         
#include <fstream>      // std::ifstream
#include <vector>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <map>
#include <unordered_map>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <signal.h>
#include <algorithm> 
//#include <nlohmann/json.hpp>

// for convenience
//
using json = nlohmann::json;   // std::replace
using namespace std;

#define FILE_NAME_LEN 128
#define BACKLOG 5
#define LENGTH 512
#define INPUT_LENGTH 1024

#define FILES_DIR "files/"
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

void * handle_put(int nsockfd, string &filename, string &input)
{
    ofstream  infile("file1", ios::in |  ios::out |  ios::app);
   // infile.open (filename.c_str(), ios::out |  ios::app);
    infile << input.c_str();
    cout << __LINE__ << endl;
 
    infile.close();
    cout << "closing socket" << endl;
    return 0;
}

int main (int argc, char **argv)
{
	/* Defining Variables */
	int sockfd;
	int nsockfd;
	int port_num;
	int fr_block_sz = 0;
	socklen_t sin_size;
	struct sockaddr_in addr_local; /* client addr */
	struct sockaddr_in addr_remote; /* server addr */
	char revbuf[LENGTH]; // Receiver buffer
	map < string , string > map_user_to_pass;

	DIR *dir = NULL;
	dir = opendir(FILES_DIR);
	if (!dir) {
		printf("Creating files dir...\n");
		const int dir_err = mkdir(FILES_DIR);
		if (-1 == dir_err) {
			printf("Error creating files directory!n");
			return 1;
		}
	} else {
		closedir(dir);
		printf("files dir exits\n");
	}

    char ip[256] = "127.0.0.1"; // A buffer for our ID
    port_num = 20000;
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }
   
    /* Get the Socket file descriptor */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor. (errno = %d)\n", errno);
        exit(1);
    }
    else
        printf("[Server] Obtaining socket descriptor successfully.\n");

    /* Fill the client socket address struct */
    addr_local.sin_family = AF_INET; // Protocol Family
    addr_local.sin_port = htons(port_num); // Port number
    addr_local.sin_addr.s_addr = INADDR_ANY; // AutoFill local address
    bzero(&(addr_local.sin_zero), 8); // Flush the rest of struct

    /* Bind a special Port */
    if( bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1 )
    {
        fprintf(stderr, "ERROR: Failed to bind Port. (errno = %d)\n", errno);
        exit(1);
    }
    else 
        printf("[Server] Binded tcp port %d in addr 127.0.0.1 sucessfully.\n",port_num);

    /* Listen remote connect/calling */
    if(listen(sockfd,BACKLOG) == -1)
    {
        fprintf(stderr, "ERROR: Failed to listen Port. (errno = %d)\n", errno);
        exit(1);
    }
    else
        printf ("[Server] Listening the port %d successfully.\n", port_num);

    int success = 0;
    while(success == 0)
    {
        sin_size = sizeof(struct sockaddr_in);
        /* Wait a connection, and obtain a new socket file despriptor for single connection */
        if ((nsockfd = accept(sockfd, (struct sockaddr *)&addr_remote, &sin_size)) == -1) 
        {
            fprintf(stderr, "ERROR: Obtaining new Socket Despcritor. (errno = %d)\n", errno);
            exit(1);
        }
        else
            printf("[Server] Server has got connected from %s.\n", inet_ntoa(addr_remote.sin_addr));

        bzero(revbuf, LENGTH);
        if((fr_block_sz = recv(nsockfd, revbuf, LENGTH, 0)) <= 0) {
            printf("received buff empty\n");
            close(nsockfd);
            continue;
        }
        string cmd(revbuf);
        std::replace(cmd.begin(), cmd.end(), ',', '\n');
        map<string, string> dictionary = mappify1(cmd);
        /*
    for(auto const& p: dictionary)
       std::cout <<   p.first << " => " << p.second   << '\n';
        */
       map<string, string>::iterator cmd_it = dictionary.find("\"command\"");
       if (cmd_it == dictionary.end()) {
            cout << "missing command ... " << endl;
            continue;
       } 

        string operation(cmd_it->second); 
  	    if (operation.compare("\"ADD\"") == 0) {
            cout << __LINE__ << endl;

            cout << "add operation ... " << endl;
            map<string, string>::iterator id_it = dictionary.find("\"ID\"");
            if (id_it == dictionary.end()) {
                cout << "missing ID ... " << endl;
                continue;
            }        
            string file_name(id_it->second); 
            remove(file_name.begin(), file_name.end(), '\"');
            map<string, string>::iterator data_it = dictionary.find("\"data\"");
            if (data_it == dictionary.end()) {
                cout << "missing data ... " << endl;
                continue;
            }
            string input = data_it->second;
            cout << nsockfd << "," <<  file_name << "," << input << endl;

            handle_put(nsockfd, file_name, input);
            close(nsockfd);
		
	} else if (operation.compare("GET") == 0) {
           cout << "get operation ... " << endl;
            
            //string output;
           // handle_get(file_name, &output);

	} else if (operation.compare("UPDATE") == 0) {

	}
    }
}
