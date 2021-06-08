#include "tcp_client.hpp"

/*command pairs*/
command_pair_map_t command_pairs;

/*command info pairs*/
info_pair_map_t com_info_pairs;

/*used to send commands*/
static char CMD_AR[CMD_ARR_SZ] = { 0 };
static char RESP_AR[CMD_ARR_SZ] = { 0 };

/*serial number*/
uint8_t sn = 0;


/*init commands*/
void initCommands(command_pair_map_t& command_pairs, info_pair_map_t& com_info_pairs) {
    command_pairs.insert(command_pair_t("help", HELP));
    com_info_pairs.insert(info_pair_t(HELP, "help command"));

    command_pairs.insert(command_pair_t("trcv", TRCV));
    com_info_pairs.insert(info_pair_t(TRCV, "trcv command syntax: trcv <file name>"));

    command_pairs.insert(command_pair_t("3", CMD_3));
    com_info_pairs.insert(info_pair_t(CMD_3, "3 command syntax: 3 power[Watt]"));

    command_pairs.insert(command_pair_t("42", CMD_42));
    com_info_pairs.insert(info_pair_t(CMD_42, "dimming, 42 command syntax: 42 dim"));

    command_pairs.insert(command_pair_t("56", CMD_56));
    com_info_pairs.insert(info_pair_t(CMD_56, "get status: 56"));


    command_pairs.insert(command_pair_t("142", CMD_142));
    com_info_pairs.insert(info_pair_t(CMD_142, "142 +(color ratio config) + enter"));

    command_pairs.insert(command_pair_t("145", CMD_145));
    com_info_pairs.insert(info_pair_t(CMD_145, "145 command is taken from cmd145.txt\n If 145 19 then open loop table"));

    command_pairs.insert(command_pair_t("146", CMD_146));
    com_info_pairs.insert(info_pair_t(CMD_146, "146 command is taken from cmd146.txt"));

    command_pairs.insert(command_pair_t("150", CMD_150));
    com_info_pairs.insert(info_pair_t(CMD_150, "150 : UVX_Lamp_SetConfig_Request "));

    command_pairs.insert(command_pair_t("151", CMD_151));
    com_info_pairs.insert(info_pair_t(CMD_151, "151 : Get UVX Lamp parameters "));

    command_pairs.insert(command_pair_t("152", CMD_152));
    com_info_pairs.insert(info_pair_t(CMD_152, "152 : Set/Clear UVX Lamp into/From UVC Mode "));

    command_pairs.insert(command_pair_t("156", CMD_156));
    com_info_pairs.insert(info_pair_t(CMD_156, "156 1/"": UVX Lamp / Light gonfig set dim, 156 1 => uvc , 156 => light"));

    command_pairs.insert(command_pair_t("157", CMD_157));
    com_info_pairs.insert(info_pair_t(CMD_157, "157 : UVX Lamp / Light gonfig get dim"));

    command_pairs.insert(command_pair_t("158", CMD_158));
    com_info_pairs.insert(info_pair_t(CMD_158, "158 : UVX Lamp / Light gonfig set min dim"));

    command_pairs.insert(command_pair_t("159", CMD_159));
    com_info_pairs.insert(info_pair_t(CMD_159, "159 : UVX Lamp / Light gonfig get min dim"));


    command_pairs.insert(command_pair_t("160", CMD_160));
    com_info_pairs.insert(info_pair_t(CMD_160, "160 : sets presets table indices."));

    command_pairs.insert(command_pair_t("161", CMD_161));
    com_info_pairs.insert(info_pair_t(CMD_161, "161 : gets presets table indices."));


    command_pairs.insert(command_pair_t("254", OPCOD_GPIO_TEST));
    com_info_pairs.insert(info_pair_t(OPCOD_GPIO_TEST, "254, GPIO_TEST , use: 254 1 [enter]"));


    command_pairs.insert(command_pair_t("exit", EXIT));
    com_info_pairs.insert(info_pair_t(EXIT, "exit command"));
}

/*parse user input*/
void parseUserInput(string& userInput, string(&cmdArgs)[CMD_ARGS_MAX_NUM], int* argc) {
	int i = 0;
	string delimiter = " ";
	size_t pos = 0;
	while ((pos = userInput.find(delimiter)) != string::npos) {
		cmdArgs[i++] = userInput.substr(0, pos);
		userInput.erase(0, pos + delimiter.length());
	}
	cmdArgs[i] = userInput;
	*argc = i;
}

/*true iff input string is a number*/
bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
} 



