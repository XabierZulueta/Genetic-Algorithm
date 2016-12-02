
public class Individuo {

	private String target; // Frase.
	private String frase; // Valores aleatorios que se asignan a un individuo, genes.
	private int coincidencias; // Coincidencias de sus genes con letras del target.
	private double fi; // Fitness.
	
	public String getTarget() {
		return target;
	}

	public void setTarget(String target) {
		this.target = target;
	}

	public String getFrase() {
		return frase;
	}

	public void setFrase(String frase) {
		this.frase = frase;
	}

	public int getCoincidencias() {
		return coincidencias;
	}

	public void setCoincidencias(int coincidencias) {
		this.coincidencias = coincidencias;
	}

	public Double getFi() {
		return fi;
	}

	public void setFi(float fi) {
		this.fi = fi;
	}

	public Individuo(String frase, String target)
	{
		this.target = target;
		this.frase= frase;
		this.coincidencias = calcularCoincidencias();
		this.fi = calcularFitness();
	}
	
	public int calcularCoincidencias()
	{
		int count = 0;
		// Comprueba cada caracter de frase con cada caracter de target y suma el contador.
		for(int i = 0; i < this.target.length(); i++){
		    if(this.frase.charAt(i) == this.target.charAt(i))
		    	count++;}
		this.coincidencias=count;
		return coincidencias;
	}
	
	public double calcularFitness()
	{
		this.fi =(Math.pow(Math.E,(this.coincidencias-target.length())))- ( Math.pow(Math.E, -target.length()));
		return fi;
	}


}
