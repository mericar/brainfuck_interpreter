#include <stdio.h>
int code[500] = {0};
int data[30000] = {0};
int bstack[1000] = {0};
int ip = 0;
int * dp = data;
int sp = 0;
int end = 0;

void readcode(char read)
{
	switch(read)
	{
	case '>': code[ip++] = 0; break;
	case '<': code[ip++] = 1; break;
	case '+': code[ip++] = 2; break;
	case '-': code[ip++] = 3; break;
	case '.': code[ip++] = 4; break;
	case ',': code[ip++] = 5; break;
	case '[': code[ip++] = 6; break;
	case ']': code[ip++] = 7; break;
	}
	end = ip;
}

void interpret ()
{
	switch(code[ip])
	{
		case 0: dp++; ip++; break; // >
		case 1: dp--; ip++; break; // <
		case 2: *dp = (*dp)++; ip++; break; // +
		case 3: *dp = (*dp)--; ip++; break; // -
		case 4: putchar(*dp); ip++; break; // .
		case 5: *dp = getchar(); ip++; break; // ,
		case 6:  // [
				bstack[sp++] = ip;
				if (*dp == 0)
				{
				while (code[++ip] != 7){}
				}
				break;
			
		case 7: // ]
				if (*dp != 0)
				{
				ip = bstack[--sp];
				}
				else {ip++;}
				break;
		default: ip++;
	}

}


int main(int argc, char *argv[])
{
	if (argc !=  2)
	{
		printf("ERROR: PLEASE INCLUDE BF FILE AS ARGUMENT\n");
		return -1;
	}
	FILE * file = fopen(argv[1], "r+");
	if (file == 0)
	{
		printf("ERROR: COULD NOT OPEN FILE\n");
		return -1;
	}

	int read;
	while (( (read = fgetc(file)) != EOF))
	{
		readcode(read);
	}
	ip = 0;
	while (ip <= end)
	{
	interpret();
	}
}