/*********************************************************************************
* Takes data from file to dst.
* @param  path, path to file.
* @param  dst, destination.
* @param  sz, size of data taken from file to dst, in bytes.
*********************************************************************************/
int takeFromFile(string path, char* dst, size_t& sz) {
	int x = 0;
	int i = 0;
	ifstream inFile;
	inFile.open(path);
	if (!inFile) {
		cout << "Unable to open file";
		exit(1);
	}
	cout << "trying to read: " << path << endl;

	while (inFile >> x) {
		dst[i++] = x;
	}

	sz = i;
	cout << endl;
	inFile.close();
	return 0;
}


/*handle console commands*/
void cmd(SOCKET* ptrConnectSocket) {
	size_t  sz = 0;
	string  userInput;
	string cmdArgs[CMD_ARGS_MAX_NUM];
	int argc;

	
	getline(std::cin, userInput);
	parseUserInput(userInput, cmdArgs, &argc);

		

	if (command_pairs.find(cmdArgs[0]) == command_pairs.end()) {
		cout << "Error try again, print \"help\"" << endl;
		return;
	}
	command_index_t ind = command_pairs.at(cmdArgs[0]);
	switch (ind) {
	case HELP: {

		command_pair_map_t::iterator itr;
		for (itr = command_pairs.begin(); itr != command_pairs.end(); ++itr) {
			cout << '\t' << itr->first << " - " << com_info_pairs.at(itr->second) << '\n';

		}
		break;
	}

	case TRCV: {
		printf("dummy trcv \n");
		break;
	}

	case CMD_3: {
		takeFromFile("./cmd_files/cmd3.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		if (1 <= argc) {
			if (is_number(cmdArgs[1])) {
				CMD_AR[8] = stoi(cmdArgs[1]);
			}
			else {
				cout << "Error try again,  ener a number" << endl;
				return;
			}
		}
		printf("power : %d [Watt] \n", CMD_AR[8]);
			

		parse_and_send(ptrConnectSocket, CMD_AR, sz);

		break;
	}


	case CMD_42: {
		takeFromFile("./cmd_files/cmd42.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		if (1 <= argc) {

			if (is_number(cmdArgs[1])) {

				CMD_AR[8] = stoi(cmdArgs[1]);
			}
			else {
				cout << "Error try again,  ener a number" << endl;
				return;
			}
		}
		printf("please wait for response ...\n");
		parse_and_send(ptrConnectSocket, CMD_AR, sz);
		get_from_server(ptrConnectSocket, RESP_AR, sz);




		break;
	}

	case CMD_56: {
		takeFromFile("./cmd_files/cmd56.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		parse_and_send(ptrConnectSocket, CMD_AR, sz);



		printf("power : %s [Watt] \n", "gSerialBuffer[8]");
		printf("Max power : %s [Watt] \n", "gSerialBuffer[9]");

		break;
	}

	case CMD_142: {

		takeFromFile("./cmd_files/cmd142.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		printf("please wait for response ...\n");
			
		parse_and_send(ptrConnectSocket, CMD_AR, sz);
		break;
	}

	case CMD_145: {

		printf("%d \n", CMD_AR[25]);

		takeFromFile("./cmd_files/cmd145.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		if (1 <= argc) {
			if (is_number(cmdArgs[1])) {
				CMD_AR[24] = stoi(cmdArgs[1]);
			}
			else {
				cout << "Error try again,  ener a number" << endl;
				return;
			}
		}
		parse_and_send(ptrConnectSocket, CMD_AR, sz);

		break;
	}

	case CMD_146: {
		takeFromFile("./cmd_files/cmd146.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		parse_and_send(ptrConnectSocket, CMD_AR, sz);
		//read_serial_resp(gSerialBuffer);
		break;
	}

	case CMD_150: {

		takeFromFile("./cmd_files/cmd150.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		printf("please wait for response ...\n");
		parse_and_send(ptrConnectSocket, CMD_AR, sz);

		break;
	}
	case CMD_151: {

		takeFromFile("./cmd_files/cmd151.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		printf("please wait for response ...\n");
		parse_and_send(ptrConnectSocket, CMD_AR, sz);

		break;
	}
	case CMD_152: {

		takeFromFile("./cmd_files/cmd152.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		printf("please wait for response ...\n");
		parse_and_send(ptrConnectSocket, CMD_AR, sz);

		break;
	}

	case CMD_156: {

		if (1 <= argc) {
			takeFromFile("./cmd_files/cmd156uvc.txt", CMD_AR, sz);
		}
		else {
			takeFromFile("./cmd_files/cmd156light.txt", CMD_AR, sz);
		}


		CMD_AR[CMD_ARR_SN_INDEX] = sn;


		printf("cmd156, please wait for response ...\n");
		parse_and_send(ptrConnectSocket, CMD_AR, sz);

		break;
	}

	case CMD_157: {
		takeFromFile("./cmd_files/cmd157.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		printf("cmd157, please wait for response ...\n");
		parse_and_send(ptrConnectSocket, CMD_AR, sz);
		break;
	}

	case CMD_158: {
		takeFromFile("./cmd_files/cmd158.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		printf("cmd159, please wait for response ...\n");
		parse_and_send(ptrConnectSocket, CMD_AR, sz);
		break;
	}

	case CMD_159: {
		takeFromFile("./cmd_files/cmd159.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		printf("cmd159, please wait for response ...\n");
		parse_and_send(ptrConnectSocket, CMD_AR, sz);
		break;
	}

	case CMD_160: {
		takeFromFile("./cmd_files/cmd160.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		printf("cmd160, please wait for response ...\n");
		parse_and_send(ptrConnectSocket, CMD_AR, sz);
		break;
	}

	case CMD_161: {
		takeFromFile("./cmd_files/cmd161.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		printf("cmd161, please wait for response ...\n");
		parse_and_send(ptrConnectSocket, CMD_AR, sz);
		break;
	}

	case OPCOD_GPIO_TEST: {
		/*
		PD0	A2D	CS_UVC1	Analog measurment UVC1
		PD1		CS_UVC2	Analog measurment UVC2
		PD2		CS_UVC3	Analog measurment UVC3
		PD3		CS_UVC4	Analog measurment UVC4
		PA8	Control FANs	MODE_SELECT	1'- FANs ON and UVC dimming EN. '0' FANs off and UVC dimming disabled.
		PD13	PIR INPUT	PIR_IN	Input From Relay. Normally close- "0". Will change to "1" when detects movement
		*/
		takeFromFile("./cmd_files/cmd254.txt", CMD_AR, sz);
		CMD_AR[CMD_ARR_SN_INDEX] = sn;
		if (1 <= argc) {
			if (is_number(cmdArgs[1])) {
				CMD_AR[8] = stoi(cmdArgs[1]);
			}
			else {
				cout << "Error try again,  ener a number" << endl;
				return;
			}
		}
		printf("please wait for response ...\n");
			
			
		parse_and_send(ptrConnectSocket, CMD_AR, sz);
			
		break;
	}
	case EXIT: {
			
		exit(EXIT_SUCCESS);
		break;
	}
	default:
		break;
	}
	
	cout << userInput << endl;
}


/**
* Parses user input and sends the result to the server.
* It uses send function.
* @param user_input, input of the user.
*/
int parse_and_send(SOCKET* ptrConnectSocket,char * user_input, int user_input_sz) {
    int iResult = send(*ptrConnectSocket, user_input, user_input_sz, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(*ptrConnectSocket);
        WSACleanup();
        iResult = 1;
    }
    return iResult;
}

/**
*  
*  get response from server.
*  
*/
int get_from_server(SOCKET* ptrConnectSocket, char* server_input, int server_input_sz) {
	 
	int iResult = recv(*ptrConnectSocket, server_input, server_input_sz, 0);
	if (iResult > 0) {
		 
		printf("Bytes received: %d\n", iResult);

		printf("RX Hex: ");
		for(int j =0;  j < iResult; j++){
			printf("%02X ", server_input[j]);
		}

	}
	else if (iResult == 0) {
		printf("Connection closed\n");
	}
	else {
		printf("recv failed with error: %d\n", WSAGetLastError());
	}

	return iResult;
}


int __cdecl main(int argc, char** argv)
{
	initCommands(command_pairs, com_info_pairs);

    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    const char* sendbuf = "this is a test, man!";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
  

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    string send_str;
    while (1) {
        //cin >> send_str;
        //// Send the buffer
        //iResult = send(ConnectSocket,(char *) &send_str[0], send_str.length(), 0);
        //if (iResult == SOCKET_ERROR) {
        //    printf("send failed with error: %d\n", WSAGetLastError());
        //    closesocket(ConnectSocket);
        //    WSACleanup();
        //    return 1;
        //}

		cmd(&ConnectSocket);

        //printf("Bytes Sent: %ld\n", iResult);

        /*iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            cout << recvbuf << endl;
            printf("Bytes received: %d\n", iResult);
        }
        else if (iResult == 0) {
            printf("Connection closed\n");
        }
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
        }*/
    }
    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}
