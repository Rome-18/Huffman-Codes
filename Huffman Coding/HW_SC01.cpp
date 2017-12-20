/*Program to compute Entropy and Huffman Codes for given probability distributions.*/
/*Author: Siffi Singh */
/*Dated: 24/10/2017 */

/* For standard Headers */
#include <bits/stdc++.h>
using namespace std;

 
// A Huffman tree node
struct MinHeapNode
{
    string data;                // One of the input characters
    unsigned freq;             // Frequency of the character
    MinHeapNode *left, *right; // Left and right child
 
    MinHeapNode(string data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
 
// For comparison of two heap nodes (needed in min heap)
struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};
 
// Prints huffman codes from the root of Huffman Tree.
void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;
 
    if (root->data != "$")
        cout <<"  "<< root->data << ":\t " << str << "\n";
 
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}
 
// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
void HuffmanCodes(string data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;
 
    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));
 
    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1)
    {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();
 
        right = minHeap.top();
        minHeap.pop();
 
        // Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted
        // node as left and right children of this new node. Add
        // this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = new MinHeapNode("$", left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
 
    // Print Huffman codes using the Huffman tree built above
    printCodes(minHeap.top(), "");
}
//The function that compares and calculates the frequency of a given format for N=4 bits.
int compare4(char a[])
{
	char b[16][100];
    string s;
    for(int i=0; i<16; i++)
    {
    bitset<4> bin_x(i);	//Generating combinations for N = 4 bits
    s = bin_x.to_string();
    strcpy(b[i], s.c_str());
    }
	for(int i=0; i<16; i++)
	{
		int count = 0;
		if(strcmp(a, b[i])==0)		
		return i;
		else
		continue;
	}
}
//The function that compares and calculates the frequency of a given format for N=8 bits.
int compare8(char a[])
{
	char b[256][100];
    string s;
    for(int i=0; i<256; i++)
    {
    bitset<8> bin_x(i);
    s = bin_x.to_string();	//Generating combinations for N = 8 bits
    strcpy(b[i], s.c_str());
    //cout<<b[i]<<endl;
    }	
	for(int i=0; i<256; i++)
	{
		int count=0;
		if(strcmp(a, b[i])==0)
		return i;
		else
		continue;
	}
}

