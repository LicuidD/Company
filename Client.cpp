#include <winsock.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int ch;

char data[] = "Data";
char remove1[] = "Remove";
char add[] = "Add";

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	WSAData wsadata;
	WORD vers = MAKEWORD(2, 2);
	if (WSAStartup(vers, &wsadata) != 0) {
		std::cout << "WSA Error";
		Sleep(INFINITE);
	}
	SOCKADDR_IN addr;
	int s = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("10.9.8.154");
	addr.sin_port = htons(45487);
	addr.sin_family = AF_INET;

	SOCKET conn = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(conn, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Failed Connect to server";
		return 1;
	}
	std::cout << "connect!";
	Sleep(1000);
	system("cls");

	char msq[4096];
	std::string msq1;

	while (true) {
		std::cout << "=======================================\n";
		Sleep(20);
		std::cout << "[1] - Посмотреть работников\n";
		Sleep(20);
		std::cout << "=======================================\n";
		std::cin >> ch;
		system("cls");
		if (ch == 1) {
			send(conn, data, sizeof(data), NULL);
			while (true) {
				int bytes = recv(conn, msq, sizeof(msq), NULL);
				msq[bytes] = '\0';

				msq1 = msq;
				if (msq1 == "stop") {
					break;
				}

				std::cout << msq;
			}
		}
	}
}

