#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
//#include <netinet/in.h>
//#include <sys/wait.h>
//#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>          
//#include <arpa/inet.h>
//#include <netdb.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

#define FILE_NAME_LEN 128
#define DEFUALT_PORT 20000
#define DEFUALT_IP "127.0.0.1"
#define LENGTH 512 

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

string ip;
int port;
string user;
string pass;

void error(const char *msg)
{
        perror(msg);
            exit(1);
}

int inet_pton(int af, const char *src, void *dst)
{
  struct sockaddr_storage ss;
  int size = sizeof(ss);
  char src_copy[INET6_ADDRSTRLEN+1];

  ZeroMemory(&ss, sizeof(ss));
  /* stupid non-const API */
  strncpy (src_copy, src, INET6_ADDRSTRLEN+1);
  src_copy[INET6_ADDRSTRLEN] = 0;

  if (WSAStringToAddress(src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0) {
    switch(af) {
      case AF_INET:
    *(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
    return 1;
      case AF_INET6:
    *(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
    return 1;
    }
  }
  return 0;
}

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
  struct sockaddr_storage ss;
  unsigned long s = size;

  ZeroMemory(&ss, sizeof(ss));
  ss.ss_family = af;

  switch(af) {
    case AF_INET:
      ((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
      break;
    case AF_INET6:
      ((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
      break;
    default:
      return NULL;
  }
  /* cannot direclty use &size because of strict aliasing rules */
  return (WSAAddressToString((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0)?
          dst : NULL;
}


int handle_put(string &file_name)
{
    int sockfd; 
    int nsockfd;
    char revbuf[LENGTH]; 
    struct sockaddr_in remote_addr;
 
    /* Get the Socket file descriptor */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",errno);
        exit(1);
    }

    /* Fill the socket address struct */
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &remote_addr.sin_addr); 
    bzero(&(remote_addr.sin_zero), 8);

    /* Try to connect the remote */
    if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",errno);
        exit(1);
    }
    else 
        printf("[Client] Connected to server at port %d...ok!\n", port);

    printf("file name %s\n", file_name.c_str());
    /* Send File to Server */
    //if(!fork())
    FILE *fs = fopen(file_name.c_str(), "r");
    if(fs == NULL)
    {
        printf("ERROR: File %s not found.\n", file_name.c_str());
        exit(1);
    }

    char sdbuf[LENGTH];
    int fs_block_sz;
    bzero(sdbuf, LENGTH);
    //changing the temp file name
    size_t found = file_name.find_last_of("/\\");
    string newname;
    if (found == string::npos) {
        newname = file_name;
    } else {
        newname = file_name.substr(found+1);
    }

    fs_block_sz = sprintf(sdbuf, "%s %s put %s", user.c_str(), pass.c_str(), newname.c_str());
    if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
    {
        fprintf(stderr, "ERROR: Failed to send operation put %s. (errno = %d)\n",
                file_name.c_str(), errno);
        return 1;
    }

    printf("[Client] Sending %s to the Server... \n", file_name.c_str());
    bzero(sdbuf, LENGTH);
    //sleep(1);

    while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs)) > 0)
    {
        if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
        {
            fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", file_name.c_str(), errno);
            break;
        }
        bzero(sdbuf, LENGTH);
    }
    printf("Ok File %s from Client was Sent!\n", file_name.c_str());
    fclose(fs);
    close (sockfd);
    printf("[Client] Connection closed.\n\n");
    return 0;
}

int handle_get(string &file_name)
{
    int sockfd; 
    int nsockfd;
    char revbuf[LENGTH]; 
    struct sockaddr_in remote_addr;
 
    /* Get the Socket file descriptor */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",errno);
        exit(1);
    }

    /* Fill the socket address struct */
    remote_addr.sin_family = AF_INET; 
    remote_addr.sin_port = htons(port); 
    inet_pton(AF_INET, ip.c_str(), &remote_addr.sin_addr); 
    bzero(&(remote_addr.sin_zero), 8);

    /* Try to connect the remote */
    if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",errno);
        exit(1);
    }
    else 
        printf("[Client] Connected to server at port %d...ok!\n", port);

    /* Send File to Server */
    //if(!fork())
    FILE *fr = fopen(file_name.c_str(), "w");
    if(fr == NULL)
    {
        printf("ERROR: File %s not found.\n", file_name.c_str());
        close(sockfd);
        exit(1);
    }

    char srbuf[LENGTH];
    int fs_block_sz;
    bzero(srbuf, LENGTH);

    fs_block_sz = sprintf(srbuf, "%s %s get %s", user.c_str(), pass.c_str(), file_name.c_str());
    if(send(sockfd, srbuf, fs_block_sz, 0) < 0)
    {
        fprintf(stderr, "ERROR: Failed to send operation get %s. (errno = %d)\n",
                file_name.c_str(), errno);
        return 1;
    }

    printf("[Client] Receiving %s from the Server... \n", file_name.c_str());

    bzero(revbuf, LENGTH); 
    int fr_block_sz = 0;
    bool receive_data = false;
    while((fr_block_sz = recv(sockfd, revbuf, LENGTH, 0)) > 0)
    {
        receive_data = true;
        int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
        if(write_sz < fr_block_sz)
        {
            error("File write failed.\n");
        }
        bzero(revbuf, LENGTH);
        if (fr_block_sz == 0 || fr_block_sz != 512) 
        {
            break;
        }
    }

    if(fr_block_sz < 0) {
        if (errno == EAGAIN)
        {
            printf("recv() timed out.\n");
        }
        else
        {
            fprintf(stderr, "recv() failed due to errno = %d\n", errno);
        }
    }
    printf("Ok received from server!\n");

    fclose(fr);
    close (sockfd);

    if (!receive_data)
        printf("[Client] No data received from server please check valid user and password."
               " Please also check correct file name\n\n");

    printf("[Client] Connection closed.\n\n");
    return 0;
}



