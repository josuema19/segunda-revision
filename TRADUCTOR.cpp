#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h >

using namespace std;

const char *nombre_archivo = "archivo.dat";



struct Palabras{
	char pal_ing[20];
	char pal_esp[20];
	char pal_info[300];
};

struct Traduc{
	char cadena[500];
	
	
	
};

void abrir_palabra();
void ingresar_palabra();
void modificar_palabra();
void traducir();
void eliminar_palabra();

int main(){

    int opcion;
    
        system("cls");        
        
        cout << "\n\nMenu de Opciones" << endl;
        
        cout << "1. Leer palabras almacenadas" << endl;
        cout << "2. Ingresar nueva palabra" << endl;
        cout << "3. Modificar Palabra" << endl;
        cout << "4. Traducir texto" << endl;
        cout << "5. Eliminar" << endl;
        cout << "6. SALIR" << endl;
        
        cout << "\nIngrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                
                system("cls");
                abrir_palabra();
                break;
                
            case 2:
                
                system("cls");
                ingresar_palabra();
                break;
                
            case 3:
                
                system("cls");
				modificar_palabra();  
                break;
                
            case 4:
                
                system("cls");
				traducir();  
                break;
			    
            case 5:
                
                system("cls");
				eliminar_palabra();    
                break;
                
            case 6:
                
                system("cls");
				return 0;
				   
        }     
           
    return 0;
}

void abrir_palabra(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	if(!archivo) {
		archivo = fopen(nombre_archivo, "w+b");
	}
	Palabras palabras;
	int registro=1;
	fread ( &palabras, sizeof(Palabras), 1, archivo );
	do{
	cout<<"| No."<<registro<<" | \n"<<"Palabra original: "<< palabras.pal_ing <<"\nPalabra traducida: "<< palabras.pal_esp<<"\nDescripcion: "<<palabras.pal_info<<"\n"<<endl;
	
	fread ( &palabras, sizeof(Palabras), 1, archivo );
		registro += 1;	
		} while (feof( archivo ) == 0);
		
    cout<<endl;    
	fclose(archivo);
	
	_getch();
	main();
}

void ingresar_palabra(){
	
	char continuar;
	FILE* archivo = fopen(nombre_archivo, "ab");
	if(!archivo) {
		archivo = fopen(nombre_archivo, "w+b");
	}
	
		Palabras palabras;
		string pal_ing,pal_esp,pal_info;
		system("cls");
		
		do{
			fflush(stdin);
			
		cout<<"Ingrese palabra en ingles: ";
		getline(cin,pal_ing);
        strcpy(palabras.pal_ing, pal_ing.c_str()); 
        
		cout<<"Ingrese palabra en espanol: ";
		getline(cin,pal_esp);
    	strcpy(palabras.pal_esp, pal_esp.c_str()); 
    	
		cout<<"Ingrese definicion: ";
		getline(cin,pal_info);
    	strcpy(palabras.pal_info, pal_info.c_str()); 
		
		fwrite( &palabras, sizeof(Palabras), 1, archivo );
		
		cout<<"Desea agregar otra palabra S/N: ";
		cin>>continuar;
		}
		while((continuar=='s') || (continuar=='S'));
		
		
		fclose(archivo);
		
	_getch();
	main();
}

void modificar_palabra(){
	system("cls");
	
	FILE* archivo = fopen(nombre_archivo, "r+b");
	int id;
		
    	Palabras palabras;
		string pal_ing,pal_esp,pal_info;
    	
    	cout << "Ingrese el id que desea Modificar: ";
    	cin >> id;
    	id=id-1;
    	fseek ( archivo, id * sizeof(Palabras), SEEK_SET );
		
		//cout<<"Ingrese palabra en ingles: ";
		getline(cin,pal_ing);
        strcpy(palabras.pal_ing, pal_ing.c_str());
		
		cout<<"Ingrese palabra en ingles: ";
		getline(cin,pal_ing);
        strcpy(palabras.pal_ing, pal_ing.c_str()); 
        
		cout<<"Ingrese palabra en espanol: ";
		getline(cin,pal_esp);
    	strcpy(palabras.pal_esp, pal_esp.c_str()); 
    	
		cout<<"Ingrese definicion: ";
		getline(cin,pal_info);
    	strcpy(palabras.pal_info, pal_info.c_str());
    	
    	fwrite( &palabras, sizeof(Palabras), 1, archivo );
		fclose(archivo);
		
	_getch();
	main();	
}

void traductor(string& frase, string buscar,string rempl){
	int pos= frase.find(buscar);
	while (pos != -1){
		frase.replace(pos,buscar.size(),rempl);
		pos = frase.find(buscar, pos + rempl.size());
	}
}

void traducir(){
	system("cls");
	
	FILE* archivo = fopen(nombre_archivo, "rb");
	string frase;
	Palabras palabras;
	cout<<"Ingrese codigo para traducir: \n";
	cout<<"Ingrese el signo '$' al terminar"<<endl;
	getline(cin,frase,'$');
	
	fread(&palabras,sizeof(Palabras),1,archivo);	
	do{
		
		traductor(frase, palabras.pal_ing, palabras.pal_esp);
		fread ( &palabras, sizeof(Palabras), 1, archivo );
	} while (feof( archivo ) == 0);
	cout<<"\n\nEste es el codigo traducido: "<<endl;
	
	
	cout<<frase<<endl;
	fclose(archivo);
	
	_getch();
	main();
}



void eliminar_palabra(){
	system("cls");
	
	const char *nombre_temp = "temp.dat";
	int aux=0;
	char borrar[20];
	
	Palabras palabras;

	FILE* archivo = fopen(nombre_archivo, "rb");
	FILE* temp = fopen(nombre_temp, "wb");
	cout<<"ingrese palabra que desea borrar: ";
	cin>>borrar;
	
	while (fread(&palabras,sizeof(Palabras),1,archivo) != NULL) {
		if (strcmp (borrar, palabras.pal_ing) == 0) {
			cout<<"\nla palabra ha sido eliminada.";
			aux=1;
		} else {
			fwrite(&palabras, sizeof(Palabras), 1, temp);
		}
	}

	fclose(archivo);
	fclose(temp);

	remove("archivo.dat");
	rename("temp.dat", "archivo.dat");
	 
	
	_getch();
	main();
}


