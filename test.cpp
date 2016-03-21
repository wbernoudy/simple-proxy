#include<assert.h>
#include"myproxy.h"
#include<string>

using namespace std;

void test_get_content_length(){
	string str = "HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 44\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert(44==get_content_length(str));

	string str2 = "HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert(0==get_content_length(str2));

	string str3 = "HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 256\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert(256==get_content_length(str3));
}

void test_get_cache(){
	//should be true?
	string str3 = "HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nCache-Control: no-cache\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert(true==get_cache(str3)); 

	string str4 = "HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nCache-Control: max-age=0\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert(false==get_cache(str4));

	string str5 = "HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert(false==get_cache(str5)); 
}


void test_get_IMS(){
	//should be ==?
	string str4 = "HTTP/1.1 200 OK\r\nServer: Apache/2.2.14 (Win32)\r\nIf-Modified-Since: Wed, 19 Oct 2005 10:50:00 GMT\r\nAccept-Ranges: bytes\r\nCache-control: no-cache\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert( "Wed, 19 Oct 2005 10:50:00 GMT" == get_IMS(str4)); 

}

void test_get_hostname_and_port(){
	string str5 = "HTTP/1.1 200 OK\r\nHost: www.cse.cuhk.edu.hk:80\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 44\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert( (pair<string,int> ("www.cse.cuhk.edu.hk",80) )== get_hostname_and_port(str5));
	
	string str6 = "HTTP/1.1 200 OK\r\nHost: www.cse.cuhk.edu.hk:8000\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 44\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert( (pair<string,int> ("www.cse.cuhk.edu.hk",8000) )== get_hostname_and_port(str6));
	
	string str7 = "HTTP/1.1 200 OK\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 44\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert( (pair<string,int> ("",NULL) )== get_hostname_and_port(str7));
	
	string str8 = "HTTP/1.1 200 OK\r\nHost: www.cse.cuhk.edu.hk\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 44\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert( (pair<string,int> ("www.cse.cuhk.edu.hk",80) )== get_hostname_and_port(str8));
	
}

void test_get_url(){
	string str = "GET http://www.cse.cuhk.edu.hk/v7/javascripts/marquee_i.js HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 44\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert( "http://www.cse.cuhk.edu.hk/v7/javascripts/marquee_i.js" ==get_url(str));
}

void test_get_extension(){
	string str = "GET http://www.cse.cuhk.edu.hk/v7/javascripts/marquee_i.js HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 44\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert( "js" ==get_extension(str));
}

void test_is_valid_ext(){
	string str = "GET http://www.cse.cuhk.edu.hk/v7/javascripts/marquee_i.js HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 44\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert( false == is_valid_ext(str));

	string str2 = "GET http://www.cse.cuhk.edu.hk/v7/javascripts/marquee_i.pdf HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 44\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert( true == is_valid_ext(str2));

	string str3 = "GET http://www.cse.cuhk.edu.hk/v7/javascripts/ HTTP/1.1 200 OK\r\nDate: Sun, 18 Oct 2009 08:56:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Sat, 20 Nov 2004 07:16:26 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: 44\r\nConnection: close\r\nContent-Type: text/html\r\nX-Pad: avoid browser bug\r\n\r\n<html><body><h1>It works!</h1></body></html>";
	assert( false == is_valid_ext(str3));
}

int main(){

	test_get_content_length();
	test_get_cache();
	//test_get_IMS();
	test_get_hostname_and_port();
	test_get_url();
	test_get_extension();
	test_is_valid_ext();
	


	
	
}
