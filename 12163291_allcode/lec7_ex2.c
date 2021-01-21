#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	int x,y;

	char chkid[10];
	int chksize;
	char format[10];
	char sbchk1id[10];
	int sbchk1size;
	short audioform;
	short numchannels;
	int samplerate;
	int byterate;
	short blkalign;
	short bitpersample;
	char sbchk2id[10];
	int sbchk2size;

	x=open("./swvader03.wav",O_RDONLY,00777); //re view!!
	   
	y=read(x, chkid, 4);  // read first 4 bytes into ChunkID[]
	chkid[y]=0;           // make it a string   
	printf("ChunkID:%s\n", chkid);
	
	y=read(x, &chksize, 4);  // read first 4 bytes into ChunkID[]
	printf("ChunkSize:%d\n", chksize);

	y=read(x, format, 4);  // read first 4 bytes into ChunkID[]
	format[y]=0;           // make it a string   
	printf("Format:%s\n", format);
	
	y=read(x, sbchk1id, 4);  // read first 4 bytes into ChunkID[]
	sbchk1id[y]=0;           // make it a string   
	printf("SubChunk1ID:%s\n", sbchk1id);
	
	y=read(x, &sbchk1size, 4);  // read first 4 bytes into ChunkID[]
	printf("SubChunk1Size:%d\n", sbchk1size);
	
	y=read(x, &audioform, 2);  // read first 4 bytes into ChunkID[]
	printf("Audio form:%d\n", audioform);
	
	y=read(x, &numchannels, 2);  // read first 4 bytes into ChunkID[]
	printf("Number of Channels:%d\n", numchannels);

	y=read(x, &samplerate, 4);  // read first 4 bytes into ChunkID[]
	printf("Sample Rate:%d\n", audioform);
	
	y=read(x, &byterate, 4);  // read first 4 bytes into ChunkID[]
	printf("Byte Rate:%d\n", numchannels);
	
	y=read(x, &blkalign, 2);  // read first 4 bytes into ChunkID[]
	printf("Block Align:%d\n", blkalign);
	
	y=read(x, &bitpersample, 2);  // read first 4 bytes into ChunkID[]
	printf("Bit per Sample sz:%d\n", bitpersample);

	y=read(x, sbchk2id, 4);  // read first 4 bytes into ChunkID[]
	sbchk2id[y]=0;           // make it a string   
	printf("SubChunk2ID:%s\n", sbchk2id);
	
	y=read(x, &sbchk2size, 4);  // read first 4 bytes into ChunkID[]
	printf("SubChunk2Size:%d\n", sbchk2size);
}

