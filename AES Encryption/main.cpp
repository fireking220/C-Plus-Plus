#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

//prototypes
unsigned long long Whitening(unsigned short[], unsigned short[]);
void keyToLong(ifstream &, unsigned long long &);
void textToLong(ifstream &, unsigned long long &, int);
int F(short, short, unsigned char [16][12]);
short G(short, int, unsigned char [16][12]);
short Ftable(short);
unsigned char K(int, unsigned long long &);
unsigned int hexToBin(char);
unsigned long long cipher(unsigned char [16][12], unsigned short [4], unsigned long long);

//globals
int roundNumber = 0;
//fTable for getting bytes based on subkeys
unsigned char fTable[16][16] = { {0xa3,0xd7,0x09,0x83,0xf8,0x48,0xf6,0xf4,0xb3,0x21,0x15,0x78,0x99,0xb1,0xaf,0xf9},
								 {0xe7,0x2d,0x4d,0x8a,0xce,0x4c,0xca,0x2e,0x52,0x95,0xd9,0x1e,0x4e,0x38,0x44,0x28},
								 {0x0a,0xdf,0x02,0xa0,0x17,0xf1,0x60,0x68,0x12,0xb7,0x7a,0xc3,0xe9,0xfa,0x3d,0x53},
								 {0x96,0x84,0x6b,0xba,0xf2,0x63,0x9a,0x19,0x7c,0xae,0xe5,0xf5,0xf7,0x16,0x6a,0xa2},
								 {0x39,0xb6,0x7b,0x0f,0xc1,0x93,0x81,0x1b,0xee,0xb4,0x1a,0xea,0xd0,0x91,0x2f,0xb8},
								 {0x55,0xb9,0xda,0x85,0x3f,0x41,0xbf,0xe0,0x5a,0x58,0x80,0x5f,0x66,0x0b,0xd8,0x90},
								 {0x35,0xd5,0xc0,0xa7,0x33,0x06,0x65,0x69,0x45,0x00,0x94,0x56,0x6d,0x98,0x9b,0x76},
								 {0x97,0xfc,0xb2,0xc2,0xb0,0xfe,0xdb,0x20,0xe1,0xeb,0xd6,0xe4,0xdd,0x47,0x4a,0x1d},
								 {0x42,0xed,0x9e,0x6e,0x49,0x3c,0xcd,0x43,0x27,0xd2,0x07,0xd4,0xde,0xc7,0x67,0x18},
								 {0x89,0xcb,0x30,0x1f,0x8d,0xc6,0x8f,0xaa,0xc8,0x74,0xdc,0xc9,0x5d,0x5c,0x31,0xa4},
								 {0x70,0x88,0x61,0x2c,0x9f,0x0d,0x2b,0x87,0x50,0x82,0x54,0x64,0x26,0x7d,0x03,0x40},
								 {0x34,0x4b,0x1c,0x73,0xd1,0xc4,0xfd,0x3b,0xcc,0xfb,0x7f,0xab,0xe6,0x3e,0x5b,0xa5},
								 {0xad,0x04,0x23,0x9c,0x14,0x51,0x22,0xf0,0x29,0x79,0x71,0x7e,0xff,0x8c,0x0e,0xe2},
								 {0x0c,0xef,0xbc,0x72,0x75,0x6f,0x37,0xa1,0xec,0xd3,0x8e,0x62,0x8b,0x86,0x10,0xe8},
								 {0x08,0x77,0x11,0xbe,0x92,0x4f,0x24,0xc5,0x32,0x36,0x9d,0xcf,0xf3,0xa6,0xbb,0xac},
								 {0x5e,0x6c,0xa9,0x13,0x57,0x25,0xb5,0xe3,0xbd,0xa8,0x3a,0x01,0x05,0x59,0x2a,0x46} };

