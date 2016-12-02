import java.io.IOException;

public class Escritor {

	private Poblacion poblacion;
	private Config config;
	
	public Escritor(Poblacion poblacion) throws IOException
	{
		this.poblacion=poblacion;
	}
	
	public void imprimirResumen(int generacionActual) {
		escribir("");
		escribir("<-- RESUMEN GENERACIÓN (" + generacionActual + ") -->");
		escribir("Mejor individuo: "+poblacion.getIndividuos().get(poblacion.calcularMejorIndividuo()).getFrase());
		escribir("Nº de coincidencias máximo: " +  poblacion.calcularCoincidenciasMaxima());
       // escribir("Individuo consenso: " +  poblacion.generarFraseConsenso());
        escribir("Nº de targets: " + poblacion.calcularTargets());
        escribir("Nº de coincidencias medio: " +  poblacion.calcularCoincidenciasMedia());
        escribir("");
    }

    public void imprimirPoblacion() {
    	escribir("");
        escribir("<-- POBLACIÓN TOTAL (20%) -->");
        for(int i=0;i<poblacion.getIndividuos().size();i++)
        {
        	if(i%5==0)
        	escribir(poblacion.getIndividuos().get(i).getFrase());
        }
        escribir("");
    }

    public void escribir(String texto)
    {
        System.out.println(texto);

    }
}
