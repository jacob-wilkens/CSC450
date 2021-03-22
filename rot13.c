#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char encodeRot13(char c);
int indexOf(char c, char* s);
int stringLength(char* s);
char* encodeRot13String(char* s);

char* encodeRot13String(char* s)
{
    
    int length = stringLength(s);
    char* answer = (char*)malloc(length * (int)sizeof(char) + 1);
    char temp;
    for(int i = 0; i < length; i++)
    {
        temp = encodeRot13(*(s + i));
        *(answer + i) = temp;
    }
    *(answer + length) = '\0';
    return answer;

}

int stringLength(char* s)
{
    int count = 0;
    while(*s != '\0')
    {
        count++;
        s = s + 1;
    }
    return count;
}

char encodeRot13(char c)
{
    char* alphabet = "abcdefghijklmnopqrstuvwxyz";
    int index = indexOf(c, alphabet);
    index = (index + 13)%26;
    return *(alphabet + index);

}

int indexOf(char c, char* s)
{
    int s_length = stringLength(s);
    for(int i = 0; i < s_length; i++)
    {
        if(c  == *(s+i))
        {
            return i;
        }
    }
    return -1;
}