int main(int argc, char* argv[]) {
	//all of our subkeys for all rounds
	unsigned char subKeys[16][12];
	unsigned char RsubKeys[16][12];
	ifstream keyFile("key.txt");
	ifstream plainFile;
	streampos sizeEnd = 0;
	streampos sizeBeg = 0;
	streampos sizeMid = 0;
	unsigned short Keys[4];
	unsigned long long key = 0;
	unsigned long long plain = 0;
	unsigned long long * cipherText = NULL;
	unsigned long long * plainText = NULL;
	unsigned i = 0;

	if (argc < 2) {
		cout << "Usage: main.cpp *.txt" << endl;
		cin.get();
		return -1;
	}
	else {
		//converts hex string into a unsigned long long if keyFile could be opened
		if (keyFile.is_open()) {
			keyToLong(keyFile, key);
			keyFile.close();
		}
		else {
			cout << "ERROR: KEY FILE COULD NOT BE OPENED";
			keyFile.close();
			return -1;
		}

		//convert plaintext and key into 4 16 bit shorts
		for (int i = 0; i < 4; i++) {
			Keys[i] = ((key & (0xFFFF000000000000 >> i * 16)) >> (3 - i) * 16) & 0xFFFF;
		}

		//GENERATE ALL KEYS FOR ALL ROUNDS
		for (int j = 0; j < 16; j++) {
			for (int i = 0; i < 12; i++) {
				unsigned char x = K(4 * roundNumber + (i % 4), key);
				subKeys[j][i] = x;
				RsubKeys[15 - j][i] = x;
			}
			roundNumber++;
		}
		roundNumber = 0;
		plainFile.open(argv[1]);

		//encrypt or decrypts plaintext.txt
		//converts first 8 characters into a unsigned long long if plaintext could be opened
		if (plainFile.is_open()) {
			ofstream cipherFileWrite;
			ofstream plainFileWrite;
			float numOfChar = 8.0;
			if (plainFile.peek() == '0') {
				plainFile.seekg(1, ios::beg);
				if (plainFile.peek() == 'x') {
					numOfChar = 16.0;
				}
			}
			//seek to end for calculating size
			plainFile.seekg(0, ios::end);
			//if numOfChar == 8.0 then we are converting from ASCII to hex, if else, we are converting from hex to ASCII
			if (numOfChar == 8.0) {
				cipherFileWrite.open("cyphertext.txt");
				cipherFileWrite << "0x";
			}
			else
				plainFileWrite.open("plaintext.txt");
			sizeEnd = plainFile.tellg();
			if (numOfChar == 16.0)
				plainFile.seekg(2, ios::beg);
			else
				plainFile.seekg(0, ios::beg);
			sizeBeg = plainFile.tellg();
			sizeMid = sizeEnd - sizeBeg;
			sizeEnd = ceil(sizeMid / numOfChar);
			for (int i = 0; i < sizeEnd; i++) {
				plain = 0;
				textToLong(plainFile, plain, numOfChar);
				if (numOfChar == 8.0) {
					unsigned long long b = cipher(subKeys, Keys, plain);
					cipherFileWrite << hex << setfill('0') << setw(16) << b;
				}
				else {
					unsigned long long temp = cipher(RsubKeys, Keys, plain);
					for (int j = 0; j < 8; j++) {
						char a = (char)((temp >> 8 * (7 - j)) & 0xFF);
						if (a)
							plainFileWrite << a;
					}
				}
			}
		}
		else {
			cout << "ERROR: PLAINTEXT FILE COULD NOT BE OPENED";
			plainFile.close();
			return -1;
		}
	}
	return 0;
}

//converts hex key to unsigned long long via bit manipulation
void keyToLong(ifstream & keyFile, unsigned long long & key) {
	keyFile.seekg(2, ios::beg);
	for (int i = 0; i < 8; i++) {
		key = key << 4;
		key = key ^ hexToBin(keyFile.get());
		key = key << 4;
		key = key ^ hexToBin(keyFile.get());
	}
}

//converts string to unsigned long long via bit manipulation
void textToLong(ifstream & plainFile, unsigned long long & plain, int base) {
	char c;
	int i = 0;

	if (base == 16) {
		while (i < 16 && plainFile.get(c)) {
			i++;
			plain = plain << 4;
			plain = plain ^ hexToBin(c);
		}
	}
	else if(base == 8){
		while (i < 8 && plainFile.get(c)) {
			i++;
			plain = plain << 8;
			plain = plain ^ (int)c;
		}
	}
}

//gets subkeys
unsigned char K(int x, unsigned long long & key) {
	int roundBit = 0;
	if ((key >> 63) & 1) {
		roundBit = 1;
	}
	key = key << 1;
	key += roundBit;
	//key is our 64 bit key so we can perform bit shifts
	//THIS IS MY SUBKEY BASED ON 4*ROUND+0,1,2,3 = x!!!!!!!
	return (key >> 8 * (x % 8)) & 0xFF;
}

//Whiteing Step
unsigned long long Whitening(unsigned short words[], unsigned short keys[]) {
	unsigned long long retWhite = 0;
	for (int i = 0; i < 4; i++) {
		//XOR 16 bits of our plaintext with 16 bits of our key
		retWhite = retWhite ^ (words[i] ^ keys[i]);
		//this is here so we don't shift bits to much
		if(i < 3)
			retWhite = retWhite << 16;
	}
	return retWhite;
}

