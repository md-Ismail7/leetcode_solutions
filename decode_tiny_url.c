#include <stdio.h>
#include<string.h>
#define Mx_urls 1000
#define Mx_l 10000
/** Encodes a URL to a shortened URL. */
#define MAX_URLS 1000
#define MAX_LEN  10000

char urlStore[MAX_URLS][MAX_LEN];
int counter = 0;

char* encode(char* longUrl) {
    static char shortUrl[100];
    strcpy(urlStore[counter], longUrl);
    sprintf(shortUrl, "http://tinyurl.com/%d", counter);
    counter++;
    return shortUrl;
}

char* decode(char* shortUrl) {
    int id;
    sscanf(shortUrl, "http://tinyurl.com/%d", &id);
    return urlStore[id];
}
// Your functions will be called as such:
// char* s = encode(s);
// decode(s);