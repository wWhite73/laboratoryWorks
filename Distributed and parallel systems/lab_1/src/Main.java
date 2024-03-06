public class Main {
    public static void main(String[] args) {

        InputHandler inputHandler = new InputHandler();
        Function[] functions = {new ExpSinFunction(), new SinFunction(), new CosFunction(), new ExpCosFunction()};
        String[] functionNames = {"e^x*sin(y)", "sin(x+2y)", "cos(x·e^y)", "exp(cos(x^2+y))"};
        System.out.print("\033[0;31m");
        double a = inputHandler.getDouble("Введите значение a:");
        double b = inputHandler.getDouble("Введите значение b:");
        double c = inputHandler.getDouble("Введите значение c:");
        double d = inputHandler.getDouble("Введите значение d:");
        int n = inputHandler.getInt("Введите значение n:");
        int m = inputHandler.getInt("Введите значение m:");
        int threadCount = inputHandler.getThreadCount("Введите количество потоков (1, 2 или 4):");
        System.out.print("\033[0m");

        for (int i = 0; i < functions.length; i++) {
            Function function = functions[i];
            String functionName = functionNames[i];

            long startTime = System.nanoTime();
            OptimizedIntegralCalculator calculator = new OptimizedIntegralCalculator(function, a, b, c, d, n, m);
            double integral = calculator.calculate();
            long endTime = System.nanoTime();
            long duration = (endTime - startTime) / 1000000;  // convert to milliseconds

            System.out.println("\033[0;34m" + "Приближенное значение интеграла для функции " + functionName + " равно " + integral + "\033[0m");
            System.out.println("\033[0;33m" + "Время выполнения: " + duration + " мс" + "\033[0m");
        }
    }
}
