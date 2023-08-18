#include "http_request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef const char const* char_final;

HttpResponse* send_http_request(HttpObject const *http_object) {
	char_final format = "%s /%s HTTP/1.0\n\rHost:%s\r\n";
	int http_str_len = snprintf(NULL, 0, format, http_object->method, http_object->path, http_object->host);
	char* http_str = (char*) malloc(http_str_len);
	if (http_str == NULL) return NULL;

#ifdef __unix__
	snprintf(http_str, http_str_len, format, HttpMethod[http_object->method], http_object->path, http_object->host);
#else
	sprintf_s(http_str, http_str_len, format, HttpMethod[http_object->method], http_object->path, http_object->host);
#endif
	HttpResponse* http_response = (HttpResponse*) malloc(sizeof(HttpResponse));
	if (http_response == NULL) return NULL;

	http_response->response = http_str;
	// Test 
	return http_response;

}

HttpResponse* send_http_get_request(HttpObject* http_object) {
	return NULL;
}

HttpResponse* send_http_post_request(HttpObject* http_object) {
	return NULL;
}

HttpResponse* _send_http_string(HttpObject* http_object, char* str) {
	return NULL;
}

