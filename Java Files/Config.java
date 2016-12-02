import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.Date;
import java.util.Properties;

public class Config {

	public int nc;
	private int ni;
	public int ngen;
	public int nres;
	public int ntotal;
	public double q;
	public String target;
	public String fichero;
	public int longitud;
	private String result = "";
	private InputStream inputStream;
	
	
	public void leer() throws IOException
	{
		try {
			Properties prop = new Properties();
			String propFileName = "configuracion.properties";
 
			inputStream = getClass().getClassLoader().getResourceAsStream(propFileName);
 
			if (inputStream != null) {
				prop.load(inputStream);
			} else {
				throw new FileNotFoundException("property file '" + propFileName + "' not found in the classpath");
			}
			String ni = prop.getProperty("ni");
			this.ni=Integer.parseInt(ni);
			String nc = prop.getProperty("nc");
			this.nc=Integer.parseInt(nc);
			String ngen = prop.getProperty("ngen");
			this.ngen=Integer.parseInt(ngen);
			String q = prop.getProperty("q");
			this.q=Double.parseDouble(q);
			String nres = prop.getProperty("nres");
			this.nres=Integer.parseInt(nres);
			String ntotal = prop.getProperty("ntotal");
			this.ntotal=Integer.parseInt(ntotal);
			System.out.println("Q = "+this.q);
			System.out.println("NC = "+this.nc);
			System.out.println("NI = "+this.ni);
			System.out.println("NGEN = "+this.ngen);
			System.out.println("NRES = "+this.nres);
			System.out.println("NTOTAL = "+this.ntotal);
		} catch (Exception e) {
			System.out.println("Exception: " + e);
		} finally {
			inputStream.close();
		}
	}
	
	public Config(String target) throws IOException {
		leer();
		this.target = target;
		setTarget(target);
	}
	public int getNc() {
		return nc;
	}
	public void setNc(int nc) {
		this.nc = nc;
	}
	public int getNi() {
		return ni;
	}
	public void setNi(int ni) {
		this.ni = ni;
	}
	public int getNgen() {
		return ngen;
	}
	public void setNgen(int ngen) {
		this.ngen = ngen;
	}
	public int getNres() {
		return nres;
	}
	public void setNres(int nres) {
		this.nres = nres;
	}
	public int getNtotal() {
		return ntotal;
	}
	public void setNtotal(int ntotal) {
		this.ntotal = ntotal;
	}
	public double getQ() {
		return q;
	}
	public void setQ(float q) {
		this.q = q;
	}
	public String getTarget() {
		return target;
	}
	public void setTarget(String target) {
		this.target = target;
	}
	public String getFichero() {
		return fichero;
	}
	public void setFichero(String fichero) {
		this.fichero = fichero;
	}
	public int getLongitud() {
		return longitud;
	}
	public void setLongitud(int longitud) {
		this.longitud = longitud;
	}
	
}
