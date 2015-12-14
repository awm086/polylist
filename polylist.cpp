
//#include <stdio.h>  
#include <stdlib.h>  
//#include <ctype.h> 


#include <iostream>
#include <fstream>

#include <sstream>
#include <string>
using namespace std;

class Node {
private:
	int coef;
	int exp;
	Node* next;
public:
	Node(int c, int e, Node* l) {
		coef = c;
		exp = e;
		next = l;
	}
	Node() {
		coef=exp=0;
		next = NULL;
	}
	Node(int c, int e) {
		coef = c;
		exp = e;
		next = 0;
	}
	bool hasLink() {return next != NULL;}
	void setExp(int e) {exp=e;}
	void setCoef(int c) {coef=c;}
	void setLink(Node* l) {next = l;}
	int getExp() {return exp;}
	int getCoef() {return coef;}
	Node*& link() {
		return next;
	}
};

class polyList{
private:
	Node* first;
public:
	polyList() {first=NULL;}
	Node* findTerm(int e) {
		Node* temp=first;
		while (temp!=NULL) {
			if (temp->getExp()==e) return temp;
			temp=temp->link();
		}
		return NULL;
	}
	void print() {
		cout << "In Print! ";
		Node* temp=first;
		while (temp!=NULL) {
			cout << "coef=" << temp->getCoef() << ", exp=" << temp->getExp() << "--> ";
			temp=temp->link();
		}
		cout << endl;
	}
	void addTerm (int c, int e) {
		if (first==NULL) {
			cout << "Adding Term" << endl;
			first = new Node(c,e,NULL);
			cout << "List so far: ";
			print();
			return;
		}
		cout << "Adding Term" << endl;
		Node* temp;
		if (temp=findTerm(e)) {
			temp->setCoef(temp->getCoef()+c);
		} else if (e < first->getExp()) {
			temp= new Node(c,e,first);
			first=temp;
		} else {
			temp=first;
			while (temp->hasLink() && temp->link()->getExp() < e) {
				temp=temp->link();
			}
			insertAfter(temp,c,e);
		}
		cout << "List so far: ";	
		print();
		return;
	}
	void insertAfter (Node* t, int c, int e) {
		Node* newNode= new Node(c, e, t->link());
		t->setLink(newNode);
	}

	
	void printP(Node* P){
		if(P != NULL){
			printP(P->link());
			if(P->getCoef()!= 0){
				cout << " + "<< "(" << P->getCoef() << ")";
				if ( P->getExp() !=0 )
				cout <<"X^"<< P->getExp();
				}
		}
	}

	void display(){
		Node* temp=first;
		printP(temp);
		cout<<endl;
		return;
	}
	
	
	void printPF(Node* P, ofstream& file){
		if(P != NULL){
			printPF(P->link(), file);
			if(P->getCoef()!= 0){
				file << " + "<< "(" << P->getCoef() << ")";
				if ( P->getExp() !=0 )
				file <<"X^"<< P->getExp();
				}
		}
	}

	void displayF(ofstream& file){
		Node* temp=first;
		printPF(temp, file);
		file<<endl;
		return;
	}

	polyList sum(polyList B){
		Node* temp=B.first;
		Node* temp1=first; 
		polyList newList;

		while(temp!=NULL ){
		
			(newList).addTerm(temp->getCoef(),temp->getExp());
			//temp.first=temp.first->link();
			temp = temp->link();
			//B.first= B.first.link();
		}
		while(temp1 != NULL){
			(newList).addTerm(temp1->getCoef(),temp1->getExp());
			temp1 = temp1->link();
		}
		return newList;
	}
	
	polyList sub(polyList B){     	// set coefs to negative then simply addterms
		Node* temp = B.first;
		Node* temp1 = first;
		polyList newList;  			// to hold the *this list
		polyList newList2;				 // to hold B's negative list
		polyList result;
		while ( temp1 != NULL){
			(newList).addTerm(temp1->getCoef(),temp1->getExp());
			temp1 = temp1->link();
		}
		while(temp!=NULL ){			
			
				//temp->setCoef(-1 * temp->getCoef());
				(newList2).addTerm(-1 * temp->getCoef(),temp->getExp());
				 temp = temp->link();
				
			}
		result = newList.sum(newList2);
		return result;
			
	}

	  polyList multiply(polyList B){
		//multiply 2 polynomials
		polyList temp;
		int coe, exp;
		for (Node* t = first ; t != NULL; t=t ->link() ){
		   for (Node* t2 = B.first ; t2 != NULL; t2=t2 ->link()){
			coe = (t->getCoef()) * (t2->getCoef());
			exp = (t->getExp()) + (t2->getExp());
			temp.addTerm(coe,exp);
			
		   }
		}
		return temp;
	  }
/*	   Node* Reverse (  Node* p) 
	  { 
	     Node *pr = NULL; 
	     while (p != NULL) 
	     { 
	        Node *tmp = p->link(); 
	        p->link() = pr; 
	        pr = p; 
	        p = tmp; 
	     } 
	     return pr; 
	  }

	  
	     Node* dispFile(ofstream & file){
		Node* temp1 = first;
		Node* temp = Reverse(temp1);
	        
	        while(temp!=NULL){
	            if ( temp->getCoef() != 0 ){
	                file << " + " << "(" << temp->getCoef() << ")";
	                if ( temp->getExp() !=0 )
	                    file <<"X^"<< temp->getExp();
	                
	            }
	            temp=temp->link();
	        }
		file<<"\n";
	        file.flush();
	        Reverse(temp1);
	        return temp1;
	     

	    }*/
	
};
polyList readFile(polyList B, int Lpos){
    polyList temp = B;    
    ifstream infile;
    infile.open("input.txt");
    if (!infile) {
                cout << "Unable to open file input.txt";
                exit(1);   // call system to stop
    }
   
    string str;
    int coe, exp;
   
	//while(infile){
		if(Lpos == 2){infile.ignore(256,'\n');}
		getline(infile,str);
		istringstream iss(str,istringstream::in);
		while(iss>>coe && iss>>exp){
		
			
		    if (coe != 0)
			temp.addTerm(coe,exp);
		   
		}
		
	//}
	return temp;
}

int main () {
	polyList a, b, c, d, e;
	b=readFile(b,1);
	
	a=readFile(a,2);
	
	
	ofstream output;
		output.open("output.txt");
		if(!(output.is_open())){
			cout << "Error opening file. \n";
			exit(1);
		}
		
		output<<"Y1:\n";
		b.displayF(output);
		
		output<<"Y2:\n";
		a.displayF(output);
		
		c=a.sum(b);
				output<<"Y1+Y2:\n";
				c.displayF(output);
				
		e=b.sub(a);
			output<<"Y1-Y2:\n";
			e.displayF(output);
			
		d= a.multiply(b);
			output<<"Y1 * Y2:\n";
			d.displayF(output);
		
		
		cout<< "Y1 : "<<endl;
		b.display();
		
		cout<< "Y2: "<<endl;
		a.display();
		
		cout<< "Y1+Y2 : "<<endl;
		c.display();
		
		cout<< "Y1-Y2 : "<<endl;
		e.display();
		
		cout<< "Y1*Y2 : "<<endl;
		d.display();
	
	
	return 0;
}


