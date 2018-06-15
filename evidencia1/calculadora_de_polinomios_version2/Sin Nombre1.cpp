#include <iostream>
#include <cstdlib>

using namespace std;

class Polinomio{
public:
	int grado;
	Polinomio(){coef = new double[1];grado=0;coef[grado]=0;};
	
	~Polinomio(){delete [] coef;}
	void input();
	void output();
	void reset(int ndeg);
	void add(const Polinomio& pol);
	void subtract(const Polinomio& pol);
	void mult(const Polinomio& pol);
	void div(const Polinomio& divisor, const Polinomio& quotient, const Polinomio& remainder);
	friend Polinomio operator+(const Polinomio&, const Polinomio&); 
	friend istream& operator>>(istream&, Polinomio&); 
	friend ostream& operator<<(ostream&, const Polinomio &); 
private:
	double* coef;
	
	Polinomio(const Polinomio& base, double scalar,int mgrado);
	Polinomio(const Polinomio& base, const Polinomio& divypol);
	void checkandreduce(); 

};

void Polinomio::reset(int ndeg){
	grado = ndeg;
	delete [] coef;
	coef = new double[ndeg+1];
	for(int r=ndeg; r>=0; r--){
		coef[r] = 0;
	}
}

void Polinomio::checkandreduce(){
	for(int kl = grado; kl>=0; kl--){
		if(coef[kl]==0)continue;
		else{
			grado = kl;
			break;
		}
	}
}

ostream& operator <<(ostream& output, const Polinomio& pol){
	int cgrado;
    int first = 0;
    cgrado = pol.grado+1;
    while (cgrado>0){
        cgrado--;
        if(pol.coef[cgrado]==0)continue;
        if(pol.coef[cgrado]>0){
            if((cgrado==0) && (first==0)){
                output<< pol.coef[cgrado];
                first=1;
                continue;
            }
            if((cgrado==0) && (first==1)){
                output<< "+" << pol.coef[cgrado];
                continue;
            }
            if((cgrado==1) && (first==0) && (pol.coef[cgrado]!=1)){
                output<< pol.coef[cgrado]<<"*x";
                first=1;
                continue;
            }
            if((cgrado==1) && (first==1)&&(pol.coef[cgrado]!=1)){
                output<< "+" << pol.coef[cgrado]<<"*x";
                continue;
            }
            if((cgrado==1) && (first==0) && (pol.coef[cgrado]==1)){
                output<< "x";
                first=1;
                continue;
            }
            if((cgrado==1) && (first==1)&&(pol.coef[cgrado]==1)){
                output<< "+" << "x";
                continue;
            }
            if((first==0)&&(pol.coef[cgrado]==1)){
                output << "x^" << cgrado;
                first=1;
                continue;
            }
            if((first==1)&&(pol.coef[cgrado]==1)){
                output << "+x^" << cgrado;
                continue;
            }
            if(first==0){
                output << pol.coef[cgrado] << "*x^" << cgrado;
                first=1;
                continue;
            }
            if(first==1){
                output << "+" << pol.coef[cgrado] << "*x^" << cgrado;
                continue;
            }
        }
        if(pol.coef[cgrado]<0){
            if(cgrado==0){
                output<< pol.coef[cgrado];
                first=1;
                continue;
            }
            if((cgrado==1)&&(pol.coef[cgrado]==-1)){
                output<< "-x";
                first=1;
                continue;
            }
            if(pol.coef[cgrado]==-1){
                output << "-x^" << cgrado;
                first=1;
                continue;
            }
            else{
                output << pol.coef[cgrado] << "*x^" << cgrado;
                first=1;
                continue;
			}
		}
		
	}	
	return output;
}

Polinomio operator +(const Polinomio& pol1, const Polinomio& pol2){
	Polinomio finpol;
	if(pol1.grado<=pol2.grado)finpol.reset(pol2.grado);
	if(pol1.grado>pol2.grado)finpol.reset(pol1.grado);
	finpol.add(pol1);
	finpol.add(pol2);
	return finpol;
}

Polinomio operator -(const Polinomio& pol1, const Polinomio& pol2){
	Polinomio finpol2;
	if(pol1.grado<=pol2.grado)finpol2.reset(pol2.grado);
	if(pol1.grado>pol2.grado)finpol2.reset(pol1.grado);
	finpol2.add(pol1);
	finpol2.subtract(pol2);
	return finpol2;
}

Polinomio operator *(const Polinomio& pol1, const Polinomio& pol2){
	Polinomio finpol3;
	finpol3.reset(pol2.grado+pol1.grado);
	finpol3.add(pol1);
	finpol3.mult(pol2);
	return finpol3;
}

