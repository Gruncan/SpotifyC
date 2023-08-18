#ifndef HTTP_REQUEST_FILE_H
#define HTTP_REQUEST_FILE_H

#ifndef DEBUG
	#define DEBUG 0
#endif

#define DEB_LOG(str) if(DEBUG) fprintf(stdout, "DEBUG (%d): %s\n", __LINE__, str);


enum http_method {
	GET,
	POST,
	PUT,
	DELETE,
	
};

static const char* HttpMethod[] = {[GET]="GET", [POST]="POST", [PUT]="PUT", [DELETE]="DELETE" };

struct http_object {
	const char* host;
	const char* path;
	const int port;
	enum http_method method;
} typedef HttpObject;


struct http_response {
	char* response;
} typedef HttpResponse;

HttpResponse* send_http_request(HttpObject *http_object);

HttpResponse* send_http_get_request(HttpObject* http_object);

HttpResponse* send_http_post_request(HttpObject* http_object);

HttpResponse* _send_http_string(HttpObject* http_object, char* str);




#endif // HTTP_REQUEST_FILE_H