// Driver program 
int main()
{
	char inputfile[10000];
	cout<<"Enter name of file: ";	//Inputing name of the file to be read
	scanf("%s", inputfile);
	ifstream infile;
	infile.open(inputfile , ios::in | ios::binary);	//Reading .dat file
	/*Variable Declarations*/
	int n[8], m[4]={0};
	char a[1000];	
	int count=0;
	char ch;
	int p0=0, p1=0, p00=0, p01=0, p10=0, p11=0, last=0;
	int p8[256]={0}, p4[16]={0};	
	float entropy1=0, entropy2=0, entropy4=0, entropy8=0;	
	float P0=0, P1=0, P00=0, P01=0, P10=0, P11=0, P4[16]={0}, P8[256]={0};
	int x=0;
	/*Reading data from entered filename.dat*/
	if(infile.is_open())
	{	
	while(!infile.eof()) //Reading till the end of file
	{
		infile.read(a, 1);
		char b = a[0];
		/*Converting character inputed from file to binary*/
		for (int i = 7; i >= 0; i--){
				int bit = b >> i & 1;
				n[7 - i] = bit;
				m[x]=bit;				
				if (last == 0 && bit == 0){
					p00++; //Incrementing the probability of P(00)
				}
				else if (last == 0 && bit == 1){
					p01++; //Incrementing the probability of P(01)
				}
				else if (last == 1 && bit == 0){
					p10++; //Incrementing the probability of P(10)
				}
				else if (last == 1 && bit == 1){
					p11++; //Incrementing the probability of P(11)
				}
				if (bit == 0) p0++;  //Incrementing the probability of P(0)
				if (bit == 1) p1++;  //Incrementing the probability of P(1)
				last = bit;					
				if(x==3 || x==7)
				{
					char str[4];
					int q=0;
					int index = 0;
					for (q=0; q<4; q++)
    					index += sprintf(&str[index], "%d", m[q]); //Storing each four bit into a new char array for counting its frequency
					int ans4 = compare4(str);
					p4[ans4]++;
					x=-1;
				}	
				x++;								
			}	
			char str[8];
			int q=0;
			int index = 0;
			for (q=0; q<8; q++)
    			index += sprintf(&str[index], "%d", n[q]);	//Storing each eight bit into a new char array for counting its frequency
			int ans8=compare8(str);
			p8[ans8]++;
	}
	cout<<"----------------------------------------------"<<endl;
	/* Calculating Probabilities */
	P0=(float)p0/80000;	
	//cout<<P0<<endl;
	P1=(float)p1/80000;
	//cout<<P1<<endl;
	//cout<<"----------------------------------------------"<<endl;
	P00=(float)p00/40000;
	//cout<<P00<<endl;
	P01=(float)p01/40000;
	//cout<<P01<<endl;
	P10=(float)p10/40000;
	//cout<<P10<<endl;
	P11=(float)p11/40000;
	//cout<<P11<<endl;
	}
	
	/* Calculating Probabilities */
	//cout<<"----------------------------------------------"<<endl;
	for(int i=0; i<16; i++)
	{
		P4[i]=(float)p4[i]/20000;
		//cout<<P4[i]<<endl;
	}
	//cout<<"----------------------------------------------"<<endl;
	for(int i=0; i<256; i++)
	{
		P8[i]=(float)p8[i]/10000;
		//cout<<P8[i]<<endl;
	}
	
	/*Calculating Entropy Values*/
	entropy1 = (P0*log(1/P0) + P1*log(1/P1));
	entropy2= (P00*log(1/P00) + P01*log(1/P01) + P10*log(1/P10) + P11*log(1/P11));
	for(int i=0; i<16; i++)
	{
		if(P4[i]!=0) //Ignoring values where probability is equal to zero
		entropy4+=(P4[i]*log(1/P4[i]));
	}
	for(int i=0; i<256; i++)
	{
		if(P8[i]!=0) //Ignoring values where probability is equal to zero
		entropy8+=(P8[i]*log(1/P8[i]));
	}
	
	
	/*Printing Entropy Values*/
	cout<<"\n\n======================================================="<<endl;
	cout<<"                    Part 0: Basics                     "<<endl;
	cout<<"======================================================="<<endl;
	cout<<"\n                      ENTROPY                        \n"<<endl;
	cout<<" Entropy for N=1: "<<entropy1<<endl;
	cout<<" Entropy for N=2: "<<entropy2<<endl;
	cout<<" Entropy for N=4: "<<entropy4<<endl;
	cout<<" Entropy for N=8: "<<entropy8<<endl<<"\n";
	
	
	/*Creating Huffman Tree using the probabilities computed above*/
	cout<<"\n======================================================="<<endl;
	cout<<"                 Part 1: Huffman Codes                 "<<endl;
	cout<<"======================================================="<<endl;
	cout<<"\n                   HUFFMAN CODE                      "<<endl;
	/*For N = 2 case*/
	cout<<"\n---------------------- N = 2 -------------------------\n"<<endl;
	string hc2[4]={"1", "2", "3", "4"}; //Declaring identifiers for nodes
	int pp2[4];
	pp2[0]=p00;
	pp2[1]=p01;
	pp2[2]=p10;
	pp2[3]=p11;
	int size=4;
	HuffmanCodes(hc2, pp2, size); //Callling Huffman function for N=2
	/*For N = 4 case*/
	cout<<"\n---------------------- N = 4 -------------------------\n"<<endl;
	string hc4[16] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"}; 
	size = 16;
	HuffmanCodes(hc4, p4, size); //Callling Huffman function for N=4
	
	/*Uncomment the section below to see result for N=8 case*/
	
	/*For N = 8 case*/
//	cout<<"\n---------------------- N = 8 -------------------------\n"<<endl;	
//	string hc8[256]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145","146","147","148","149","150","151","152","153","154","155","156","157","158","159","160","161","162","163","164","165","166","167","168","169","170","171","172","173","174","175","176","177","178","179","180","181","182","183","184","185","186","187","188","189","190","191","192","193","194","195","196","197","198","199","200","201","202","203","204","205","206","207","208","209","210","211","212","213","214","215","216","217","218","219","220","221","222","223","224","225","226","227","228","229","230","231","232","233","234","235","236","237","238","239","240","241","242","243","244","245","246","247","248","249","250","251","252","253","254","255","256"};
//	size = 256;
//	HuffmanCodes(hc8, p8, size);  //Callling Huffman function for N=8	
	return 0;
}
