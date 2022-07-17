#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
   double real; 
   double imag; 
} Complex;

#define Exit 0
#define Load 1
#define Display 3
#define Copy 2
#define Conjugate 4
#define Add 5
#define Subtract 6
#define Multiply 7
#define Divide 8
#define ARSZ 4
#define setToZero(stack)  (stack.imag=0,stack.real=0) 

#define PROMPT_USER_TO(menuItem) printf("%d. %s complex numbers\n", menuItem, #menuItem);

int  displayMenu();
void executeMenuItem(int menuItem);
Complex loadComplex();
void display(Complex *c, int n);
Complex subtract(Complex *pC1, Complex *pC0);
Complex add(Complex *pC1, Complex *pC0);
Complex multiply(Complex *pC1, Complex *pC0);
Complex divide(Complex *pC1, Complex *pC0);
void complexConjugate(Complex *c);


int main(void){   
   int choice = Exit;
   printf("Welcome to the complex number calculator\n\n");
   do{
      choice = displayMenu();
	   executeMenuItem(choice);
   } while (choice != Exit);

   printf("Program exited\n");
   exit(EXIT_SUCCESS);
}

int displayMenu(){  
    int input = Exit;
    printf("Select one of the following:\n\n");
    PROMPT_USER_TO(Load)
    PROMPT_USER_TO(Copy)
    PROMPT_USER_TO(Display)
    PROMPT_USER_TO(Conjugate)
    PROMPT_USER_TO(Add)
    PROMPT_USER_TO(Subtract)
    PROMPT_USER_TO(Multiply)
    PROMPT_USER_TO(Divide)
    printf("%d. Exit Program\n", Exit);
    scanf("%d", &input);
    return input;
}

void executeMenuItem(int menuItem){  
    //creating complex numbers
    static Complex c0 = {0,0}, c1 = {0,0};
    //added pointers to number references
    Complex *pC0 = &c0, *pC1 = &c1;   
    //creating stack and stack pointer
    static Complex stack[ARSZ], *pStack = stack;
    static int head = ARSZ-1, *pHead = &head;
    
    
 
    switch (menuItem) {

        case Exit: break;

        case Load:
            //incrementing head        
            *pHead = (++head)%ARSZ;
            *(pStack+*pHead)=loadComplex(); 
            break;

        case Display:
           //passing head  
           display(pStack, head); 
           break;  

        case Copy:
            *(pStack+((++head)%ARSZ))=*(pStack+head);
            break;

        case Conjugate:
            complexConjugate(pStack+*pHead);
           break;

        case Add:
           *(pStack+*pHead-1) = add(pStack+*pHead-1,(pStack+((head-1)%ARSZ)));
           setToZero(stack[head]);
           head--;
           break;

        case Subtract: 
           *(pStack+*pHead-1) = subtract(pStack+*pHead,pStack+*pHead-1);
           setToZero(stack[head]);
           head--;
           break;

        case Multiply: 
           *(pStack+*pHead-1) = multiply(pStack+*pHead,pStack+*pHead-1);
           setToZero(stack[head]);
           head--;
           
           break;
        case Divide:
           assert(stack[head].real!=0 && stack[head].imag!=0);
           *(pStack+*pHead-1) = divide(pStack+*pHead,pStack+*pHead-1);
           setToZero(stack[head]);
           head--;
           break;     
        
        default:
            printf("Bad menu value entered; ");
    }
    printf("\n");
}

Complex loadComplex(){
   Complex cTemp; char sign;
printf("\tEnter complex number as 'a + Bi' (e.g. 3.4 - 27.1i) : ");
scanf("%lf %c %lf", &cTemp.real, &sign,
&cTemp.imag);
if (sign=='-') cTemp.imag = -cTemp.imag;
fflush(stdin);
return cTemp;
}

void display(Complex *c,int Head){
for(int i=0;i<ARSZ;i++) {
   int index = (++Head)%ARSZ;
   if((c+index)->imag>=0){   
printf("\n%.3f + %.3fi", (c+index)->real, (c+index)->imag);}
else{
printf("\n%.3f %.3fi", (c+index)->real, (c+index)->imag);}
}
}

Complex add(Complex *pC0, Complex *pC1){
Complex aTemp;
aTemp.real=(pC0->real + pC1->real);
aTemp.imag=(pC0->imag + pC1->imag);
return aTemp;
}
Complex subtract(Complex *pC0, Complex *pC1){
Complex sTemp;
sTemp.real=(pC0->real-pC1->real);
sTemp.imag=(pC0->imag-pC1->imag);
return sTemp;
}
Complex multiply(Complex *pC0, Complex *pC1){
Complex mTemp;
mTemp.real=((pC0->real*pC1->real)-(pC0->imag*pC1->imag));
mTemp.imag=((pC0->real*pC1->imag)+(pC1->real*pC0->imag));
return mTemp;
}
void complexConjugate(Complex *p){
Complex cTemp;
cTemp.real=p->real;
cTemp.imag=p->imag*-1;
*p = cTemp;
}
Complex divide(Complex *pC0, Complex *pC1){
Complex dTempNum;
Complex dTempDen;
Complex dTemp, *pDtemp=&dTemp;

//creating pointer to original pre-conjugated pC0
Complex pc0orig, *pPcorig=&pc0orig;
pc0orig.imag=pC0->imag, pc0orig.real=pC0->real;

//conjugating pC0
complexConjugate(pC0);
//using a combination of conjugated and 
//non conjugated versions of Complex Number 0
dTempNum=multiply(pC1,pC0);
dTempDen=multiply(pPcorig,pC0);
dTemp.real=dTempNum.real/dTempDen.real;
dTemp.imag=dTempNum.imag/dTempDen.real;
return dTemp;
}