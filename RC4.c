#include <stdio.h>
#include <string.h>
#include <stdlib.h>


unsigned char S[256];

//Método para intercambiar la posición de una cadena de caracteres
void swap(unsigned char *s, unsigned int i, unsigned int j) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

/* KSA Métod para encriptar el mensaje*/
void rc4_init(unsigned char *key, unsigned int key_length) {

	int i, j;
    for (i = 0; i < 256; i++)
        S[i] = i;
	j = 0;
    for (i = 0; i < 256; i++) {
        j = (j + key[i % key_length] + S[i]) % 256;
        swap(S, i, j);
    }
}

/* PRGA Método para imprimir la encriptación*/
unsigned char rc4_output(int longitudMensaje) {
	int i=0,j=0,k;
	printf("Bits a imprimir: %d\n", longitudMensaje);
	for(k=0; k<longitudMensaje; k++){
		if(k%16==0){
                    printf("\n");
                    printf("DEC %d  HEX %x:  ", k, k);
		}
    	i = (i + 1) % 256;
    	j = (j + S[i]) % 256;
    	swap(S, i, j);
		int t=	S[(S[i] + S[j]) % 256];
		if(t<16){
                    printf("0%x ", t);
                    if(((k+1)%4)==0)
                        printf(" ", t);
                }else{
                    printf("%x ", t);
                    if(((k+1)%4)==0)
                        printf(" ", t);
                }
	}
        return 0;
}

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

int main() {
	unsigned char k[]={0x01,0x02,0x03,0x04,0x05};   //key de 40 bits
	printf("Keylen de %d bytes\n", (int)ARRAY_SIZE(k));
	rc4_init(k, ARRAY_SIZE(k));
	rc4_output(4112);       //imprimos hasta el límite que indica la página de comprobación
        printf("\n");
        return 0;
}