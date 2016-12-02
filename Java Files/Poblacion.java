import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class Poblacion {
	private ArrayList<Individuo> individuos=new ArrayList<>();
	private Escritor escritor;
	private Config config;
	public String target;
	public List<Character> abecedario = new ArrayList<>(Arrays.asList(new Character[] {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '}));
	
	public char generarLetra()
	{
		return abecedario.get(new Random().nextInt(abecedario.size()));
		
	}
	
	public void generarPoblacion(){
		Individuo individuo;
		for(int i = 0; i < config.getNi(); i++)
		{
			String frase = "";
			// Genera una letra nueva por cada letra que tiene el target.
			for(int j = 0; j < config.getTarget().length(); j++)
				frase += generarLetra();
			// Introducimos el individuo en el vector.
			individuo = new Individuo(frase, config.getTarget());
			individuos.add(individuo);
		}
	}

	public Poblacion(String target) throws IOException{
		config=new Config(target);
		this.target=target;
		escritor = new Escritor(this);
		generarPoblacion();
		boolean estado=true;
		for(int generacion = 1 ; generacion <= config.getNgen(); generacion++)
		{
			int offset = new Random().nextInt(individuos.size());
            int contador = 0;

            // Loop por todos los individuos, empezando aleatoriamente y llegando hasta el anterior.
            while(contador < individuos.size())
            {
                Individuo individuo = individuos.get((contador + offset) % individuos.size());

                // Probar si cada padre se replica
                if(comprobarReplicacion(individuo))
                {
                    Individuo nuevoIndividuo = new Individuo(mutar(individuo), config.target);

                    // Sustituir nuevo individuo por cualquier individuo existente aleatorio.
                    individuos.set(new Random().nextInt(individuos.size()), nuevoIndividuo);
                }

                // Aumentamos el contador, pasamos al siguiente individuo de la población.
                contador++;
            }

            // Imprimir resumen cada NRES generaciones
            if(generacion % config.nres == 0){
                escritor.imprimirResumen(generacion);
            }


            // Imprimir poblaciones cada NTOTAL generaciones
            if(generacion % config.ntotal == 0){
            	 escritor.imprimirPoblacion();
            }
               
        }

		escritor.imprimirPoblacion();
		escritor.imprimirResumen(config.ngen);
			}
		
	// Función que calcula el número de targets correctos en la población.
	public int calcularTargets()
	{
		int contador = 0;
		for(int i = 0; i < individuos.size(); i++)
		{
			Individuo individuo = individuos.get(i);
			// Suma el contador cuando un individuo tiene una frase igual que el target introducido.
			if(individuo.getFrase().equals(config.target)){
				contador++;
			}
		}
		return contador;
	}
	// Calcular número coincidencias máximas
	public int calcularCoincidenciasMaxima()
	{
		int numCoincidenciasMax = 0;
		for(int i = 0; i < individuos.size(); i++)
		{
			Individuo individuo = individuos.get(i);
			// Actualizamos el número de coincidencias máximo.
			if(individuo.getCoincidencias() > numCoincidenciasMax)
				numCoincidenciasMax = individuo.getCoincidencias();
		}
		return numCoincidenciasMax;
	}
	// Calcular número de coincidencias medio
	public float calcularCoincidenciasMedia()
	{
		float numCoincidenciasTotal = 0;
		for(int i = 0; i < individuos.size(); i++)
		{
			Individuo individuo = individuos.get(i);
			numCoincidenciasTotal = numCoincidenciasTotal + individuo.getCoincidencias();
		}
		// Todas de coincidencias entre población.
		return (numCoincidenciasTotal/individuos.size());
	}
	// Calcular mejor individuo
	public int calcularMejorIndividuo()
	{
		int posicion = 0;
		int numCoincidenciasMax = 0;
		for(int i = 0; i < individuos.size(); i++)
		{
			Individuo individuo = individuos.get(i);
			// Actualizamos el número de coincidencias máximo.
			if(individuo.getCoincidencias() > numCoincidenciasMax)
			{
				numCoincidenciasMax = individuo.getCoincidencias();
				posicion = i;
			}
		}
		return posicion;
	}
	// Función que comprueba si un individuo se replica, en base a un random.
	public boolean comprobarReplicacion(Individuo individuoActual) 
	{
		Double FaMax = 0d;
		Double FaActual = 0d;

        for(Individuo individuo : individuos)
        {
            if((FaActual = individuo.getFi()) > FaMax)
                FaMax = FaActual;
        }

        return (individuoActual.getFi() / FaMax) > new Random().nextFloat();
	}
	
	// Función que genera una nueva frase, mutada.
	public String mutar(Individuo individuo) 
	{
		 String nuevoValor = "";
	        for(int i = 0; i < individuo.getFrase().length(); i++)
	            if(new Random().nextFloat() < config.q)
	                nuevoValor += individuo.getFrase().charAt(i);
	            else
	                nuevoValor += generarLetra();;

	        return nuevoValor;
	}
	public ArrayList<Individuo> getIndividuos() {
		return individuos;
	}

	public void setIndividuos(ArrayList<Individuo> individuos) {
		this.individuos = individuos;
	}

}