Polinomio operator /(const Polinomio& pol1, const Polinomio& pol2){
	Polinomio finpol3;
	Polinomio quotient;
	Polinomio rem;
	finpol3.reset(pol1.grado);
	cout << endl << "reset: " << finpol3 << endl;
	quotient.reset(pol1.grado-pol2.grado);
	rem.reset(pol1.grado-pol2.grado);
	finpol3.add(pol1);
	cout << endl << "add pol1: " << finpol3 << endl;
	
	finpol3.div(pol2,quotient,rem);
	cout << endl << "div pol2: " << finpol3 << endl;
	return finpol3;
}

Polinomio operator %(const Polinomio& pol1, const Polinomio& pol2){
	Polinomio finpol4;
	Polinomio quotient;
	Polinomio rem;
	finpol4.reset(pol1.grado-pol2.grado);
	cout << endl << "reset: " << finpol4 << endl;
	quotient.reset(pol1.grado-pol2.grado);
	rem.reset(pol1.grado-pol2.grado);
	finpol4.add(pol1);
	cout << endl << "add pol1: " << finpol4 << endl;
	finpol4.div(pol2,quotient,rem);
	cout << endl << "div pol2: " << finpol4 << endl;
	rem.reset(pol1.grado);
	rem.add(pol1);
	finpol4.mult(pol2);
	rem.subtract(finpol4);
	return finpol4;
}

Polinomio::Polinomio(const Polinomio& base, double scalar, int mgrado){
	grado = base.grado + mgrado;
    int i = grado;
	int j = base.grado;
    grado = base.grado+mgrado;
	coef = new double[grado+1];
    do{
		coef[i] = scalar * base.coef[j];
		i--;
		j--;
	}while((i>=0)&&(j>=0));
}

void Polinomio::add(const Polinomio& pol){
    int ngrado = grado;
    int agrado = pol.grado;
    do{
		if(ngrado==agrado){
			while(ngrado>=0){
				coef[ngrado] = coef[ngrado] + pol.coef[ngrado];
				ngrado--;
			}
			break;
		}
		if(ngrado>agrado){
			while(ngrado!=agrado){
				ngrado--;
			}
			while(ngrado>=0){
				coef[ngrado] += pol.coef[ngrado];
				ngrado--;
			}
			break;
		}
		if(ngrado<agrado){
			grado=agrado;
			while(ngrado!=agrado){
				coef[agrado] = pol.coef[agrado];
				agrado--;
			}
			while(ngrado>=0){
				coef[ngrado] += pol.coef[ngrado];
				ngrado--;
			}
			break;
		}
    }while(ngrado>=0);
}

void Polinomio::subtract(const Polinomio& pol){
    int ngrado = grado;
    int sgrado = pol.grado;
    do{
		if(ngrado==sgrado){
			while(ngrado>=0){
				coef[ngrado] = coef[ngrado] - pol.coef[ngrado];
				ngrado--;
			}
			break;
		}
		if(ngrado>sgrado){
			while(ngrado!=sgrado){
				ngrado--;
			}
			while(ngrado>=0){
				coef[ngrado] -= pol.coef[ngrado];
				ngrado--;
			}
			break;
		}
		if(ngrado<sgrado){
			grado=sgrado;
			while(ngrado!=sgrado){
				coef[sgrado] = pol.coef[sgrado]*-1;
				sgrado--;
			}
			while(ngrado>=0){
				coef[ngrado] -= pol.coef[ngrado];
				ngrado--;
			}
			break;
		}
    }while(ngrado>=0);
}

void Polinomio::mult(const Polinomio& pol){
    Polinomio multypol;
    multypol.reset(pol.grado+grado);
    for(int i = pol.grado; i >= 0; i--){
		Polinomio tmp(*this,pol.coef[i],i);
		multypol.add(tmp);
	}
    reset(multypol.grado);
    for(int finaldeg = grado+1; finaldeg >= 0; finaldeg--){
        coef[finaldeg] = multypol.coef[finaldeg];
    }
}

void Polinomio::div(const Polinomio& divy, const Polinomio& quo, const Polinomio& rem){
	Polinomio divypoly = *this;
	Polinomio resulta;
	grado = divypoly.grado-divy.grado;
	resulta.reset(grado);
	for(int i = grado; i >=0; i--){
		divypoly.checkandreduce();
		Polinomio tmp(divypoly,divy);
		resulta.add(tmp);
		tmp.mult(divy);
		divypoly.subtract(tmp);
	}
	cout << resulta;
	*this = resulta;
	output();
}
	
Polinomio::Polinomio(const Polinomio& divypoly, const Polinomio& divy){
	grado = (divypoly.grado-divy.grado);
	coef = new double[(grado+1)];
	coef[grado]=divypoly.coef[divypoly.grado]/divy.coef[divy.grado];
	for(int j=(grado-1);j>=0;j--){
		coef[j]=0;
	}
}

