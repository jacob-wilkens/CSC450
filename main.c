#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char encodeRot13(char c);
int indexOf(char c, char* s);
int stringLength(char* s);
char* encodeRot13String(char* s);

int main(int argc, char** argv)
{
    char c = 'r';
    char answer = encodeRot13(c);
    printf("%c maps to %c\n", c, answer);
    char* encodedString = encodeRot13String("hello");
    printf("encoded string is: %s \n", encodedString);
}

char* encodeRot13String(char* s)
{
    
    int length = stringLength(s);
    char* answer = (char*)malloc(length * (int)sizeof(char));

    for (int i = 0; i < length; i++)
    {
        char character = encodeRot13(*(s+i));
        *(answer + i) = character;
    }
    
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
    //printf("%d\n", index);
    index = (index + 13)%26; //17 + 13 = 30
    //printf("%d\n", index);
    //return alphabet[index];
    return *(alphabet + index);
    //how did we tell if we wrapped around?
    //**********START HERE!!!!!
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
