#include <winsock.h>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int main() {
	std::ifstream file("Data.txt");
	if (!file) {
		std::ofstream file("Data.txt");
		std::cout << "File [ Data.txt ] Not found, Please restart the application and save the data";
		file.close();
		Sleep(INFINITE);
	}
	file.close();


	WSADATA wsadata;
	WORD ver = MAKEWORD(2, 2);
	if (WSAStartup(ver, &wsadata) != 0) {
		std::cout << "WSA Error";
		Sleep(INFINITE);
	}

	SOCKADDR_IN addr;
	int x = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	addr.sin_port = htons(45487);
	addr.sin_family = AF_INET;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sock, (SOCKADDR*)&addr, sizeof(addr));
	listen(sock, SOMAXCONN);

	std::cout << "Server Started!\n";

	SOCKET NewConnect;
	NewConnect = accept(sock, (SOCKADDR*)&addr, &x);
	
	if (NewConnect == 0) {
		std::cout << "Connect Failed\n";
	}
	else {
		std::cout << "Connected!\n";
	}
	char stop[] = "stop";
	char msq[4096];
	std::string msq1;
	std::string data;

	while (true) {
		recv(NewConnect, msq, sizeof(msq), NULL);
		msq1 = msq;
		if (msq1 == "Data") {
			std::ifstream file1("Data.txt");

			while (std::getline(file1, data)) {
				data += '\n';
				send(NewConnect, data.c_str(), data.size(), 0);
				Sleep(10);
			}
			Sleep(200);
			send(NewConnect, stop, sizeof(stop), NULL);
			std::cout << "Send!";
			file1.close();
		}
	}
}