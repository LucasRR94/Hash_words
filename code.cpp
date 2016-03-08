#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std; 
//--------------------------------------------------------------------------------------------------------------------------------
//funcionando
class Unit{
	string  chave;
	class   Unit * next;
	int ocupado;
public:
 	Unit(char*,class Unit*); //encaixa a chave e o ponteiro pro proximo 
	Unit();
	void set_string(string);
	string  get_string(){return(chave);}
    void set_pointer(class Unit*);
    class Unit* get_pointer(){return(next);} 
	int  isOcuped(){return(ocupado);}
	int  isnull();
};

Unit::Unit(){
	next  = NULL;
	ocupado = 0;
}


Unit::Unit(char*A,class Unit *B){
	chave   = string(A);
	next    = B;
	ocupado = 1;
}
int  Unit::isnull(){
		if(next == NULL){
				return(1);
		}
		else{
				return(0);
		}
}

void Unit::set_string(string B){
	chave = B;
	if(ocupado==0){
		ocupado++;
	}
}

void Unit::set_pointer(class Unit *B){
	next = new Unit;
	next = B;
}
//-----------------------------------------------------------------------------------------------------------------------------------

int funcao_hash(string a, int tamanho); //funcionando


void alocacao(class Unit *k , int tamanho , string palavra , int posicao);

void busca(string a,class Unit* tabela,int *tamanho2,int *entrada2);

class Unit* funcao_hehash(class Unit *k,int tamanho);
//-----------------------------------------------------------------------------------------------------------------------------------

int main(){
	//-----------
	Unit *simplevector; //vetor
    int tamanho = 100; // tamanho do vetor
   	int entrada = 0;   // numero de entradas lidas 
   	float fatorDeCrescimento;
    simplevector = new Unit[tamanho];
    string entradas; 
  	ifstream arquivo ("entrada.txt"); // arquivo de entrada  
  	if (arquivo.is_open()){ 

	    while (! arquivo.eof() ){ // le do arquivo ateh nao obter mais entradas
			  getline (arquivo,entradas); //le a linha 
	          entrada++;//+um no contador
	          fatorDeCrescimento = (tamanho/entrada);
		      
		      if(fatorDeCrescimento <= 1.5 ){ // fator de crescimento = entrada/espaco na tabela hehash 
		     		simplevector = funcao_hehash(simplevector,tamanho);
		   			tamanho = tamanho * 2;	
					alocacao(simplevector,tamanho,entradas,funcao_hash(entradas,tamanho));
		       		
		       } 
		      
		      else{ //insercao simples
		      		
					alocacao(simplevector,tamanho,entradas,funcao_hash(entradas,tamanho));
		       }
    		
	    }
	    arquivo.close();
  	}
  	else cout<<"NAO FOI POSSIVEL ABRIR ARQUIVO"<<endl;
    busca("XMWOPSSFHYBVCEWNTINJTZAXTFORRGHJOTKJM1LNCSDQVAIUNSQYVHLVDYCBUPLQKUCMMITKEHLXWUGZDRVVJCGZOABAADUTK",simplevector,&tamanho,&entrada); 
    busca("UEOHHEGWLAKZDPUOBFIJIGMVUIMOSLCOBGLWHNWGUQWKTVJOPGZEWKWZEVCOEWTSMHCFOGVXDLXPUICINUSRMALIAOWMKYIWVFMSUIAPUOFP",simplevector,&tamanho,&entrada);   
  	busca("EHOWZXTCMPDMLRNITIKOBQAMUBFLAJLRCPGIJOQKQOBWVIJRYBASSEJWAIIEXEQFHPIWRBRHZU",simplevector,&tamanho,&entrada); 
    return(0);
}


int funcao_hash(string a,int tamanho){ //working
	char    i  = (a[a.size()-1]);
	char 	n  = (a[0]);
	int     ki  = int(i);
	int     ji  = int(n);
	int  h  = a.size();
	float  master = (h*(ji*ki));
	ki = int (master); 
	return(ki%tamanho);//k % tamanho);
}


