#include<cstdio>
#include<cstdlib>

//fast io
/*********************
 *  setvbuf(FILE *stream , char *buf, int type, unsigned size)
 *  type:
 *      _IOFBF: read from stream when buffer is empty, or write to stream when buffer is full
 *      _IOLBF: read from or write to stream by lines
 *      _IONBF: read from or write to stream without buffer
 *  size:
 *      size of buffer (bytes)
 *
 * *********************/
const size_t SZ = 1 << 20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin, inbuf, _IOFBF, SZ);
        setvbuf(stdout, outbuf, _IOFBF, SZ);
    }
}io;


const size_t max_number = 1600010;//maximum size is 1600000
int A[max_number];//Entering line A
int B[max_number];//Leaving line B
int S[max_number];//Station S
bool Operation[2*max_number];//store operation historis, TRUE for push(), FALSE for pop()

int main(){
	//redirecte io to file
	#ifndef _OJ_
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

    long line_size, station_size;//number of trains and the maximum trains station can contain
    scanf("%ld %ld", &line_size, &station_size);
    for(int i = 0; i < line_size; ++i)
        scanf("%d", &B[i]);
    for(int i = 0; i < line_size; i++)
        A[i] = i + 1;
	A[line_size] = line_size + 1;//set a sentry
	S[0] = line_size + 1;
    //three simulated pointers pointing to three arraies respectively
    size_t pointer_A(0), pointer_B(0), pointer_S(0);
    size_t op_size(0);//operation times
    bool end = false; //flag for the loop ending
	while(end = !end){
		//push numbers into stack until the next is larger than the given one
        while(pointer_S < station_size && B[pointer_B] >= A[pointer_A]){
            S[++pointer_S] = A[pointer_A++];//move pointer
            Operation[op_size++] = true; //recorder the operation   
            end = false;
        }
		//pop from stack until the next is unequal to the given one
        while(S[pointer_S] == B[pointer_B]){
            --pointer_S; ++pointer_B;//move pointer
            Operation[op_size++] = false;//record the operation
            end = false;
        }
    }
	//pointer of B moving to the end means the successful traversal
    if(pointer_B == line_size)
        for(int i = 0; i < op_size; ++i)
            if(Operation[i])
                printf("push\n");
            else
                printf("pop\n");
    else
        printf("No\n");

    return 0;
}