int handle_list()
{
    int sockfd;
    int nsockfd;
    char revbuf[FILE_NAME_LEN]; 
    struct sockaddr_in remote_addr;

    /* Get the Socket file descriptor */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",errno);
        exit(1);
    }

    /* Fill the socket address struct */
    remote_addr.sin_family = AF_INET; 
    remote_addr.sin_port = htons(port); 
    inet_pton(AF_INET, ip.c_str(), &remote_addr.sin_addr); 
    bzero(&(remote_addr.sin_zero), 8);

    /* Try to connect the remote */
    if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",errno);
        exit(1);
    }
    else 
        printf("[Client] Connected to server at port %d...ok!\n", port);

    char srbuf[LENGTH];
    int fs_block_sz;
    bzero(srbuf, LENGTH);

    fs_block_sz = sprintf(srbuf, "%s %s list", user.c_str(), pass.c_str());
    if(send(sockfd, srbuf, fs_block_sz, 0) < 0)
    {
        fprintf(stderr, "ERROR: Failed to send operation list. (errno = %d)\n",
                errno);
        return 1;
    }

    printf("[Client] Receiving file list from the Server... \n");

    bzero(revbuf, FILE_NAME_LEN);
    int fr_block_sz = 0;
    bool receive_data = false;
    while((fr_block_sz = recv(sockfd, revbuf, FILE_NAME_LEN, 0)) > 0) {
        printf("file name: %s", revbuf);
        receive_data = true;
        bzero(revbuf, FILE_NAME_LEN);
        if (fr_block_sz == 0) {
            break;
        }
    }

    if (fr_block_sz < 0) {
        if (errno == EAGAIN)
        {
            printf("recv() timed out.\n");
        }
        else
        {
            fprintf(stderr, "recv() failed due to errno = %d\n", errno);
        }
    }

    close (sockfd);
    if (!receive_data)
        printf("[Client] No data received from server please check valid user and password.\n\n");

    printf("[Client] Connection closed.\n\n");

   return 0;
}

int testing_connection()
{
    int sockfd;
    struct sockaddr_in remote_addr;

    /* Get the Socket file descriptor */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",errno);
        exit(1);
    }

    /* Fill the socket address struct */
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &remote_addr.sin_addr); 
    bzero(&(remote_addr.sin_zero), 8);

    /* Try to connect the remote */
    if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1) {
        fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",errno);
        exit(1);
    }
    else
        printf("[Client] Connection to %s at port %d is ok !\n", ip.c_str(), port);

    close (sockfd);
}

int main(int argc, char *argv[])
{
    /* Variable Definition */
//    ip = DEFUALT_IP;
//    port = DEFUALT_PORT;

    cout << "Enter ip:" << endl;
    getline(cin,ip);
    cout << "Enter port:" << endl;
    cin >> port;

    printf("ip is %s, port is %d\n", ip.c_str(), port);
    if(testing_connection()) {
        cout << "can't connect to server. exiting ...." << endl;
        return 1;
    }

    cout << "Enter user:" << endl;
    cin.ignore();
    getline(cin,user);

    cout << "Enter password:" << endl;
    getline(cin,pass);

    printf("user is %s, password is %s\n", user.c_str(), pass.c_str());

    while (1) {

        string cmd;
        cout << "Enter the operation and paramters if needed: " << endl;
        cout << "*) put filename1 filename2 ... " << endl;
        cout << "*) get filename1 filename2 ... " << endl;
        cout << "*) list " << endl;
        cout << "*) exit " << endl;
        cout << "e.g. for getting 2 files please enter : get filename1 filename2" << endl;
        getline (cin,cmd);

        stringstream ss(cmd);
        string item;
        vector<string> tokens;
        while (getline(ss, item, ' ')) {
            tokens.push_back(item);
        }
        string operation(tokens[0]);
        if(operation.compare("put") == 0) {
            for (int i = 1; i < tokens.size(); ++i) {
                handle_put(tokens[i]);
            }

        } else if (operation.compare("get") == 0) {
            for (int i = 1; i < tokens.size(); ++i) {
                handle_get(tokens[i]);
            }

        } else if (operation.compare("list") == 0) {

            handle_list();

        } else if (operation.compare("exit") == 0) {
            cout << "Exiting ..." << endl;
            return 0;
        } else {
            cout << "please use put, get, list or exit operations." << endl;
        }
    }

    return (0);

}
