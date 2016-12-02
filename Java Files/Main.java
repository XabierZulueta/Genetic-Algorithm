import java.io.IOException;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) throws IOException {
		String target;
		Scanner scanner = new Scanner(System.in);
        System.out.print("Introduzca el target: ");
        target=scanner.nextLine();
        target = target.toUpperCase();
        System.out.println("Target introducido: "+target);
		Poblacion poblacion = new Poblacion(target);
		
	}
}