void Polinomio::input(){ 
    int cgrado;
    cin >> grado;
    cgrado = grado;
    delete [] coef;
    coef=new double [cgrado+1];
    while (cgrado>=0){
        cin >> coef[cgrado];
        cgrado--;
    }
}

void Polinomio::output(){ 
    int cgrado;
    int first = 0;
    cgrado = grado+1;
    while (cgrado>0){
        cgrado--;
        if(coef[cgrado]==0)continue;
        if(coef[cgrado]>0){
            if((cgrado==0) && (first==0)){
                cout<< coef[cgrado];
                first=1;
                continue;
            }
            if((cgrado==0) && (first==1)){
                cout<< "+" << coef[cgrado];
                continue;
            }
            if((cgrado==1) && (first==0) && (coef[cgrado]!=1)){
                cout<< coef[cgrado]<<"*x";
                first=1;
                continue;
            }
            if((cgrado==1) && (first==1)&&(coef[cgrado]!=1)){
                cout<< "+" << coef[cgrado]<<"*x";
                continue;
            }
            if((cgrado==1) && (first==0) && (coef[cgrado]==1)){
                cout<< "x";
                first=1;
                continue;
            }
            if((cgrado==1) && (first==1)&&(coef[cgrado]==1)){
                cout<< "+" << "x";
                continue;
            }
            if((first==0)&&(coef[cgrado]==1)){
                cout << "x^" << cgrado;
                first=1;
                continue;
            }
            if((first==1)&&(coef[cgrado]==1)){
                cout << "+x^" << cgrado;
                continue;
            }
            if(first==0){
                cout << coef[cgrado] << "*x^" << cgrado;
                first=1;
                continue;
            }
            if(first==1){
                cout << "+" << coef[cgrado] << "*x^" << cgrado;
                continue;
            }
        }
        if(coef[cgrado]<0){
            if(cgrado==0){
                cout<< coef[cgrado];
                first=1;
                continue;
            }
            if((cgrado==1)&&(coef[cgrado]==-1)){
                cout<< "-x";
                first=1;
                continue;
            }
            if(coef[cgrado]==-1){
                cout << "-x^" << cgrado;
                first=1;
                continue;
            }
            else{
                cout << coef[cgrado] << "*x^" << cgrado;
                first=1;
                continue;
			}
		}
		
	}
}

int main()
{
    Polinomio poly1,poly2;
	char choice;
    int done = 0;
    cout << "Calculadora de polinomios" << endl;
    do{
        cout << endl << endl <<"0. salir"
        << endl <<"1. definicion de polinomios"
        << endl <<"2. Suma"
        << endl <<"3. Resta"
        << endl <<"4. Multiplicacion"
        << endl <<"5. Division"
        << endl <<"-------------------" << endl << endl;
		
		
        do{
            cout << "Elige una opcion: ";
            cin >> choice;
            if((choice!='6') && (choice!='5') && (choice!='4') && (choice!='3')
			   && (choice!='2') && (choice!='1') && (choice!='0')){
                cout << "'" << choice << "Opcion invalida"<< endl;
            }
        }while((choice!='6') && (choice!='5') && (choice!='4') && (choice!='3')
			   && (choice!='2') && (choice!='1') && (choice!='0'));
        if(choice=='0')exit(1);
        if(choice=='1'){
			cout << "ingrese los coeficientes del primer polinomio : ";
            poly1.input();
            cout << "ingrese los coeficientes del segundo polinomio : ";
			poly2.input();
			done=1;
        }
        if(choice=='2'){
            if(done==0){
                cout << "introdusca su primer polinomio" << endl;
                continue;
            }
			cout << "(" << poly1 << ")+(" << poly2 << ")=" << (poly1+poly2);
        }
        if(choice=='3'){
            if(done==0){
                cout << "introdusca su primer polinomio" << endl;
                continue;
            }
			cout << "(" << poly1 << ")-(" << poly2 << ")=" << (poly1-poly2);
        }
        if(choice=='4'){
            if(done==0){
                cout << "introdusca su primer polinomio" << endl;
                continue;
            }
			cout << "(" << poly1 << ")*(" << poly2 << ")=" << (poly1*poly2);
        }
        if(choice=='5'){
            if(done==0){
                cout << "introdusca su primer polinomio" << endl;
                continue;
            }
			cout << "(" << poly1 << ")/(" << poly2 << ")=" << (poly1/poly2);
        }
        if(choice=='6'){
            if(done==0){
                cout << "introduzca su primer polinomio" << endl;
                continue;
            }
			cout << "(" << poly1 << ")%(" << poly2 << ")=" << (poly1%poly2);
        }
    }while(choice!=0);
	
	
	return 0;
}