int F(short r0, short r1, unsigned char subKeys[16][12]) {
	short t0 = G(r0, 0, subKeys);
	short t1 = G(r1, 1, subKeys);
	int x = 0xFFFF + 1;
	//(subKeys[roundNumber][8] << 8) ^ subKeys[roundNumber][9]) concatenates subkeys
	short f0 = (t0 + (2 * t1) + ((subKeys[roundNumber][8] << 8) ^ subKeys[roundNumber][9])) % x;
	short f1 = ((2 * t0) + t1 + ((subKeys[roundNumber][10] << 8) ^ subKeys[roundNumber][11])) % x;
	return (f0 << 16) ^ (f1 & 0xFFFF);
}

short G(short r0, int i, unsigned char subKeys[16][12]) {
	short g1 = (r0 >> 8) & 0xFF;
	short g2 = r0 & 0xFF;
	short g3;
	short g4;
	short g5;
	short g6;

	g3 = Ftable(g2 ^ subKeys[roundNumber][4 * i + 0]) ^ g1;
	g4 = Ftable(g3 ^ subKeys[roundNumber][4 * i + 1]) ^ g2;
	g5 = Ftable(g4 ^ subKeys[roundNumber][4 * i + 2]) ^ g3;
	g6 = Ftable(g5 ^ subKeys[roundNumber][4 * i + 3]) ^ g4;
	short gc = (g5 << 8) ^ g6;
	//concatenates g5 and g6
	return (g5 << 8) ^ g6;
}

short Ftable(short g) {
	return fTable[(g >> 4) & 0xF][g & 0xF];
}

//converter for hex to binary number
unsigned int hexToBin(char x) {
	int val = 0;

	char i = toupper(x);
	switch (i) {
	case '0': val = 0;
		break;
	case '1': val = 1;
		break;
	case '2': val = 2;
		break;
	case '3': val = 3;
		break;
	case '4': val = 4;
		break;
	case '5': val = 5;
		break;
	case '6': val = 6;
		break;
	case '7': val = 7;
		break;
	case '8': val = 8;
		break;
	case '9': val = 9;
		break;
	case 'A': val = 10;
		break;
	case 'B': val = 11;
		break;
	case 'C': val = 12;
		break;
	case 'D': val = 13;
		break;
	case 'E': val = 14;
		break;
	case 'F': val = 15;
		break;
	}
	return val;
}

unsigned long long cipher(unsigned char subKeys[16][12], unsigned short Keys[4], unsigned long long plain) {
	short unsigned Words[4];

	for (int i = 0; i < 4; i++) {
		Words[i] = ((plain & (0xFFFF000000000000 >> i * 16)) >> (3 - i) * 16) & 0xFFFF;
	}

	//Whitening step
	unsigned long long retWhite = Whitening(Words, Keys);

	//reset roundNumber
	roundNumber = 0;
	//F step, run for 16 rounds
	for (int i = 0; i < 16; i++) {
		short r0 = (retWhite >> 48) & 0xFFFF;
		short r1 = (retWhite >> 32) & 0xFFFF;
		short r2 = (retWhite >> 16) & 0xFFFF;
		short r3 = retWhite & 0xFFFF;
		short temp0;
		short temp1;
		int f = F(r0, r1, subKeys);
		short f0 = (f >> 16) & 0xFFFF;
		short f1 = f & 0xFFFF;
		temp0 = r0;
		temp1 = r1;
		r0 = r2 ^ f0;
		r1 = r3 ^ f1;
		r2 = temp0;
		r3 = temp1;
		retWhite = 0;
		retWhite = (((retWhite ^ r0) << 48) & 0xFFFF000000000000) ^
			(((retWhite ^ r1) << 32) & 0x0000FFFF00000000) ^
			(((retWhite ^ r2) << 16) & 0x00000000FFFF0000) ^
			((retWhite ^ r3) & 0x000000000000FFFF);
		if (roundNumber == 15) {
			retWhite = 0;
			retWhite = (((retWhite ^ r2) << 48) & 0xFFFF000000000000) ^
				(((retWhite ^ r3) << 32) & 0x0000FFFF00000000) ^
				(((retWhite ^ r0) << 16) & 0x00000000FFFF0000) ^
				((retWhite ^ r1) & 0x000000000000FFFF);
		}
		roundNumber++;
	}

	//Split retwhite into 4 16 bit shorts and store in Words
	for (int i = 0; i < 4; i++) {
		Words[i] = ((retWhite & (0xFFFF000000000000 >> i * 16)) >> (3 - i) * 16) & 0xFFFF;
	}

	return Whitening(Words, Keys);
}