class Unit* funcao_hehash(class Unit *k,int tamanho){//working
	int copy = tamanho;
	tamanho = tamanho * 2;
	class Unit *l;
	l = new Unit[tamanho];
	int i;
	for(i=0;i <= copy-1;i++){
		if(k[i].isOcuped() == 1){   //caso esteja ocupado ele é relocado
			string aux = k[i].get_string(); 		//pega a string
			int numb = funcao_hash(aux,tamanho);	//descobre nova posicao
			alocacao(l,tamanho,aux,numb);
			class Unit * percorre;
			percorre = k[i].get_pointer();
			while(percorre != NULL){
					int numb2 = funcao_hash(percorre->get_string(),tamanho);
					alocacao(l,tamanho,percorre->get_string(),numb2);
					class Unit * aux;
					aux = percorre->get_pointer();//aux = percorre.next,percorre = aux ou seja , percorrer = percorre->next()
					percorre = aux;	
			}
									
				
		}
	}
	delete [] k;

	return (l);
}

void alocacao(class Unit *k , int tamanho , string palavra , int posicao){//working
	if(k[posicao].isOcuped() == 1){ //fazer alocacao na lista
		Unit *z;
		z = new Unit;
		z->set_string(palavra);
		if(k[posicao].isnull() == 0){ // se ele tem uma lista ele tem que trocar a direcao dos ponteiros
			class Unit *apontador;
			apontador = new Unit();
			apontador = k[posicao].get_pointer();
			k[posicao].set_pointer(z);
			z->set_pointer(apontador);
		}
		else{
			k[posicao].set_pointer(z);
		}
	}
	if(k[posicao].isOcuped() == 0){
		k[posicao].set_string(palavra);
	}

}
 
void busca(string a,class Unit* tabela,int *tamanho2,int* entrada2){ //working
	int tamanho = *tamanho2;
	int entrada = *entrada2;
	int posicao =  funcao_hash(a,tamanho);
	int achou = 0;
	float fatorDeCrescimento2 = 0;
	if(tabela[posicao].isOcuped()==1){ //Isocuped It means that there is something in this vector position
		string comparison = tabela[posicao].get_string();
		if(comparison.compare(a)==0){
			cout<<"position of string : "<<posicao<<endl;
		}
		else{
			class Unit *percorre,*aux;
			percorre = tabela[posicao].get_pointer();
			while(percorre!=NULL){
				string copy = percorre->get_string();
				if(copy.compare(a)==0){
					cout<<"position of string : "<<posicao<<endl;
					percorre = NULL;
					achou++;
					
				}
				else{
					aux = percorre->get_pointer();
					percorre = aux;
				}
			}
			if(achou == 0){
				fatorDeCrescimento2 = (tamanho/entrada);
				cout<<"String not in the vector 1"<<endl;
				entrada++;
				if(fatorDeCrescimento2 <= 1.5 ){ // fator de crescimento = entrada/espaco na tabela hehash 
		     		tabela = funcao_hehash(tabela,tamanho);
		   			tamanho = tamanho * 2;
		   			*entrada2 = entrada;
					alocacao(tabela,tamanho,a,funcao_hash(a,tamanho)); // fazer uma funcao de insercao que verifica condições de hehash
		       		tamanho2 = &tamanho;
					
		       	} 
		      
		      	else{ //insercao simples

		      		*entrada2 = entrada;
					alocacao(tabela,tamanho,a,funcao_hash(a,tamanho)); // fazer uma funcao de insercao que verifica condições de hehash
		       		
		        }	
				
		
			}

			
		}
	}
	else{
		cout<<"String not in the vector 2"<<endl;
		fatorDeCrescimento2 = (tamanho/entrada);
		entrada++;
		entrada2 = &entrada;
		if(fatorDeCrescimento2 <= 1.5 ){ // fator de crescimento = entrada/espaco na tabela hehash 
		    tabela = funcao_hehash(tabela,tamanho);
		   	tamanho = tamanho * 2;	
			alocacao(tabela,tamanho,a,funcao_hash(a,tamanho)); // fazer uma funcao de insercao que verifica condições de hehash
		    tamanho2 = &tamanho;
		       		
		} 
		      
		else{ //insercao simples
		      		
			alocacao(tabela,tamanho,a,funcao_hash(a,tamanho)); // fazer uma funcao de insercao que verifica condições de hehash
			

		}
	}

}
