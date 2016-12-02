#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <ctime>
#include <stdlib.h>     /* srand, rand */

using namespace std;

// Función que genera letras random.
char generarLetra()
{

	char arrayNum[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
	// Generamos un número random entre 0 y 27, para elegir un elemento del array.
	int RandIndex = rand() % 27;
	// Devolvemos la letra generada aleatoriamente. 
	return arrayNum[RandIndex];
}

// Clase configuración.
class Configuracion
{
	public:
		
		// Variables que recogemos del fichero de configuración.
		int nc;
		int ni;
		int ngen;
		int nres;
		int ntotal;
		float q;
		string target;
		string fichero;
		int longitud;
		
		// Función que lee el fichero de configuración, ya sea por filas o por columnas.
		void leer()
		{
			ifstream archivo;
			archivo.open(fichero+".cfg");
			// En caso de que haya un fichero. Leemos la primera línea, donde están los valores.
			if(archivo)
			{
				// Leemos cada fichero de configuración.
				archivo >> nc;
				archivo >> ni;
				archivo >> ngen;
				archivo >> nres;
				archivo >> ntotal;
				archivo >> q;
				
				// En caso de que falte un dato en el fichero de configuración. Sale del programa.
				if(nc==0 || ni==0 || ngen==0 || nres==0 || ntotal==0 || q==0)
				{
					cout<<"El fichero no tiene los valores necesarios.";
					archivo.close();
					exit(0);
				}
				
				else
				{
					cout<<"\nEl contenido del fichero es el siguiente.";
					cout<<"\nQ = "<< q;
					cout<<"\nNC = "<<nc;
					cout<<"\nNI = "<<ni;
					cout<<"\nNGEN = "<<ngen;
					cout<<"\nNRES = "<<nres;
					cout<<"\nNTOTAL = "<<ntotal<<endl<<endl;
				}
			}
			// Si no hay fichero.
			else 
			{
				cout<<"El fichero con el nombre introducido no está en este directorio.";
				archivo.close();
				exit(0);
			}
			archivo.close();
			//Generar poblacion de individuos aleatorios. Y calcular su fitness.
			//El fitness depende del nº de caracteres correctamente colocados comparado con el target.
			//Fórmula F[i]= e^(ncoincidencias-longitud)-e(-longitud)
			//for(int i=0; i<config.ni; i++ )
		}
}config;


// Clase individuo.
class Individuo
{
	public:
		
		string target; // Frase.
		string frase; // Valores aleatorios que se asignan a un individuo, genes.
		int coincidencias; // Coincidencias de sus genes con letras del target.
		float fi; // Fitness.
		
		// Un individuo recibe la frase y sus valores.
		Individuo(string frase, string target)
		{
			this->target=target;
			generarFrase(frase);
		}
		
		// Se pasan los valores al individuo.
		void generarFrase(string frase)
		{
			this->frase=frase;
			calcularCoincidencias();
		}
		
		// Se calculan las coincidencias de los genes con el target.
		void calcularCoincidencias()
		{
			int count = 0;
			// Comprueba cada caracter de frase con cada caracter de target y suma el contador.
			for(int i = 0; i < target.length(); i++)
			    if(frase.at(i) == target.at(i))
				count++;
				
			this->coincidencias = count;
			calcularFitness();
		}

		// Calcula el fitness.
		void calcularFitness()
		{
			// Formulita.
			int coincidencias = this->coincidencias;
			int longitud = this->target.size();
			
			/*cout<<"C: "<< coincidencias <<endl;
			cout<<"Ltar: "<< longitud <<endl;
			cout<<"C-Ltar: "<< coincidencias - longitud <<endl;*/
			this->fi = exp(coincidencias - longitud) - exp( - longitud);
			//cout<<" Fi: "<< this->fi << endl << endl;
		}
		
		// Función que comprueba si un individuo se replica, en base a un random.
		bool comprobarReplicacion(Individuo individuoActual, vector<Individuo> poblacion) 
		{
			float FaMax = 0;
			float FaActual = 0;
			//int random = rand() % 100;
			double probability = (rand()/(double)(RAND_MAX));
			// Compara cada individuo y actualiza el fitness máximo.
			for(int i = 0; i < poblacion.size(); i++)
			{
				Individuo individuo = poblacion.at(i);
				if((FaActual = individuo.fi) > FaMax)
					FaMax = FaActual;
			}
			/*
			cout << "famax: " << FaMax << "\n";
			cout<< "fi: " << individuoActual.fi<<endl;
			cout << "random: " << random << "\n";
			*/
			return ((individuoActual.fi)/FaMax) > probability;
		}

		// Función que genera una nueva frase, mutada.
		string mutar(string frase) 
		{
			string nuevaFrase = "";
			int random;
			char letra;
			// For que hace tantas pasadas como el tamaño de la frase.
			for(int i = 0; i < frase.length(); i++)
			{
				double probability = (rand()/(double)(RAND_MAX));
				//RANDOM ARREGLADO
				// Si el random es menor que la q le metemos la letra que hay en un individuo.
				if(probability < (config.q))
					nuevaFrase = nuevaFrase + frase.at(i);
				// Si no genera una frase nueva.
				else 
				{
					letra = generarLetra();
					nuevaFrase = nuevaFrase + letra;
				}
			}
			return nuevaFrase;
		}
};


// Clase Poblacion
class Poblacion
{
	public:
		
		vector<Individuo> individuos;
		
		// Genera los individuos en base al target.
		void generarIndividuos(string target) {
			// For que crea una nueva frase o conjunto de genes para cada individuo.		
			for(int i = 0; i < config.ni; i++)
			{
				string frase = "";
				// Genera una letra nueva por cada letra que tiene el target.
				for(int j = 0; j < target.length(); j++)
					frase += generarLetra();
				// Introducimos el individuo en el vector.
				Individuo* individuo = new Individuo(frase, target);
				individuos.push_back(*individuo);
			}
		}
};


// Clase que realiza los cálculos.
class Calculadora
{
	public:

		// Función que calcula el número de targets correctos en la población.
		int calcularTargets(vector<Individuo> poblacion)
		{
			int contador = 0;
			for(int i = 0; i < poblacion.size(); i++)
			{
				Individuo individuo = poblacion.at(i);
				// Suma el contador cuando un individuo tiene una frase igual que el target introducido.
				if(individuo.frase == config.target)
					contador++;
			}
			return contador;
		}
		
		// Calcular número coincidencias máximas
		int calcularCoincidenciasMaxima(vector<Individuo> poblacion)
		{
			int numCoincidenciasMax = 0;
			for(int i = 0; i < poblacion.size(); i++)
			{
				Individuo individuo = poblacion.at(i);
				// Actualizamos el número de coincidencias máximo.
				if(individuo.coincidencias > numCoincidenciasMax)
					numCoincidenciasMax = individuo.coincidencias;
			}
			return numCoincidenciasMax;
		}
		
		// Calcular número de coincidencias medio
		float calcularCoincidenciasMedia(vector<Individuo> poblacion)
		{
			float numCoincidenciasTotal = 0;
			for(int i = 0; i < poblacion.size(); i++)
			{
				Individuo individuo = poblacion.at(i);
				numCoincidenciasTotal = numCoincidenciasTotal + individuo.coincidencias;
			}
			// Todas de coincidencias entre población.
			return (numCoincidenciasTotal/poblacion.size());
		}
		
		// Calcular mejor individuo
		int calcularMejorIndividuo(vector<Individuo> poblacion)
		{
			int posicion = 0;
			int numCoincidenciasMax = 0;
			for(int i = 0; i < poblacion.size(); i++)
			{
				Individuo individuo = poblacion.at(i);
				// Actualizamos el número de coincidencias máximo.
				if(individuo.coincidencias > numCoincidenciasMax)
				{
					numCoincidenciasMax = individuo.coincidencias;
					posicion = i;
				}
			}
			return posicion;
		}
		
		// Calcular consenso.
		string calcularConsenso(vector<Individuo> poblacion)
		{
			char arrayNum[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
			int abecedario[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
			string consenso;
			int posicion;
			char letra;
			const int N = sizeof(abecedario) / sizeof(int);
			// Recorro cada letra.
			for(int i = 0; i< config.target.length(); i++)
			{	
				// Recorro cada individuo.
				for(int j = 0; j < poblacion.size(); j++)
				{
					Individuo individuo = poblacion.at(j);
					//cout<<individuo.frase;
					letra = individuo.frase.at(i);
					// Comprueba que letra es y aumento el contador.
					for(int k = 0; k < 27; k++)
					{
						if(arrayNum[k]==letra)
						{
							//cout<<arrayNum[k]<<endl;
							abecedario[k]++;
							//cout<<"Cantidad de veces en posicion k="<<i<<" Cantidad:"<<abecedario[k]<<" Letra: "<<arrayNum[k]<<endl;
						}
					}
					//cout<<letra<<endl;
				}
				// Calcula la posición del mayor valor.
				posicion = distance(abecedario, max_element(abecedario, abecedario + N));
				// Le suma la letra en la posición calculada previamente.
				consenso += arrayNum[posicion];
				
				//Reiniciamos el array de contadores.
				for(int j = 0; j < 27; j++)
				{
					abecedario[j]=0;
				}

			}
			//cout<<abecedario;
			
			return consenso;
		}
		
}calculadora;


// Clase que escribe en el fichero de salida los resultados y también los muestra por pantalla.
class Escritor
{
	public:
		
		// Archivo de salida.
		ofstream archivo;
		// Función que escribe la cabecera.
		void escribirCabecera()
		{
			// current date/time based on current system
			time_t now = time(0);
			tm *ltm = localtime(&now);
			
			archivo.open(config.fichero + ".txt");
			cout<<"GR-05: Xabier Zulueta, Diego Martínez Garrote, Juan José Martínez"<<endl;
			archivo<<"GR-05: Xabier Zulueta, Diego Martínez Garrote, Juan José Martínez"<<endl;
			cout<<ltm->tm_hour <<":"<< ltm->tm_min <<":"<< ltm->tm_sec <<" Día: " <<  ltm->tm_mday <<" Mes: "<<1+ltm->tm_mon<<" Año: "<< 1900 + ltm->tm_year<<endl<<endl;
			archivo << ltm->tm_hour <<":"<< ltm->tm_min <<":"<< ltm->tm_sec <<" Día: " <<  ltm->tm_mday <<" Mes: "<<1+ltm->tm_mon<<" Año: "<< 1900 + ltm->tm_year<<endl<<endl;
			archivo<<"Target introducido: "<<config.target<<endl<<endl;
			cout<<"Target introducido: "<<config.target<<endl<<endl;
			archivo<<"<-- Valores recogidos del archivo '"<<config.fichero<<".cfg' -->"<<endl;
			cout<<"<-- Valores recogidos del archivo '"<<config.fichero<<".cfg' -->"<<endl;
			archivo<<"Ltar: "<<config.longitud<<endl;
			cout<<"Ltar: "<<config.longitud<<endl;
			archivo<<"NC: "<<config.nc<<endl;
			cout<<"NC: "<<config.nc<<endl;
			archivo<<"NI: "<<config.ni<<endl;
			cout<<"NI: "<<config.ni<<endl;
			archivo<<"NTOTAL: "<<config.ntotal<<endl;
			cout<<"NTOTAL: "<<config.ntotal<<endl;
			archivo<<"Q: "<<config.q<<endl<<endl;
			cout<<"Q: "<<config.q<<endl<<endl;
		}
		
		// Función que escribe por cada generación.
		void escribirResumen(int generacion, vector<Individuo> poblacion)
		{
			int maximas, media, targets;
			double porcentaje;
			int tamano;
			int posicion;
			string consenso;
			maximas = calculadora.calcularCoincidenciasMaxima(poblacion);
			targets = calculadora.calcularTargets(poblacion);
			media = calculadora.calcularCoincidenciasMedia(poblacion);
			posicion = calculadora.calcularMejorIndividuo(poblacion);
			archivo<<"<-- RESUMEN GENERACIÓN ("<< generacion<< ") -->"<<endl;
			cout<<"<-- RESUMEN GENERACIÓN ("<< generacion<< ") -->"<<endl;
			// Preguntar si es el mejor target o qué es.
			//archivo<<"Mejor individuo";
			tamano = poblacion.size();
			porcentaje = (maximas*(float)(tamano/100.0));
			Individuo individuo = poblacion.at(posicion);
			archivo<<"Mejor individuo: "<<individuo.frase<<endl;
			// Creo que es porcentaje del target, no de la población. Preguntar.
			archivo<<"Nº de coincidencias máximo: "<<maximas<<" - "<<(maximas/(config.target.size()/100.0))<<"%"<<endl;
			cout<<"Nº de coincidencias máximo: "<<maximas<<" - "<<(maximas/(config.target.size()/100.0))<<"%"<<endl;
			archivo<<"Nº de targets: "<<targets<<endl;
			cout<<"Nº de targets: "<<targets<<endl;
			//archivo<<"Individuo consenso";
			consenso = calculadora.calcularConsenso(poblacion);
			cout<<"Individuo consenso: "<<consenso<<endl;
			archivo<<"Individuo consenso: "<<consenso<<endl;
			porcentaje = (media * (float)(tamano/100.0));
			// Idem aqui.
			archivo<<"Nº de coincidencias medio: "<<media<<" - "<<media/(config.target.size()/100.0)<<"%"<<endl;
			cout<<"Nº de coincidencias medio: "<<media<<" - "<<media/(config.target.size()/100.0)<<"%"<<endl<<endl;

		}
		
		// Función que escribe cada NTOTAL.
		void escribirPoblacion(vector<Individuo> poblacion) 
		{
			archivo<<endl<<"<-- POBLACIÓN TOTAL (20%) -->"<<endl;
			cout<<"<-- POBLACIÓN TOTAL (20%) -->"<<endl;
			int porciento;
			porciento = (poblacion.size() * 20)/100;
			// Mostramos únicamente el 20% de la población.
			for(int i = 0; i < poblacion.size(); i++)
			{
				// Para mostrar 20 de 100, 10 de 50.
				if(i % 5 == 0)
				{
					Individuo individuo = poblacion.at(i);
					archivo<<individuo.frase<<endl;
					cout<<individuo.frase<<endl;
				}
			}
			archivo<<endl;
			cout<<endl;
		}
		
		void cerrarArchivo()
		{
			archivo.close();
		}
};


//individuo=frase parecida al target. un gen una letra. mutar gen cambiar de letra.
//contar cuantos digitos tiene la frase introducida.
//random alfabeto mas el blanco.

int main(int argc, char *argv[]) {

	// Declaramos las variables.
	srand(time(0));
	string target, nombreFichero;
	Escritor escritor;
	bool estado;

	// Recogemos el target.
	cout <<"Introduzca el target: ";
	getline( cin, target);
	
	// Poner el target en mayúsculas.
	transform(target.begin(), target.end(), target.begin(), ::toupper);
	cout <<"Target introducido: "<<target;
	config.target = target;
	
	// Calculamos longitud frase.
	config.longitud = target.length();
	cout <<"\nIntroduzca el nombre de fichero: ";
	getline( cin, config.fichero);
	
	// Leemos el fichero de configuración.
	config.leer();
	
	//Llamamos a escritor y a la función que escribe la cabecera.
	escritor.escribirCabecera();
	
	// Generamos la población.
	Poblacion* poblacion = new Poblacion();
	poblacion->generarIndividuos(target);//1 y 2

	// Para cada generación. //CONDICION
	for(int generacion = 1 ; generacion <= config.ngen; generacion++)
	{
		// Calculamos el individuo inicial con un random.
		int offset = rand() % poblacion->individuos.size();
		int contador = 0;
		
		while(contador < poblacion->individuos.size())
		{
			// Numero de individuo aleatorio.
			int numindividuo = (contador+offset) % poblacion->individuos.size();
			
			Individuo individuo = poblacion->individuos.at(numindividuo);
			estado = individuo.comprobarReplicacion(individuo, poblacion->individuos);
			// Probar si cada padre se replica.
			// Si se replica entonces lo mutamos.
			if(estado == true)
			{
				string mutada = "";
				// Generar frase mutada.
				mutada = individuo.mutar(individuo.frase);
				
				int nuevo; 
				nuevo = rand() % config.ni;
				// Sustituir nuevo individuo por cualquier individuo existente aleatorio.
				poblacion->individuos.at(nuevo).generarFrase(mutada);			
			}
			contador++;
		}
		// Imprimir cada nres.
		if(generacion % config.nres == 0)
			escritor.escribirResumen(generacion, poblacion->individuos);
		// Imprimir cada total.
		if(generacion % config.ntotal == 0)
			escritor.escribirPoblacion(poblacion->individuos);
		
	}
	escritor.escribirPoblacion(poblacion->individuos);
	escritor.escribirResumen(config.ngen, poblacion->individuos);
	escritor.cerrarArchivo();

	return 0;
}