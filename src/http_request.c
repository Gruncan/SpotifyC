#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifdef __unix__
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>

	#define ERR_LOG(str, err) fprintf(stderr, "Failed! %s: %d\n", str, err);
	#define ERR_LOGR(str, err) {fprintf(stderr, "Failed! %s: %d\n", str, err); return NULL;}
#else
	#define _WINSOCK_DEPCRECATED 1
	#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <windows.h>
	#pragma comment(lib,"ws2_32.lib") //Winsock Library

	#define ERR_LOG(str)  fprintf(stderr, "Failed! %s: %d\n", str, WSAGetLastError());
	#define ERR_LOGR(str) {fprintf(stderr, "Failed! %s: %d\n", str, WSAGetLastError()); return NULL;}
#endif

#include "http_request.h"

	
typedef const char const* char_final;

HttpResponse* send_http_request(HttpObject *http_object) {
	printf("%d\n", DEBUG);
	char_final format = "%s /%s HTTP/1.0\n\rHost:%s\r\n";
	int http_str_len = snprintf(NULL, 0, format, http_object->method, http_object->path, http_object->host);
	char* http_str = (char*) malloc(http_str_len);
	if (http_str == NULL) return NULL;
#ifdef __unix__
	snprintf(http_str, http_str_len, format, HttpMethod[http_object->method], http_object->path, http_object->host);
#else
	sprintf_s(http_str, http_str_len, format, HttpMethod[http_object->method], http_object->path, http_object->host);
#endif
	HttpResponse* http_response = _send_http_string(http_object, http_str);
	return http_response;
}

HttpResponse* send_http_get_request(HttpObject* http_object) {
	return NULL;
}

HttpResponse* send_http_post_request(HttpObject* http_object) {
	return NULL;
}

HttpResponse* _send_http_string(HttpObject* http_object, char* str){
	HttpResponse* http_response = malloc(sizeof(HttpResponse));
	char* response = (char*) malloc(4096);
	if (http_response == NULL || response == NULL) return NULL;
#ifdef __unix__
	struct hostent *server;
    struct sockaddr_in serv_addr;


	// Create socket
 	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) ERR_LOGR("Unable to establish socket", sockfd);
	DEB_LOG("Created socket");

	server = gethostbyname(http_object->host);
    if (server == NULL) ERR_LOGR("No such host found", -1);
	DEB_LOG("Got host");

	memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(http_object->port);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
	DEB_LOG("Wrote connection structs to memory");

	int con_err = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if (con_err < 0) ERR_LOGR("Unable to connect", con_err);
	DEB_LOG("Connected to socket");

	int bytes = write(sockfd, str, strlen(str));
	if(bytes < 0) ERR_LOGR("Unable to write to socket", bytes);
	DEB_LOG("Wrote http string to socket");

	

	memset(response, 0, sizeof(response));
    int total = sizeof(response) - 1;
    int received = 0;
	DEB_LOG("Attenpting to read socket");
    do {
        bytes = read(sockfd, response  + received, total - received);
        if (bytes < 0)
            ERR_LOGR("Unable to read socket", bytes);
        if (bytes == 0)
            break;

        received += bytes;
    } while (received < total);
	DEB_LOG("Read response from socket");

	int close_err = close(sockfd);
	if (close_err < 0) ERR_LOGR("Unable to close socket", close_err);
	DEB_LOG("Closed socket");
	
#else
	WSADATA wsa;
	SOCKET sck;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) ERR_LOGR("Could not startup");
	

	if ((sck = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		ERR_LOGR("Could not create socket");
	

	struct hostent *server = gethostbyname(http_object->host);
	struct sockaddr_in serv_addr;

	serv_addr.sin_addr.s_addr = inet_addr(server->h_addr);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(http_object->port);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(http_object->port);
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

	
	if (connect(sck, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) ERR_LOGR("Unable to connect");
	
	printf("Connected!\n");

	if (send(sck, str, strlen(str), 0) < 0) ERR_LOGR("Unable to send message");
	
	printf("Sent message!\n");

	int received;
	if ((received = recv(sck, response, 4096 * sizeof(char), 0)) == SOCKET_ERROR)
		ERR_LOG("Did not recieve a response");
	printf("Recieved: %d\n", received);
	response_buf[received] = '\0';

	closesocket(sck);
	WSACleanup();

#endif
	http_response->response = response;
	return http_response;
}




