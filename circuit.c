////////////////////////////////////////////////////////////////////////
// File: name here
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // may need to change to #include <string.h>

enum
{
   G_JUNK,         /* 0 */
   G_INPUT,        /* 1 */
   G_OUTPUT,       /* 2 */
   G_XOR,          /* 3 */
   G_XNOR,         /* 4 */
   G_DFF,          /* 5 */
   G_AND,          /* 6 */
   G_NAND,         /* 7 */
   G_OR,           /* 8 */
   G_NOR,          /* 9 */
   G_NOT,          /* 10 */
   G_BUF,          /* 11 */
};

////////////////////////////////////////////////////////////////////////
// circuit class
////////////////////////////////////////////////////////////////////////

class circuit
{
    // circuit information
    int gatenum;
    int numgates;       // total number of gates (faulty included)
    int maxlevels;      // number of levels in gate level ckt
    int numInputs;	// number of inputs
    int numOutputs;	// number of outputs
    unsigned char *gtype;	// gate type
    short *fanin;		// number of fanins of gate
    short *fanout;		// number of fanouts of gate
    int *levelNum;		// level number of gate
    int **faninlist;		// fanin list of gate
    int **fanoutlist;		// fanout list of gate
    int *visited;

    // you may wish to add more private variables here

public:
    int k;
    int a[100];
    circuit(char *);            // constructor
    void initializevisits()
    {
        k=0;
        for(int i=0;i<numgates;i++)
        {
            visited[i] = 0;
        }
        printf("Initialization Complete \n\n\n");
    }
    
    void printfanins(int gatenum)
    {
        int input1,input2;
        visited[gatenum]=1;
        if(fanin[gatenum] == 0)
        {
            return;
        }
        else
        {
            for(int i=0;i<fanin[gatenum];i++)
            {
                if(visited[faninlist[gatenum][i]] == 1)
                {
                    continue;
                }
                a[k]=faninlist[gatenum][i];
                k++;
                printfanins(faninlist[gatenum][i]);
            }
        }
    }

    // you may wish to add more function declarations (or public variables) here
};

////////////////////////////////////////////////////////////////////////
// constructor: reads in the *.lev file and builds basic data structure
// 		for the gate-level ckt
////////////////////////////////////////////////////////////////////////
circuit::circuit(char *cktName)
{
    FILE *inFile;
    char fName[256];
    int i, j, count;
    char c;
    int junk;
    int f1, f2, f3;
    k=0;

    strcpy(fName, cktName);
    strcat(fName, ".lev");
    inFile = fopen(fName, "r");
    if (inFile == NULL)
    {
	fprintf(stderr, "Can't open .lev file\n");
	exit(-1);
    }

    numgates = maxlevels = 0;
    numInputs = numOutputs = 0;

    fscanf(inFile, "%d", &count);	// number of gates
    fscanf(inFile, "%d", &junk);	// skip the second line

    // allocate space for gates data structure
    gtype = new unsigned char[count];
    fanin = new short[count];
    fanout = new short[count];
    levelNum = new int[count];
    visited = new int[count];
    faninlist = new int * [count];
    fanoutlist = new int * [count];

    // now read in the circuit
    for (i=1; i<count; i++)
    {
	fscanf(inFile, "%d", &gatenum);
	fscanf(inFile, "%d", &f1);
	fscanf(inFile, "%d", &f2);
	fscanf(inFile, "%d", &f3);

	numgates++;
	gtype[gatenum] = (unsigned char) f1;
	if (gtype[gatenum] > 13)
	    printf("gate %d is an unimplemented gate type\n", gatenum);
	else if (gtype[gatenum] == G_INPUT)
	    numInputs++;
	else if (gtype[gatenum] == G_OUTPUT)
	    numOutputs++;

	f2 = (int) f2;
	levelNum[gatenum] = f2;

	if (f2 >= (maxlevels))
	    maxlevels = f2 + 5;

	fanin[gatenum] = (int) f3;
	// now read in the faninlist
	faninlist[gatenum] = new int[fanin[gatenum]];
	for (j=0; j<fanin[gatenum]; j++)
	{
	    fscanf(inFile, "%d", &f1);
	    faninlist[gatenum][j] = (int) f1;
	}

	for (j=0; j<fanin[gatenum]; j++) // followed by samethings
	    fscanf(inFile, "%d", &junk);

	// read in the fanout list
	fscanf(inFile, "%d", &f1);
	fanout[gatenum] = (int) f1;

	fanoutlist[gatenum] = new int[fanout[gatenum]];
	for (j=0; j<fanout[gatenum]; j++)
	{
	    fscanf(inFile, "%d", &f1);
	    fanoutlist[gatenum][j] = (int) f1;
	}

	// skip till end of line
	while ((c = getc(inFile)) != '\n' && c != EOF)
	    ;
    }	// for (i...)
    fclose(inFile);

    printf("Successfully read in circuit:\n");
    printf("\t%d PIs.\n", numInputs);
    printf("\t%d POs.\n", numOutputs);
    printf("\t%d total number of gates\n", numgates);
    printf("\t%d levels in the circuit.\n", maxlevels / 5);
}

////////////////////////////////////////////////////////////////////////
// other member functions here
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
// main starts here
////////////////////////////////////////////////////////////////////////
main(int argc, char *argv[])
{
    char cktName[256];
    circuit *ckt,*ckt2;
    int vecWidth, poNum;
    int gate1;
    int gate2;
    int inputs;
    //static vector< vector<int> > vec;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <ckt>\n", argv[0]);
        exit(-1);
    }

    strcpy(cktName, argv[1]);

    // read in the circuit and build data structure
    ckt = new circuit(cktName);
   // scanf("%d", &inputs);
   /* for(int i=0;i<inputs;i++)
    {
        
    }*/
    ckt->printfanins(13);
    
    //  printf("Please enter the first PO:\n");
    //   scanf("%d",&gate1);

    //printf("Please enter the second PO:\n");
    //scanf("%d",&gate2);

    //printf("The common primary inputs for gate %d and %d are \n",gate1,gate2 );
    for(int x=0;x<10;x++)
        {
            printf("%d ",ckt->a[x]);
        }
    ckt->initializevisits();
    ckt->printfanins(8);
    printf("\n \n");
    for(int x=0;x<10;x++)
    {
       printf("%d ",ckt->a[x]);
    }
      ckt->initializevisits();
    ckt->printfanins(12);
    printf("\n \n");
    for(int x=0;x<10;x++)
    {
       printf("%d ",ckt->a[x]);
    }
}