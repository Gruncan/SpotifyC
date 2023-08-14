#ifndef HTTP_REQUEST_FILE_H
#define HTTP_REQUEST_FILE_H


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

HttpResponse* send_http_request(struct http_object* http_object);

HttpResponse* send_http_get_request(struct http_object* http_object);

HttpResponse* send_http_post_request(struct http_object* http_object);

HttpResponse* _send_http_string(struct http_object* http_object, char* str);




#endif // HTTP_REQUEST_FILE_H