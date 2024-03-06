import java.util.Scanner;
import java.util.Locale;

public class InputHandler {
    private final Scanner scanner;

    public InputHandler() {
        this.scanner = new Scanner(System.in).useLocale(Locale.US);
    }

    public double getDouble(String prompt) {
        while (true) {
            System.out.println(prompt);
            try {
                return scanner.nextDouble();
            } catch (Exception e) {
                System.out.println("Введены некорректные данные. Пожалуйста, введите число.");
                scanner.next();
            }
        }
    }

    public int getInt(String prompt) {
        while (true) {
            System.out.println(prompt);
            try {
                return scanner.nextInt();
            } catch (Exception e) {
                System.out.println("Введены некорректные данные. Пожалуйста, введите целое число.");
                scanner.next();
            }
        }
    }

    public int getThreadCount(String prompt) {
        while (true) {
            System.out.println(prompt);
            try {
                int threadCount = scanner.nextInt();
                if (threadCount == 1 || threadCount == 2 || threadCount == 4) {
                    return threadCount;
                } else {
                    System.out.println("Недопустимое количество потоков. Пожалуйста, введите 1, 2 или 4.");
                }
            } catch (Exception e) {
                System.out.println("Введены некорректные данные. Пожалуйста, введите целое число.");
                scanner.next();
            }
        }
    }
}
